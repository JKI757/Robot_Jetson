
# Robotics Research and Development

![Robot pic](https://github.com/JKI757/Robot_c-/blob/master/pics/IMG_5699%20(2).jpeg)

## Bill of Materials:
1. Jetson Nano Devkit Model
2. Generic Wifi Dongle -- could also use an M2 wifi module supported by the Jetson Nano.
3. AUSTAR 313mm Wheelbase Chassis Frame W/ Tires For 1/10 AXIAL SCX10 RC Car

![austar pic](https://github.com/JKI757/Robot_c-/blob/master/pics/Screen%20Shot%202020-05-17%20at%206.46.17%20PM.png)

4. Logitech F710 Controller
5. NodeMCU ESP8266 Microcontroller

![nodemcu pic](https://github.com/JKI757/Robot_c-/blob/master/pics/IMG_5703.jpeg)

6. DC Motor Driver, DROK L298 Dual H Bridge Motor Speed Controller DC 6.5V-27V 7A PWM Motor Regulator Board 12V 24V Electric Motor Control Module Industrial 160W with Optocoupler Isolation

![drok motor controller pic](https://github.com/JKI757/Robot_c-/blob/master/pics/IMG_5183.jpeg)

7. Elegoo EL-CP-004 120pcs Multicolored Dupont Wire 40pin Male to Female, 40pin Male to Male, 40pin Female to Female Breadboard Jumper Wires Ribbon Cables Kit for arduino
8. 2* DC Buck Module, DROK Adjustable Buck Converter Step Down Voltage Regulator 6V-32V 30V 24V 12V to 1.5-32V 5V 5A LCD Power Supply Volt Reducer Transformer Module Board with USB Port Protective Case 

![dc buck converter DROK](https://github.com/JKI757/Robot_c-/blob/master/pics/IMG_5702.jpeg)

9. TalentCell Rechargeable 12V/11000mAh 9V/14500mAh 5V/26400mAh DC Output Lithium ion Battery Pack for LED Strip and CCTV Camera, Portable Li-ion Power Bank with AC/DC Charger, Black

![battery pic](https://github.com/JKI757/Robot_c-/blob/master/pics/IMG_5188.jpeg)

10. Protek 130T Digital High Torque Servo

![protek pic](https://github.com/JKI757/Robot_c-/blob/master/pics/IMG_5704.jpeg)

11. RPLIDAR A1 -- not currently used, but installed.
12. Makeblock Starter Robot Kit (IR Version)
13. Assorted hookup wires, standoffs, breadboard, etc.

## Code
- placeholder

## Concept
- So one day I was taking AI4R at Georgia Tech, and one of the extra credit assignments was to build a robot, any robot, for possibly a point or two of extra credit.  So I bought the Makeblock starter kit and put it together.  It was a cool little skid steer, I could drive it around the floor a little bit with its IR remote, it could detect walls and back up instead of running into them, it had a little arduino onboard, but it was pretty limited in what it could do.

![old robot pic](https://github.com/JKI757/Robot_c-/blob/master/pics/IMG_4411.jpeg)

- But then I got bored.  There just wasn't much I could do with the platform.  So I started looking up different robotics platforms, looking up sensors, looking at all kinds of different ways to get involved in the field.  

- I'd already purchased a Jetson Nano Dev kit, so I thought that might be a place to start.  I tried to shoehorn it into my skid steer, rapidly found out that wasn't going to work (space or power) and so I started down the path to where we are today.  

- First I knew I'd need some kind of a platform.  I tried buying some additional rails for the makeblock kit, and did end up using them a little bit (you can see the blue aluminum bracket holding the rplidar in the pictures).  That still didn't get me where I wanted to be, and then I realized that skid steer was kind of silly if I wanted to build something that was truly going to represent something interesting.  So I went down to the local hobby store and started looking at pieces and parts for a real steering system (and at this point I knew nothing at all about RC cars or anything in that world at all), purchased a couple of steering arms, some linkage, a servo, etc.  Started working on trying to put something together with those and discovered that it just wasn't something I knew enough (or had the manufacturing capabilty) to do.

- So then I started reading about RC cars.  Went to the hobby shop again, and saw several that I might be able to take apart, but spending 300 bucks on one and then throwing half of it away seemed silly, also I didn't care a bit about the body at all.  Once I had an idea what I was looking for, however, I happened upon a chassis kit on ebay.  That gave me everything I needed to get started.  When I built that up, I installed a steering servo, build a platform to attach the motor controller to, added a breadboard at the front to hold my microcontroller that I used to generate the PWM signals to drive the steering servo and the motor controller, added a battery, put the Jetson in place and added two Drok DC buck converters to get the voltages I needed.  The servo can run on 5vdc, but 7 works better (the servo needs to be relatively powerful to move the wheels with the weight on them), the Jetson needs exactly 5vdc, the motor controllers needs some voltage to run its logic (more on this later), and the micro can take from 5-20 or so vdc, but its logic level is 3.3vdc.  Also key to this is that the nodemcu can provide 3.3vdc out.  

- It's important to talk about logic levels here.  I actually pulled out a bunch of different hobby microcontrollers -- Arduino Mega 2560, Arduino Micro, Arduino Mini, Teensy 4.0, and finally settled on a NodeMCU ESP8266 board.  There were two major difficulties with all of them -- #1, getting the right logic levels (of course level shifters can be used, and I did), and keeping power draw down and being able to have a device that's capable of listening to serial for the commands and driving two different PWM devices with two different PWM frequencies at the same time.  All of these micros can probably do this, but the nodemcu seemed to do it most easily, was able to take a large voltage in (relieving me of the need to run 5vdc down to the lower deck of the vehicle as I already had 7vdc there for the steering servo), and could generate 3.3vdc for the motor controller.  The motor controller can run on 3.3 or 5, but it has to be provided with the same voltage to its logic power pin as the gpio volatge of the device powering it.  This is not documented anywhere, the silkscreen and datasheet say 5vdc.  That was actually the last piece of the puzzle to get the whole thing to work.  The Jetson Nano is actually a 1.8vdc device, but it has level shifters internal to the dev kit board that bring it up to 3.3vdc.  But you can't talk to a 5vdc level micro with that -- Arduino Mega and some of the others are all 5vdc gpios and serial lines.  The Arduino mega (and a couple of others) can listen to serial over their USB port, and that's what I ended up using for serial on the NodeMCU micro.

- So the obvious question here -- why use a micro at all?  Why not just run pwm from the two Jetson pins on the devkit that support it, and use the gpios to control the motor controller?  First, it's a lot of wires to run.  Second, when I started this, the jetson didn't have an easy way to reconfigure the j41 pins to enable pwm out, and it seemed (oh so silly in hindsight) easier to just run one serial line down to a micro that could do the pwm and gpios.  I discovered about five minutes into this that it was going to be a pain when I couldn't even get the Jetson to put serial out on the j41 header -- but figured I'd stick with it for the learning value anyway.

- In the end, I used a very simple serial protocol that uses two bytes, a command byte from [0x0A..0x0F] and a data byte from [0x00..0xFF] -- commands are the obvious, change direction, turn left, turn right, brake, drive, and the data is just a magnitude for the command.  The micro just runs a simple loop looking for serial data, when it comes in it checks to see if it has a command onboard already, if it does not it interprets the byte it sees as a command and then looks for data, if it has a command onboard already it takes the data and executes the command.  Very simple protocol, only limited by the 0-255 data amount, but those values were sufficient to provide both smooth acceleration, driving, and steering.  Basically the event data from the joystick is internally mapped from whatever it is (usually -32768..32768) to 0-255, and then that value is mapped onboard the micro to the real hard values that we want to set as limits.  As an example, the steering servo accepts values from 1000 to 2000 microseconds, 1000 is far right, 2000 far left, so the mapping is essentially turn left 0-255 where 0 is 1500 and 255 is 2000, similarly, the driving motor controller uses a pwm value from 0-65, which maps from 0-255 as well.  Those values are determined from experimentation and datasheets.  There's essentially zero error checking and there have been a couple of instances where the micro apparently either stopped receiving commands from the control program and left the pwm values where they were (steering hard left at full speed and totally unresponsive to commands in one case).  

- Control program.  C++, uses libevdev to process the events from the controller, has an event loop that simply looks for events and processes those it's interested in.  Mostly the two joysticks are used, left to steer and right for throttle, but others can be and have been used.  Skid steering has been done with the trigger buttons, which provide a smooth 0-255 analog signal.  There are two layers of abstraction between the control program and the hardware, the Robot class holds all the logic to do the driving and the Motor class translates commands into something to put on the wire and then sends them down to the micro.  Both of these could be named better and the functionality could be isolated better.

- Future work:  In progress now, the Lidar is implemented roughly to the level that we can turn it on and off from the program using the rplidar api and driver provided by the manufacturer over USB.  At the moment further work is on hold there due to power requirements, the jetson can't power that and control the micro at the same time both over USB.  As a result, the code is being refactored in another branch to directly control the motor controller pwm and gpios and the servo pwm from the Jetson to take that load off the usb and remove the micro completely from the picture.  Also the project desperately needs to be refactored into a good cmake project to distribution.
