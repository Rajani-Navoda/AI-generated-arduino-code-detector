#include <AccelStepper.h>

const int potPin = A0; // Analog pin for potentiometer
const int maxSteps = 1000; // Maximum number of steps for the motor

// Define the stepper motor
AccelStepper stepper(AccelStepper::DRIVER, 2, 3); // Using pins 2 and 3 for step and direction

void setup() {
  // Set maximum speed and acceleration
  stepper.setMaxSpeed(200.0);
  stepper.setAcceleration(100.0);
  
  // Set the initial position
  stepper.setCurrentPosition(0);
}

void loop() {
  // Read the analog value from the potentiometer
  int potValue = analogRead(potPin);
  
  // Map the potentiometer value to a speed (0 to 200 steps per second)
  float speed = map(potValue, 0, 1023, 0, 200);
  stepper.setSpeed(speed);
  
  // Set the target position based on the potentiometer value
  long targetPosition = map(potValue, 0, 1023, 0, maxSteps);
  
  // Move the stepper to the target position at the set speed
  stepper.moveTo(targetPosition);
  stepper.runSpeedToPosition(); // Blocking call to move to target position
  
  // Delay for a short period to allow the stepper to settle
  delay(100);
}
