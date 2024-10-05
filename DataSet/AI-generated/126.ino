volatile int encoderValue = 0;  // Variable to store encoder counts
const int encoderPin = 2;       // Encoder output connected to digital pin 2

const int motorPin1 = 9;        // Motor control pin 1
const int motorPin2 = 10;       // Motor control pin 2
const int motorSpeedPin = 3;    // PWM pin for motor speed control

void setup() {
  // Set up the motor control pins as outputs
  pinMode(motorPin1, OUTPUT);
  pinMode(motorPin2, OUTPUT);
  pinMode(motorSpeedPin, OUTPUT);

  // Set up the encoder pin as an input
  pinMode(encoderPin, INPUT);
  
  // Attach interrupt to the encoder pin
  attachInterrupt(digitalPinToInterrupt(encoderPin), encoderISR, RISING);

  // Initialize serial communication
  Serial.begin(9600);
}

void loop() {
  // Control the motor
  analogWrite(motorSpeedPin, 128);  // Set motor speed (0-255)
  digitalWrite(motorPin1, HIGH);    // Set motor direction
  digitalWrite(motorPin2, LOW);

  // Print the encoder value
  Serial.print("Encoder Value: ");
  Serial.println(encoderValue);
  
  delay(100);  // Delay for readability
}

// Interrupt service routine for encoder
void encoderISR() {
  encoderValue++;  // Increment encoder value on each pulse
}
