#include <AccelStepper.h>

// Define motor pins
#define motorPin1 2  // IN1 on the ULN2003 driver
#define motorPin2 3  // IN2 on the ULN2003 driver
#define motorPin3 4  // IN3 on the ULN2003 driver
#define motorPin4 5  // IN4 on the ULN2003 driver

// Define encoder pins
const int encoderPinA = 6;  // Encoder A output
const int encoderPinB = 7;  // Encoder B output

long encoderPosition = 0;  // Track the encoder position
int lastEncoded = 0;  // Stores the last encoder state

// Create an instance of the AccelStepper class using 4 pins
AccelStepper stepper(AccelStepper::FULL4WIRE, motorPin1, motorPin2, motorPin3, motorPin4);

void setup() {
  // Set up motor parameters
  stepper.setMaxSpeed(1000);
  stepper.setAcceleration(500);

  // Set up encoder pins as inputs
  pinMode(encoderPinA, INPUT);
  pinMode(encoderPinB, INPUT);

  // Initialize serial communication for debugging
  Serial.begin(9600);
}

void loop() {
  // Read the current state of encoder pins
  int MSB = digitalRead(encoderPinA);  // Most Significant Bit
  int LSB = digitalRead(encoderPinB);  // Least Significant Bit
  
  int encoded = (MSB << 1) | LSB;  // Combine MSB and LSB to get a 2-bit number
  int sum = (lastEncoded << 2) | encoded;  // Combine current state with the last state

  // Check for changes in the encoder's state and update position accordingly
  if (sum == 0b1101 || sum == 0b0100 || sum == 0b0010 || sum == 0b1011) encoderPosition++;
  if (sum == 0b1110 || sum == 0b0111 || sum == 0b0001 || sum == 0b1000) encoderPosition--;

  lastEncoded = encoded;  // Store this state for the next loop iteration

  // Example motor movement: move forward and backward in steps
  stepper.moveTo(1000);
  stepper.runToPosition();
  delay(1000);
  stepper.moveTo(0);
  stepper.runToPosition();
  delay(1000);

  // Print the current encoder position to the Serial Monitor
  Serial.print("Encoder position: ");
  Serial.println(encoderPosition);
}
