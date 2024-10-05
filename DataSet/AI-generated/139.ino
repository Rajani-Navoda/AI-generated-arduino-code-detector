#include <AccelStepper.h>
#include <MultiStepper.h>

// Define the stepper motors
AccelStepper stepper1(AccelStepper::DRIVER, 2, 3); // Motor 1
AccelStepper stepper2(AccelStepper::DRIVER, 4, 5); // Motor 2
AccelStepper stepper3(AccelStepper::DRIVER, 6, 7); // Motor 3

// Create an instance of MultiStepper
MultiStepper steppers;

void setup() {
  // Set maximum speed and acceleration for stepper1
  stepper1.setMaxSpeed(100.0);
  stepper1.setAcceleration(50.0);

  // Set maximum speed and acceleration for stepper2 and stepper3
  stepper2.setMaxSpeed(100.0);
  stepper2.setAcceleration(50.0);
  stepper3.setMaxSpeed(100.0);
  stepper3.setAcceleration(50.0);

  // Add steppers to MultiStepper
  steppers.addStepper(stepper1);
  steppers.addStepper(stepper2);
  steppers.addStepper(stepper3);

  // Set target positions for all steppers
  long positions[3]; // Array to hold target positions for each motor
  positions[0] = 1000; // Target position for motor 1
  positions[1] = 1000; // Target position for motor 2
  positions[2] = 1000; // Target position for motor 3

  // Move all motors to the target positions
  steppers.moveTo(positions);
}

void loop() {
  // Run all the steppers to their target positions
  steppers.run();

  // Check if the motors have reached their target positions
  if (!steppers.isRunning()) {
    // Reverse direction for stepper1 and set new targets for all steppers
    long newPositions[3];
    newPositions[0] = -stepper1.currentPosition(); // Reverse direction for motor 1
    newPositions[1] = 1000; // Maintain position for motor 2
    newPositions[2] = 1000; // Maintain position for motor 3

    // Move all motors to the new target positions
    steppers.moveTo(newPositions);
  }
}
