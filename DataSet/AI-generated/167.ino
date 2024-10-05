#include <Servo.h>  // Include the Servo library

Servo myServo;  // Create a Servo object

void setup() {
  myServo.attach(9);  // Attach the servo control to pin 9
}

void loop() {
  // Sweep the servo from 0 to 180 degrees
  for (int angle = 0; angle <= 180; angle++) {
    myServo.write(angle);  // Set the servo position
    delay(15);             // Wait for the servo to reach the position
  }

  // Sweep the servo from 180 to 0 degrees
  for (int angle = 180; angle >= 0; angle--) {
    myServo.write(angle);  // Set the servo position
    delay(15);             // Wait for the servo to reach the position
  }
}
