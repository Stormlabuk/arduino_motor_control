#include <ros.h>
#include <std_msgs/UInt32.h>
#include <Servo.h>

ros::NodeHandle nh;
/**
 * @brief Actuator objects
 * act 0 is the most proximal actuator, act 3 is the most distal
 */
Servo act0, act1, act2, act3;
char loginfo_buffer[100];

void act_cb(const std_msgs::UInt32 &cmd_msg) {
    uint32_t data = cmd_msg.data;
    uint8_t act_cmds[4];
    int step_inputs[4];
    sprintf(loginfo_buffer, "data, var: %X", data);
    nh.loginfo(loginfo_buffer);

    for (int i = 0; i < 4; i++) {
        act_cmds[i] = (data & 0xFF);  // Extract the rightmost byte
        step_inputs[i] = (int) (act_cmds[i]) * 1000 / 255 +
                      1000;
        sprintf(loginfo_buffer, "shifted data: %02X at i %d", act_cmds[i], i);
        nh.loginfo(loginfo_buffer);
        sprintf(loginfo_buffer, "calc data: %d at i %d", step_inputs[i], i);
        nh.loginfo(loginfo_buffer);
        data >>= 8;
    }
    


    // sprintf(loginfo_buffer, "act0: %d", act_cmds[3]);
    // nh.loginfo(loginfo_buffer);
    // sprintf(loginfo_buffer, "act1: %d", act_cmds[2]);
    // nh.loginfo(loginfo_buffer);
    // sprintf(loginfo_buffer, "act2: %d", act_cmds[1]);
    // nh.loginfo(loginfo_buffer);
    // sprintf(loginfo_buffer, "act3: %d", act_cmds[0]);
    // nh.loginfo(loginfo_buffer);

    // act0.writeMicroseconds(act_cmds[3]);
    // act1.writeMicroseconds(act_cmds[2]);
    // act2.writeMicroseconds(act_cmds[1]);
    // act3.writeMicroseconds(act_cmds[0]);
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
    act0.writeMicroseconds(1500);
    act1.writeMicroseconds(1500);
    act2.writeMicroseconds(1500);
    act3.writeMicroseconds(1500);
}

void loop() {
    nh.spinOnce();
    delay(1);
}