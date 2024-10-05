/*
  Example code for controlling a motor using an H-bridge driver and a potentiometer.
  The code demonstrates two modes:
  1. Position control: The motor moves to a position based on the potentiometer value.
  2. Speed control: The motor speed is controlled based on the potentiometer value.
*/

// Pin definitions
const int potPin = A0;  // Analog input pin for the potentiometer
const int motorPin1 = 9;  // PWM output pin 1 for the H-bridge
const int motorPin2 = 10; // PWM output pin 2 for the H-bridge
const int motorEnablePin = 8; // Enable pin for the H-bridge

// Mode selection (change these variables to switch modes)
bool positionControlMode = true;  // Set to true for position control, false for speed control

void setup() {
  // Initialize serial communication for debugging
  Serial.begin(9600);
  
  // Set motor pins as outputs
  pinMode(motorPin1, OUTPUT);
  pinMode(motorPin2, OUTPUT);
  pinMode(motorEnablePin, OUTPUT);
  
  // Enable the motor driver
  digitalWrite(motorEnablePin, HIGH);
}

void loop() {
  // Read the potentiometer value (0 to 1023)
  int potValue = analogRead(potPin);

  // Convert potentiometer value to a motor control signal
  int motorSpeed = map(potValue, 0, 1023, 0, 255); // Map potentiometer value to PWM range (0-255)
  
  if (positionControlMode) {
    // Position Control Mode
    Serial.println("Position Control Mode");
    positionControl(potValue);
  } else {
    // Speed Control Mode
    Serial.println("Speed Control Mode");
    speedControl(motorSpeed);
  }

  delay(100); // Small delay for debounce
}

// Function to control motor position based on potentiometer value
void positionControl(int potValue) {
  int threshold = 10; // Threshold to consider the motor "in position"
  int targetPosition = map(potValue, 0, 1023, 0, 180); // Target position from potentiometer
  int currentPosition = readMotorPosition(); // Function to read motor's current position

  if (abs(currentPosition - targetPosition) > threshold) {
    if (currentPosition < targetPosition) {
      // Move motor forward
      analogWrite(motorPin1, 150); // PWM value to control speed
      analogWrite(motorPin2, 0);
    } else {
      // Move motor backward
      analogWrite(motorPin1, 0);
      analogWrite(motorPin2, 150); // PWM value to control speed
    }
  } else {
    // Stop motor if within the threshold
    analogWrite(motorPin1, 0);
    analogWrite(motorPin2, 0);
  }
  
  // Debug output
  Serial.print("Target: ");
  Serial.print(targetPosition);
  Serial.print(", Current: ");
  Serial.println(currentPosition);
}

// Function to control motor speed based on potentiometer value
void speedControl(int motorSpeed) {
  int direction = digitalRead(potPin) > 512 ? 1 : 0; // Determine direction based on potentiometer position

  if (direction) {
    // Move motor forward
    analogWrite(motorPin1, motorSpeed);
    analogWrite(motorPin2, 0);
  } else {
    // Move motor backward
    analogWrite(motorPin1, 0);
    analogWrite(motorPin2, motorSpeed);
  }

  // Debug output
  Serial.print("Motor Speed: ");
  Serial.println(motorSpeed);
}

// Placeholder function to read motor position (depends on encoder or sensor)
int readMotorPosition() {
  // Return a mock position value for demo purposes
  return analogRead(A1);  // Assume motor position is being read from another analog input
}
