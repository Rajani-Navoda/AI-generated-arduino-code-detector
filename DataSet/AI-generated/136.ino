#include <AccelStepper.h>

// Define the stepper motors
// Using pins (1, 2) for motor 1 and (3, 4) for motor 2
AccelStepper stepper1(AccelStepper::DRIVER, 2, 3); // Motor 1
AccelStepper stepper2(AccelStepper::DRIVER, 4, 5); // Motor 2

void setup() {
  // Set maximum speed and acceleration for both motors
  stepper1.setMaxSpeed(200.0);
  stepper1.setAcceleration(100.0);
  stepper2.setMaxSpeed(200.0);
  stepper2.setAcceleration(100.0);

  // Set initial positions and move to target positions
  stepper1.setCurrentPosition(0);
  stepper2.setCurrentPosition(0);

  stepper1.moveTo(1000); // Move to position 1000
  stepper2.moveTo(-1000); // Move to position -1000
}

void loop() {
  // Run the steppers
  stepper1.run();
  stepper2.run();

  // Check if both steppers have reached their targets
  if (stepper1.distanceToGo() == 0 && stepper2.distanceToGo() == 0) {
    // Reverse directions
    stepper1.moveTo(-stepper1.currentPosition());
    stepper2.moveTo(-stepper2.currentPosition());
  }
}
