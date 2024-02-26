// WifiShip docker module (connect/disconnect to station).

/*
  Version: 4
  Last mod.: 2024-02-26
*/

/*
  Design

    Data structures

      Status:
        * Not docked
        * Docked
        * Failed:
          * Station not found
          * Wrong password
          * Some other shit

      StationName == Common.CraftName // SSID
      StationPassword: TChar[64]

      // IP addresses when connected:
      ( Address = TUint_1[4] )
      ShipAddress: Address
      StationAddress: Address

    Methods

      --( inherited )--
      Init: bool

      --( Status )--
      GetStatus: bool

      --( Docking )--
      DockTo: DockingStatus
        (StationName, StationPassword)
      Undock
        // post_assert(DockingStatus == Not docked)

      --( Docking timeout )--
      GetDockingTimeout_S: TUint_1
      SetDockingTimeout_S(TUint_1)

      --( Docked channel )--
      GetShipAddress: bool, Address
        // local IP: 192.168.0.208

      GetStationAddress: bool, Address
        // Gateway IP: 192.168.0.1
*/

#pragma once

#include "Common/CraftIdentity/Interface.h"

namespace me_WifiShip_Docker
{
  // StationName (SSID)
  typedef me_WifiShip_Common_CraftIdentity::TCraftName TStationName;

  // StationPassword (Password)
  typedef TChar TStationPassword[64 + 1];

  // Address (IP)
  typedef TUint_1 TAddress[4];

  // Docking status:
  enum struct TStatus
  {
    Undocked,
    Docked,
    Nah_StationNotFound,
    Nah_WrongPassword,
    Nah_TimeoutReached,
    Nah_Other
  };

  class TDocker
  {
    public:
      TBool Init();

      // Status
      TStatus GetStatus();

      // Docking
      TStatus DockTo(
        const TStationName StationName,
        const TStationPassword StationPassword
      );
      void Undock();

      // Address
      TBool GetShipAddress(TAddress ShipAddress);
      TBool GetStationAddress(TAddress StationAddress);

      // Timeout
      TUint_1 GetDockingTimeout_S();
      void SetDockingTimeout_S(const TUint_1 aDockingTimeout_S);

    private:
      TUint_1 DockingTimeout_S;
      TStatus Status;

      TStatus MapInnerStatus(const TSint_1 aInnerStatus);
  };
}

/*
  2024-01-03
  2024-01-13
  2024-02-07
  2024-02-26
*/
