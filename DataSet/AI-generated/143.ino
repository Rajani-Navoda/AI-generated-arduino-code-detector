#include <AccelStepper.h>

AccelStepper stepper(AccelStepper::DRIVER, 2, 3); // Using pins 2 and 3 for step and direction

const int minSpeed = 50;    // Minimum speed in steps per second
const int maxSpeed = 200;   // Maximum speed in steps per second
const int minAccel = 20;    // Minimum acceleration in steps per second^2
const int maxAccel = 100;   // Maximum acceleration in steps per second^2
const int minPos = -1000;   // Minimum position
const int maxPos = 1000;    // Maximum position

void setup() {
  // Initialize stepper with default settings
  stepper.setMaxSpeed(maxSpeed);
  stepper.setAcceleration(maxAccel);

  // Set initial random target position, speed, and acceleration
  setRandomTarget();
}

void loop() {
  // Run the stepper to its target position
  stepper.run();

  // Check if the motor has reached the target position
  if (stepper.distanceToGo() == 0) {
    // Change speed, acceleration, and position at random intervals
    delay(random(1000, 3000)); // Wait for a random interval between 1 and 3 seconds

    setRandomTarget(); // Set a new random target position, speed, and acceleration
  }
}

void setRandomTarget() {
  // Set a random target position
  long targetPosition = random(minPos, maxPos);
  stepper.moveTo(targetPosition);

  // Set a random speed
  float speed = random(minSpeed, maxSpeed);
  stepper.setSpeed(speed);

  // Set a random acceleration
  float acceleration = random(minAccel, maxAccel);
  stepper.setAcceleration(acceleration);
}
