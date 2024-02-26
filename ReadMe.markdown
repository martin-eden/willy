# My mobile platform project on DC motors

  I call it "Willy" as sound resembles "wheely".

  That's not the first incarnation, platform design is 2nd generation
  and parts arrangement is 5th.

# Installation

  Clone repo, copy "Willy" to sketch folder.

  Inside there are four folders:

    1. `Arduino_Willy`
    2. `WemosD1_Willy`
    3. `Arduino_Willy libraries`
    4. `WemosD1_Willy libraries`

  Copy contents of (3) and (4) to your libraries folder. Inside are my
  libraries and commonly available libraries that is needed. Names of
  my libraries begins with "me_". So in case of file conflicts for
  standard libraries, copy only mine. Then compile and install needed
  standard libraries manually.

# Principal electronic parts

  * Motor board

    Motor board is commanded by text protocol, similar to G codes (I call
    it "M codes"). So command "L-40" starts spinning left motor backwards
    at 40% rate. "R" for right motor, "D" for delay in milliseconds.

    When motorboard is ready to receive commands it sends
    (newline, "G", newline) sequence.

  * User of motor board

    User of motor board (I call it "overseer") is another microcontroller
    board. It connects to WiFi, receives commands for motor board via Http,
    sends them to motor board and provides sampled accelerometer feedback.

    Http part is GET/POST endpoint. Returned accelerometer data is JSON.

# Now creative part...

  * You

    "You" is you or your program. You sent M-commands and received
    JSON with sampled acceleration/rotation over timeframe.
    Your task is to make rover to go where you want and how you want.
    In real world.

# Real world

## Problems

  * Accelerometer data is noisy

    You have acceleration but you want a position.

    To get position you need distance. To get distance you need to sum
    (integrate) over velocity. To get velocity you need to integrate
    over acceleration. Stationary accelerometer values are roaming.
    Some damping over feedback is needed.

  * Motors stall

    Providing 10% to motor does nothing but a buzzy sound. Even hanged
    wheels actually starts moving over 30% of power. Say 40% for floor.
    It would be nice for you to be able to figure exact values at will.

  * Ground is not flat

    Motor power values for turning depend of surface inclination.

  * There are walls!

    You can bump into them even when you figured out how to move
    straight. If you enjoy hitting walls, you can create bump map.

  * Traction is not equal

    I hope you can get the wheel out of that oil/ice/hole spot. You can
    update your oil map too.

## Hints

  * Detecting distance traveled

    Doing rotation by skid turn (100/-100) for several seconds
    (to stabilize rotational speed) retrieves rate of rotation.
    Like 312 degrees per second.

    When you know distance between wheels you can calculate length of
    arc that wheels traveled.

  * Detecting stall motor speeds

    As we can detect actual motion when we receive essential
    rotational data from accelerometer when we were doing skid turn,
    we can decrease motor values until there is no motion. So now we
    are in stall zone.

  * Measuring distance in body lengths makes more sense here

    So internal command to move forward is like "front speed .3 body lengths".

  * TWR (thrust-weight ratio)

    You naturally getting TWR from acceleration. If you know your weight,
    you can calculate thrust.

  * Balancing by rotation

    We all know we need to keep center of mass projection inside the
    support base area. For two-wheelers you can keep catching center of
    mass by doing movements within small area.

    But what about lifting third touch point by centrifugal force?
    You can use that skid turn basic movement.

  * Rudolf Kalman is your new friend. PIDs is your new area of expertise.

# Design notes

  * Two wheeler

    I would prefer one wheel but I had troubles making turns.

    Most people think that the natural arrangement is four wheels near
    corners. Like in combustion cars or RC cars. Both of them have two
    motors. One for steering (driver hands in cars) and one for linear
    motion.

    With two side motors you can do differential steering which is superior.

    There is natural tendency to oversteering tho, so you need
    non-linear compensation for that. It's possible to create
    two-combustion-engines car with two-axis joystick. But we have
    Tesla already.)

  * Two boards

    Yes, one board is enough. Initially I wanted one board but just
    switched to ESP8266 and didn't realize that Arduino motor shields
    wont work because of different electrical pinout. So I used proved
    Arduino base for motor board and wrote new stuff for gyro and WiFi
    for Esplora. Now I feel that splitting one thing in three (one, two,
    communication channel) reduces complexity more than twice.
    Especially when considering simplicity. But communication channel
    is new failure point and it adds latency.

  * Four wheels (historical note)

    My first platform had four powered wheels. From 14.4V Makita
    battery. That was overpowered thing, like rabbit on steroids. I
    burned motor controller (before utilizing step-down circuit) and
    threw wheels off axles doing skid turns (before screwing them to
    axles). So using more power requires additional design features.

    Four powered wheels with left-right side motors. Differential
    steering is the only option.

    On four wheels it introduces sideslip. Look at the letter X - wheels
    at ends of X and the center of letter is the center of mass. When
    you doing turn, ends of X rotate near the center. Wheels are pulled
    a bit of sideways by doing this. That's why they were falling.

    That tires with small rotating cylinders on them should help but I
    guess they have their own issues.

    From the other hand, four wheels will give you natural stability,
    more traction points and not-annoying-look.

# Project history and status

  As all my projects, I do changes when I have mood for this or
  inspiration.

  First four-wheels rover (3 or 4 incarnations) was made in 2016 in
  Moscow, Russia. Plywood, jigsaw.

  Two-wheels rover was made in 2023 in Mississauga, Canada. Solid wood,
  CNC.

  Code design definitely can be improved (namespaces, classes) but current
  "just works" state is okay for me.

2023-12-12, Canada
