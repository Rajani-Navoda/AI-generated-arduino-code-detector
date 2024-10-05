#include <AccelStepper.h>

// Define the stepper motor
AccelStepper stepper(AccelStepper::DRIVER, 2, 3); // Using pins 2 and 3 for step and direction

const int minPosition = 0;    // Minimum position
const int maxPosition = 1000; // Maximum position
bool goingForward = true;    // Direction flag

void setup() {
  // Set maximum speed and acceleration
  stepper.setMaxSpeed(100.0);
  stepper.setAcceleration(50.0);

  // Set the initial position
  stepper.setCurrentPosition(minPosition);
  stepper.moveTo(maxPosition); // Move to maximum position
}

void loop() {
  // Move the stepper to the target position
  stepper.run();

  // Check if we have reached the target position
  if (stepper.distanceToGo() == 0) {
    if (goingForward) {
      // If moving forward, switch direction and set new target
      goingForward = false;
      stepper.moveTo(minPosition); // Move to minimum position
    } else {
      // If moving backward, switch direction and set new target
      goingForward = true;
      stepper.moveTo(maxPosition); // Move to maximum position
    }
  }
}
