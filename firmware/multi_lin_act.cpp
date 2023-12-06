#include <Rosserial_Arduino_Library/src/ros.h>
#include <Rosserial_Arduino_Library/src/std_msgs/UInt32.h>
#include <Servo/Servo.h>

ros::NodeHandle nh;
/**
 * @brief Actuator objects
 * act 0 is the most proximal actuator, act 3 is the most distal
 */
Servo act0, act1, act2, act3;

void act_cb(const std_msgs::UInt32 &cmd_msg) {
    uint32_t data = cmd_msg.data;
    int act_cmds[4];
    for (int i = 0; i < 4; i++) {
        act_cmds[i] = (int)(data & 0xFF) * 1000 / 255 +
                      1000;  // Extract the rightmost byte
        data >>= 8;
    }
    act0.writeMicroseconds(act_cmds[3]);
    act1.writeMicroseconds(act_cmds[2]);
    act2.writeMicroseconds(act_cmds[1]);
    act3.writeMicroseconds(act_cmds[0]);
}

ros::Subscriber<std_msgs::UInt32> sub("servo", act_cb);

void setup() {
    nh.initNode();
    nh.subscribe(sub);

    act0.attach(9);
    act1.attach(10);
    act2.attach(11);
    act3.attach(12);

    // initialise positions
    act0.writeMicroseconds(1100);
    act1.writeMicroseconds(1100);
    act2.writeMicroseconds(1100);
    act3.writeMicroseconds(1100);
}

void loop() {
    nh.spinOnce();
    delay(1);
}