# Ring Control Node

Uses rosserial-arduino to bridge onto an arduino and control it through ros. Really handy.

## Usage

### [Multi-Motor](firmware/multi_lin_act.cpp)

Spins a node with single topic "servo". Message is UInt32.
Big Endian pair is then passed to the proximal motor, with the 0x00-0xFF range mapping the interval 1000-2000 (none to max extension).
The same repeats going towards Little Endian.

## Dependencies

```bash
sudo apt install ros-noetic-rosserial
sudo apt install ros-noetic-rosserial-arduino
```

### Rosserial Tutorial

Generally good [reference tutorial](http://wiki.ros.org/rosserial_arduino/Tutorials/CMake).
