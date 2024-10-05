#include <AccelStepper.h>

// Define the stepper motor
AccelStepper stepper(AccelStepper::DRIVER, 2, 3); // Using pins 2 and 3 for step and direction

void setup() {
  // Set maximum speed and acceleration
  stepper.setMaxSpeed(200.0);
  stepper.setAcceleration(100.0);

  // Set the initial position
  stepper.setCurrentPosition(0);

  // Move to the first target position
  stepper.moveTo(1000); // Move to position 1000
  stepper.runToNewPosition(1000); // Blocking call to move to position 1000
  
  // Now set a new target position
  stepper.moveTo(-1000); // Move to position -1000
  stepper.runToNewPosition(-1000); // Blocking call to move to position -1000
}

void loop() {
  // Nothing to do here
}
