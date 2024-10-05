#include <AccelStepper.h>

// Define the stepper motor
AccelStepper stepper(AccelStepper::DRIVER, 2, 3); // Using pins 2 and 3 for step and direction

void setup() {
  // Set maximum speed and acceleration
  stepper.setMaxSpeed(100.0);
  stepper.setAcceleration(50.0);

  // Move to the initial position
  stepper.setCurrentPosition(0);

  // Set a target position and block until it is reached
  stepper.moveTo(1000); // Move to position 1000
  stepper.runToNewPosition(1000); // Blocking call to move to position 1000

  // Now move to another position
  stepper.moveTo(-1000); // Move to position -1000
  stepper.runToNewPosition(-1000); // Blocking call to move to position -1000
}

void loop() {
  // Nothing to do here
}
