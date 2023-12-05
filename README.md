# Ring Control Node

Uses rosserial-arduino to bridge onto an arduino and control it through ros. Really handy.

## Usage

### [Multi-Motor](firmware/multi_lin_act.cpp)

Spins a node with single topic "servo". Message is UInt32.
Big Endian pair is then passed to the proximal motor, with the 0x00-0xFF range mapping the interval 1000-2000 (none to max extension).
The same repeats going towards Little Endian.

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
