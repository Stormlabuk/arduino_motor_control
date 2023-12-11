cmake_minimum_required(VERSION 3.0.2)
project(arduino_firm_targets)
## Compile as C++11, supported in ROS Kinetic and newer
add_compile_options(-std=c++11)

include_directories(${ROS_LIB_DIR})

# Remove this if using an Arduino without native USB (eg, other than Leonardo)
add_definitions(-DUSB_CON)

generate_arduino_firmware(chatter
  SRCS chatter.cpp ${ROS_LIB_DIR}/time.cpp
  BOARD mega2560
  PORT /dev/ttyACM0
)

generate_arduino_firmware(single_motor
  SRCS single_servo.cpp ${ROS_LIB_DIR}/time.cpp
  BOARD mega2560
  PORT /dev/ttyACM0
)

generate_arduino_firmware(multi_motor
  SRCS multi_lin_act.cpp ${ROS_LIB_DIR}/time.cpp
  BOARD mega2560
  PORT /dev/ttyACM0
)

generate_arduino_firmware(stepper
  SRCS stepper.cpp ${ROS_LIB_DIR}/time.cpp
  BOARD uno
  PORT /dev/ttyACM1
)