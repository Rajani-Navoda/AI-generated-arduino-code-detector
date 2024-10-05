#include <AccelStepper.h>

// Define the stepper motor
AccelStepper stepper(AccelStepper::DRIVER, 2, 3); // Using pins 2 and 3 for step and direction

// Calibration parameters
const int calibrationDelay = 2000; // Delay between calibration steps (in milliseconds)

// Variables to hold calibrated values
float bestSpeed = 0;
float bestAcceleration = 0;
long bestPosition = 0;

void setup() {
  // Initialize Serial Monitor
  Serial.begin(9600);
  Serial.println("Starting calibration...");

  // Start calibration
  calibrateStepper();
}

void loop() {
  // Calibration is performed in setup, so loop is empty
}

void calibrateStepper() {
  // Define ranges for calibration
  const int minSpeed = 50;
  const int maxSpeed = 300;
  const int minAccel = 20;
  const int maxAccel = 200;
  const int minPos = -1000;
  const int maxPos = 1000;

  float bestPerformance = 0; // To track the best performance observed

  // Test various speeds
  for (float speed = minSpeed; speed <= maxSpeed; speed += 50) {
    stepper.setMaxSpeed(speed);

    // Test various accelerations
    for (float accel = minAccel; accel <= maxAccel; accel += 20) {
      stepper.setAcceleration(accel);

      // Test various target positions
      for (long position = minPos; position <= maxPos; position += 500) {
        stepper.moveTo(position);

        unsigned long startTime = millis();
        while (stepper.distanceToGo() != 0) {
          stepper.run();
        }
        unsigned long elapsedTime = millis() - startTime;

        // Measure performance (you might want to use actual performance metrics)
        float performance = 1.0 / elapsedTime; // Example: inverse of time taken

        // Update best performance and parameters
        if (performance > bestPerformance) {
          bestPerformance = performance;
          bestSpeed = speed;
          bestAcceleration = accel;
          bestPosition = position;
        }

        // Print current settings to Serial Monitor
        Serial.print("Speed: ");
        Serial.print(speed);
        Serial.print(", Acceleration: ");
        Serial.print(accel);
        Serial.print(", Position: ");
        Serial.print(position);
        Serial.print(", Time: ");
        Serial.print(elapsedTime);
        Serial.println(" ms");
        
        delay(calibrationDelay); // Delay between tests
      }
    }
  }

  // Print the best parameters to Serial Monitor
  Serial.println("\nBest Parameters:");
  Serial.print("Best Speed: ");
  Serial.println(bestSpeed);
  Serial.print("Best Acceleration: ");
  Serial.println(bestAcceleration);
  Serial.print("Best Position: ");
  Serial.println(bestPosition);
  
  // Output recommendations for `ADXL335.h` or equivalent configuration
  Serial.println("\nUpdate your configuration file with these values.");
  Serial.print("#define MAX_SPEED ");
  Serial.println(bestSpeed);
  Serial.print("#define ACCELERATION ");
  Serial.println(bestAcceleration);
}
