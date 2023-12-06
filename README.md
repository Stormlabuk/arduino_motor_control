# Ring Control Node

Uses rosserial-arduino to bridge onto an arduino and control it through ros. Really handy.

## Usage

1. Create your arduino targets in [firmware](firmware/)
2. Add the relavant targets to the [package cmake](CMakeLists.txt).
3. Add target-upload version of target.
4. Add generate_arduino_firmware call to [firmware cmake](firmware/CMakeLists.txt). Two examples there already.
5. The node starts automatically at this point.
6. Either use roscore and rosserial-python to connect to the arduino node.
7. Or use a launch file like this [example](launch/single_linact.launch)

## Compiling

Compiling is done in 2 stages, verify and upload:

1. Verifying arduino-serial package **PACKAGE_NAME**

``` bash
catkin build PACKAGE_NAME
```

2. Uploading target **TARGET** in package **PACKAGE_NAME**

``` bash
catkin build --no-deps  PACKAGE_NAME --make-args PACKAGE_NAM_firmware_TARGET-upload
```

3. TARGET node is immediately uploaded and run. Node is spun when a rosserial node is used to connect the Arduino to remote master. See [single motor example](launch/single_linact.launch) for a reference.

## Examples

### [Chatter](firmware/chatter.cpp)

Simple hello world program.

### [Single Servo](firmware/single_servo.cpp)

Subscribes on topic "servo", taking in an UInt16 and applying it to the servo using "servo.writeMicroseconds()". Might be worth coming back to this and applying rosParam to the "servo.attach()" call at some point.

[Launch file](launch/single_linact.launch).

### [Stepper motor](firmware/stepper.cpp)

Subscribes on topic "stepper", message type Int32, the motor will move that many mms (works positive and negative). The pins are setup for an Arduino Uno with Motor Shield V3. The motor speed can be set using rosParam ("MOTOR_SPEED"), as well as the rotor Diameter ("ROTOR_D"), which are used together to calculate the RPM required.

## Dependencies

```bash
sudo apt install ros-noetic-rosserial
sudo apt install ros-noetic-rosserial-arduino
```

## Rosserial Tutorial

Generally good [reference tutorial](http://wiki.ros.org/rosserial_arduino/Tutorials/CMake).
