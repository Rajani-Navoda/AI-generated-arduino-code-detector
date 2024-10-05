// Define pin numbers
const int pwmPin = 9;   // PWM control pin
const int dirPin = 8;   // Direction control pin

// Define speed and direction
const int motorSpeed = 255; // Speed range from 0 to 255 (PWM duty cycle)
const bool motorForward = true; // true for forward, false for reverse

void setup() {
  // Set pin modes
  pinMode(pwmPin, OUTPUT);
  pinMode(dirPin, OUTPUT);

  // Set initial motor direction
  digitalWrite(dirPin, motorForward ? HIGH : LOW);
}

void loop() {
  // Set motor speed
  analogWrite(pwmPin, motorSpeed); // Speed range from 0 (off) to 255 (full speed)

  // Run motor for 5 seconds
  delay(5000);

  // Stop motor
  analogWrite(pwmPin, 0); // Set speed to 0

  // Reverse motor direction
  digitalWrite(dirPin, !motorForward);

  // Run motor for 5 seconds in reverse
  delay(5000);

  // Stop motor
  analogWrite(pwmPin, 0); // Set speed to 0

  // Wait before repeating
  delay(2000);
}
