#include <Wire.h>
#include <AStar32U4.h>

AStar32U4RobotController robot;

void setup() {
  // Initialize the robot controller
  robot.begin();

  // Set up motors and LEDs
  robot.setMotorSpeed(0, 0); // Stop both motors
  pinMode(LED_BUILTIN, OUTPUT);
}

void loop() {
  // Drive forward
  robot.setMotorSpeed(0, 100); // Motor 0 forward
  robot.setMotorSpeed(1, 100); // Motor 1 forward
  digitalWrite(LED_BUILTIN, HIGH); // LED on
  delay(1000);

  // Stop motors
  robot.setMotorSpeed(0, 0); 
  robot.setMotorSpeed(1, 0);
  digitalWrite(LED_BUILTIN, LOW); // LED off
  delay(500);

  // Drive backward
  robot.setMotorSpeed(0, -100); // Motor 0 backward
  robot.setMotorSpeed(1, -100); // Motor 1 backward
  digitalWrite(LED_BUILTIN, HIGH); // LED on
  delay(1000);

  // Stop motors
  robot.setMotorSpeed(0, 0); 
  robot.setMotorSpeed(1, 0);
  digitalWrite(LED_BUILTIN, LOW); // LED off
  delay(500);
}
