#include <A4990MotorShield.h>

// Create an instance of the A4990MotorShield class
A4990MotorShield md;

// Motor speed settings
const int motorSpeed = 200;  // Speed range: 0 to 400

void setup() {
  // Initialize the serial communication
  Serial.begin(9600);

  // Initialize the motor shield
  md.init();
  
  // Set up the user LED pin (usually pin 13 on many Arduino boards)
  pinMode(LED_BUILTIN, OUTPUT);
}

void loop() {
  // Drive both motors forward
  Serial.println("Driving motors forward");
  driveMotors(motorSpeed);

  // Delay to allow motors to run
  delay(2000);

  // Check for faults
  if (md.getFault()) {
    handleFault();
    return;  // Exit loop if fault is detected
  }

  // Drive both motors backward
  Serial.println("Driving motors backward");
  driveMotors(-motorSpeed);

  // Delay to allow motors to run
  delay(2000);

  // Check for faults
  if (md.getFault()) {
    handleFault();
    return;  // Exit loop if fault is detected
  }
}

// Function to drive motors at a given speed
void driveMotors(int speed) {
  md.setM1Speed(speed);
  md.setM2Speed(speed);

  // Control the LED based on the motor speed direction
  if (speed > 0) {
    digitalWrite(LED_BUILTIN, HIGH);  // LED on for forward
  } else {
    digitalWrite(LED_BUILTIN, LOW);   // LED off for backward
  }
}

// Function to handle motor faults
void handleFault() {
  // Stop both motors
  md.setM1Speed(0);
  md.setM2Speed(0);

  // Report fault to the serial monitor
  Serial.println("Fault detected! Motors stopped.");
}
