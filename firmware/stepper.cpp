/* Example sketch to control a stepper motor with Arduino Motor Shield Rev3,
 * Arduino UNO and Stepper.h library. More info: https://www.makerguides.com */
// Include the Stepper library:
#include <Arduino.h>
#include <Stepper.h>
#include <ros.h>
#include <std_msgs/Int32.h>

#define pwmA 3
#define pwmB 11
#define brakeA 9
#define brakeB 8
#define dirA 12
#define dirB 13

// Define number of steps per revolution:
const int stepsPerRevolution = 200;
char loginfo_buffer[100];
ros::NodeHandle nh;
int MOTOR_SPEED;  // Motor speed in mm/s
int rotor_d;      // Rotor diameter in mm
int MOTOR_RPM;    // Motor speed in RPM
// Give the motor control pins names:

// Initialize the stepper library on the motor shield:
Stepper myStepper = Stepper(stepsPerRevolution, dirA, dirB);

void stepper_cb(const std_msgs::Int32 &cmd_msg) {
    int data = cmd_msg.data;
    myStepper.step(data);
}

ros::Subscriber<std_msgs::Int32> sub("stepper", &stepper_cb);

void setup() {
    nh.initNode();
    nh.subscribe(sub);
    while (!nh.connected()) {
        nh.spinOnce();
    }
    if (!nh.getParam("MOTOR_SPEED", &MOTOR_SPEED)) {
        nh.loginfo("MOTOR_SPEED not set, using default");
        MOTOR_SPEED = 10;
    } else {
        sprintf(loginfo_buffer, "MOTOR_SPEED: %dmm/s", MOTOR_SPEED);
        nh.loginfo(loginfo_buffer);
    };
    if (!nh.getParam("ROTOR_D", &rotor_d)) {
        rotor_d = 5;
        nh.loginfo("ROTOR_D not set, using default");
    } else {
        sprintf(loginfo_buffer, "ROTOR_D: %dmm", rotor_d);
        nh.loginfo(loginfo_buffer);
    }
    MOTOR_RPM = MOTOR_SPEED * 60 / (PI * rotor_d);

    // Set the PWM and brake pins so that the direction pins can be used to
    // control the motor:
    pinMode(pwmA, OUTPUT);
    pinMode(pwmB, OUTPUT);
    pinMode(brakeA, OUTPUT);
    pinMode(brakeB, OUTPUT);
    digitalWrite(pwmA, HIGH);
    digitalWrite(pwmB, HIGH);
    digitalWrite(brakeA, LOW);
    digitalWrite(brakeB, LOW);
    // Set the motor speed (RPMs):
    // write into message buffer
    sprintf(loginfo_buffer, "MOTOR_RPM: %d", MOTOR_RPM);
    nh.loginfo(loginfo_buffer);
    myStepper.setSpeed(MOTOR_RPM);
}
void loop() {
    // Step one revolution in one direction:
    // myStepper.step(100);
    // delay(2000);
    // // Step on revolution in the other direction:
    // myStepper.step(-100);
    // delay(2000);
    nh.spinOnce();
    delay(1);
}