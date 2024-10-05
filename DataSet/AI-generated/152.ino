#include <Servo.h>

// Define the number of servos
const int numServos = 8;

// Create an array of Servo objects
Servo servos[numServos];

// Define the pins connected to the servo signals
const int servoPins[numServos] = {2, 3, 4, 5, 6, 7, 8, 9};

void setup() {
  // Attach each servo to its corresponding pin
  for (int i = 0; i < numServos; i++) {
    servos[i].attach(servoPins[i]);
  }
}

void loop() {
  // Sweep all servos from 0 to 180 degrees
  for (int pos = 0; pos <= 180; pos += 1) {
    for (int i = 0; i < numServos; i++) {
      servos[i].write(pos);  // Set the position of each servo
    }
    delay(15);  // Wait for the servos to reach the position
  }

  // Sweep all servos from 180 to 0 degrees
  for (int pos = 180; pos >= 0; pos -= 1) {
    for (int i = 0; i < numServos; i++) {
      servos[i].write(pos);  // Set the position of each servo
    }
    delay(15);  // Wait for the servos to reach the position
  }
}
