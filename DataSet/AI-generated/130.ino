/*
  Example of motor control using an H-bridge driver and a potentiometer
  For position following mode and speed holding mode
*/

// Define pin numbers
const int potPin = A0;  // Analog input for the potentiometer
const int motorPin1 = 9;  // Motor driver pin 1
const int motorPin2 = 10; // Motor driver pin 2
const int enablePin = 8;  // Motor driver enable pin

// Control mode settings
bool positionMode = true; // Set to true for position mode, false for speed mode

void setup() {
  Serial.begin(9600);  // Start serial communication for debugging
  pinMode(motorPin1, OUTPUT); // Set motor control pins as outputs
  pinMode(motorPin2, OUTPUT);
  pinMode(enablePin, OUTPUT);
  
  digitalWrite(enablePin, HIGH);  // Enable the motor driver
}

void loop() {
  int potValue = analogRead(potPin); // Read potentiometer value (0 to 1023)
  int motorSpeed = map(potValue, 0, 1023, 0, 255); // Map pot value to motor speed (0-255)

  if (positionMode) {
    controlPosition(potValue); // Call position control function
  } else {
    controlSpeed(motorSpeed); // Call speed control function
  }
  
  delay(100);  // Small delay to debounce and prevent rapid switching
}

// Function to control motor position based on potentiometer value
void controlPosition(int potValue) {
  int threshold = 10;  // Threshold for position accuracy
  int targetPosition = map(potValue, 0, 1023, 0, 180); // Map pot value to target position
  int currentPosition = readMotorPosition(); // Function to read motor position

  if (abs(currentPosition - targetPosition) > threshold) {
    if (currentPosition < targetPosition) {
      analogWrite(motorPin1, 150); // Move motor forward
      analogWrite(motorPin2, 0);
    } else {
      analogWrite(motorPin1, 0);
      analogWrite(motorPin2, 150); // Move motor backward
    }
  } else {
    analogWrite(motorPin1, 0); // Stop the motor
    analogWrite(motorPin2, 0);
  }

  // Print target and current positions for debugging
  Serial.print("Target Position: ");
  Serial.print(targetPosition);
  Serial.print(", Current Position: ");
  Serial.println(currentPosition);
}

// Function to control motor speed based on potentiometer value
void controlSpeed(int motorSpeed) {
  int direction = digitalRead(potPin) > 512 ? 1 : 0; // Determine motor direction

  if (direction) {
    analogWrite(motorPin1, motorSpeed); // Move motor forward
    analogWrite(motorPin2, 0);
  } else {
    analogWrite(motorPin1, 0);
    analogWrite(motorPin2, motorSpeed); // Move motor backward
  }

  // Print motor speed for debugging
  Serial.print("Motor Speed: ");
  Serial.println(motorSpeed);
}

// Placeholder function to read motor position (depends on encoder or sensor)
int readMotorPosition() {
  // Simulated position reading; replace with actual sensor reading code
  return analogRead(A1); // Example of reading from another analog input
}
