#include <AccelStepper.h>

// Define the stepper motor
AccelStepper stepper(AccelStepper::DRIVER, 2, 3); // Using pins 2 and 3 for step and direction

void setup() {
  // Set maximum speed and acceleration
  stepper.setMaxSpeed(200.0);
  stepper.setAcceleration(100.0);

  // Set initial position
  stepper.setCurrentPosition(0);

  // Move to a target position
  stepper.moveTo(1000); // Move to position 1000

  // Move the stepper to the target position at full speed
  while (stepper.distanceToGo() != 0) {
    stepper.run(); // Continue running until the target position is reached
  }

  // Call stop() to halt the motor as quickly as possible
  stepper.stop();
}

void loop() {
  // After calling stop(), the motor will come to a halt
  // Optionally, you can add some additional code to handle post-stop actions
}
