# Ring Control Node

Uses rosserial-arduino to bridge onto an arduino and control it through ros. Really handy.

## Usage

### [Chatter](firmware/chatter.cpp)

Simple hello world program.

### [Single Servo](firmware/single_servo.cpp)

Subscribes on topic "servo", taking in an UInt16 and applying it to the servo using "servo.writeMicroseconds()".

[Launch file](launch/single_linact.launch).

### [Stepper motor](firmware/stepper.cpp)

Subscribes on topic "stepper", message type Int32, the motor will move that many mms (works positive and negative). The pins are setup for an Arduino Uno with Motor Shield V3. The motor speed can be set using rosParam ("MOTOR_SPEED"), as well as the rotor Diameter ("ROTOR_D"), which are used together to calculate the RPM required.

[Launch file](launch/stepper.launch)

### [Multi-Motor](firmware/multi_lin_act.cpp)

Spins a node with single topic "servo". Message is UInt32.
Big Endian pair is then passed to the proximal motor, with the 0x00-0xFF range mapping the interval 1000-2000 (none to max extension).
The same repeats going towards Little Endian.

[Launch file](launch/multi_linact.launch)

### [Sampling Node](scripts/sampling_func.py)

Node to discretise and publish Magnetic Field and Servo positions from a min-max input to N samples, following a sinusoidal pattern.

Boundary values are defined in the [config](config/sampler.yaml) file. Field values are floats, while servo values are integers between 0 and 100, representing full retraction and full extension respectively.

To ensure even point distribution, the "ts" rosparam is always rounded to the nearest odd number.

[Launch File](launch/sampling_node.launch)

### Compiling

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

## Dependencies

```bash
sudo apt install ros-noetic-rosserial
sudo apt install ros-noetic-rosserial-arduino
```

### Rosserial Tutorial

Generally good [reference tutorial](http://wiki.ros.org/rosserial_arduino/Tutorials/CMake).
