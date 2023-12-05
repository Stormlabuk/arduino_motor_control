/* Example sketch to control a stepper motor with Arduino Motor Shield Rev3,
 * Arduino UNO and Stepper.h library. More info: https://www.makerguides.com */
// Include the Stepper library:
#include <Stepper/Stepper.h>
#include <Arduino.h>
#include <Rosserial_Arduino_Library/src/ros.h>
// Define number of steps per revolution:
const int stepsPerRevolution = 200;
// Give the motor control pins names:
#define pwmA 3
#define pwmB 11
#define brakeA 9
#define brakeB 8
#define dirA 12
#define dirB 13
// Initialize the stepper library on the motor shield:
Stepper myStepper = Stepper(stepsPerRevolution, dirA, dirB);
void setup() {
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
    myStepper.setSpeed(100);
}
void loop() {
    // Step one revolution in one direction:
    myStepper.step(100);
    delay(2000);
    // Step on revolution in the other direction:
    myStepper.step(-100);
    delay(2000);
}