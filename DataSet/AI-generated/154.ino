#include <Servo.h>

// Define pins for servos
const int servoPin1 = 9;
const int servoPin2 = 10;

// Define pins for LEDs
const int ledPin1 = 2;
const int ledPin2 = 3;
const int ledPin3 = 4;

// Create Servo objects
Servo servo1;
Servo servo2;

void setup() {
  // Attach servos to pins
  servo1.attach(servoPin1);
  servo2.attach(servoPin2);

  // Set LED pins as output
  pinMode(ledPin1, OUTPUT);
  pinMode(ledPin2, OUTPUT);
  pinMode(ledPin3, OUTPUT);

  // Initialize servos
  servo1.write(90); // Position servos to 90 degrees (centered)
  servo2.write(90);

  // Turn off LEDs initially
  digitalWrite(ledPin1, LOW);
  digitalWrite(ledPin2, LOW);
  digitalWrite(ledPin3, LOW);
}

void loop() {
  // Sweep servos from 0 to 180 degrees
  for (int angle = 0; angle <= 180; angle += 1) {
    servo1.write(angle);
    servo2.write(180 - angle); // Move in the opposite direction
    delay(15); // Wait for the servos to reach the position
  }

  // Turn LEDs on and off in sequence
  digitalWrite(ledPin1, HIGH);
  delay(500);
  digitalWrite(ledPin1, LOW);
  delay(100);
  
  digitalWrite(ledPin2, HIGH);
  delay(500);
  digitalWrite(ledPin2, LOW);
  delay(100);

  digitalWrite(ledPin3, HIGH);
  delay(500);
  digitalWrite(ledPin3, LOW);
  delay(100);

  // Sweep servos from 180 to 0 degrees
  for (int angle = 180; angle >= 0; angle -= 1) {
    servo1.write(angle);
    servo2.write(180 - angle); // Move in the opposite direction
    delay(15); // Wait for the servos to reach the position
  }
}
