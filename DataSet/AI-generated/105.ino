// Define the pins
const int motorPin = 9;       // PWM pin connected to the motor driver
const int potPin = A0;        // Analog pin connected to the potentiometer

void setup() {
  // Initialize the motor pin as an output
  pinMode(motorPin, OUTPUT);
  
  // Initialize the Serial communication for debugging
  Serial.begin(9600);
}

void loop() {
  // Read the value from the potentiometer
  int potValue = analogRead(potPin);
  
  // Map the potentiometer value to PWM range (0-255)
  int motorSpeed = map(potValue, 0, 1023, 0, 255);
  
  // Set the motor speed using PWM
  analogWrite(motorPin, motorSpeed);
  
  // Print the potentiometer value and motor speed to the Serial Monitor
  Serial.print("Potentiometer Value: ");
  Serial.print(potValue);
  Serial.print(" | Motor Speed: ");
  Serial.println(motorSpeed);
  
  // Wait a bit before the next reading
  delay(100);
}
