#include <Rosserial_Arduino_Library/src/ros.h>
#include <Rosserial_Arduino_Library/src/std_msgs/UInt16.h>
#include <Servo/Servo.h>

ros::NodeHandle nh;
Servo servo;
int servoPin = 9;
char loginfo_buffer[100];

void servo_cb(const std_msgs::UInt16 &cmd_msg) {
    servo.writeMicroseconds(cmd_msg.data);
}

ros::Subscriber<std_msgs::UInt16> sub("servo", servo_cb);

void setup() {
    nh.initNode();
    nh.subscribe(sub);

    if (!nh.getParam("servoPin", &servoPin)) {
        nh.loginfo("servoPin not set, using default");
        servoPin = 10;
    } else {
        sprintf(loginfo_buffer, "servoPin: %d", servoPin);
        nh.loginfo(loginfo_buffer);
    };
    servo.attach(servoPin);
}

void loop() {
    nh.spinOnce();
    delay(1);
}
