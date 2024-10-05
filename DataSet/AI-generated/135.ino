#include <AccelStepper.h>

// Define the stepper motor
AccelStepper stepper(AccelStepper::DRIVER, 2, 3); // Using pins 2 and 3 for step and direction

void setup() {
  // Set maximum speed (in steps per second)
  stepper.setMaxSpeed(100.0);
  stepper.setSpeed(50);  // Set the constant speed (in steps per second)
}

void loop() {
  // Continuously run the stepper at the set speed
  stepper.runSpeed();
}
