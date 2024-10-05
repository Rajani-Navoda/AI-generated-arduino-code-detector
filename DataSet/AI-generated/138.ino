#include <AccelStepper.h>
#include <MultiStepper.h>

// Define stepper motors
AccelStepper stepper1(AccelStepper::DRIVER, 2, 3); // Motor 1
AccelStepper stepper2(AccelStepper::DRIVER, 4, 5); // Motor 2

// Create an instance of MultiStepper
MultiStepper steppers;

void setup() {
  // Set maximum speed and acceleration for both motors
  stepper1.setMaxSpeed(200.0);
  stepper1.setAcceleration(100.0);
  stepper2.setMaxSpeed(200.0);
  stepper2.setAcceleration(100.0);

  // Add the steppers to MultiStepper
  steppers.addStepper(stepper1);
  steppers.addStepper(stepper2);

  // Set target positions
  long positions[2]; // Array to hold target positions for each motor
  positions[0] = 1000; // Target position for motor 1
  positions[1] = 1000; // Target position for motor 2

  // Move both motors to the target positions
  steppers.moveTo(positions);
}

void loop() {
  // Run the steppers to their target positions
  steppers.run();
  
  // Check if the motors have reached their target positions
  if (steppers.isRunning() == false) {
    // Optionally, set new target positions or perform other actions
    long newPositions[2];
    newPositions[0] = -1000; // New target position for motor 1
    newPositions[1] = -1000; // New target position for motor 2
    
    // Move both motors to the new target positions
    steppers.moveTo(newPositions);
  }
}
