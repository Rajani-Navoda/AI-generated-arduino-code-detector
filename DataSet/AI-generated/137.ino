#include <AccelStepper.h>
#include <AFMotor.h>

// Define the stepper motor using the Adafruit Motor Shield
AF_Stepper motor(200, 1); // 200 steps per revolution, Motor port #1 (M1 and M2)

// Define a subclass of AccelStepper to use with the Adafruit Motor Shield
class AFMotorStepper : public AccelStepper {
public:
  AFMotorStepper() : AccelStepper() {}

  void setPin(uint8_t pin) {
    motor.setSpeed(pin);
  }

  void setMaxSpeed(float speed) {
    motor.setSpeed(speed);
  }

  void setAcceleration(float acceleration) {
    // Acceleration is not supported in this implementation
  }

  void run() {
    motor.step(1); // Run the motor one step
  }

  void moveTo(long absolute) {
    // For simplicity, moveTo is not implemented in this example
  }

  long currentPosition() {
    return 0; // Placeholder for current position
  }

  long distanceToGo() {
    return 0; // Placeholder for distance to go
  }
};

// Create an instance of the custom stepper class
AFMotorStepper stepper;

void setup() {
  // Set speed (steps per second)
  stepper.setMaxSpeed(100.0);
  stepper.setSpeed(50.0); // Constant speed
}

void loop() {
  // Continuously run the motor at a constant speed
  stepper.run();
}
