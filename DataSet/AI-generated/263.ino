
const int analogPin = A0;   // Pin where the analog sensor is connected
int sensorValue = 0;        // Variable to store the analog sensor value
int constrainedValue = 0;   // Variable to store the constrained value

void setup() {
  // Initialize the Serial communication
  Serial.begin(9600);
}

void loop() {
  // Read the analog input from the sensor (value between 0 and 1023)
  sensorValue = analogRead(analogPin);

  // Constrain the sensor value between 100 and 900
  constrainedValue = constrain(sensorValue, 100, 900);

  // Print the original and constrained values to the Serial Monitor
  Serial.print("Original Value: ");
  Serial.print(sensorValue);
  Serial.print(" | Constrained Value: ");
  Serial.println(constrainedValue);

  // Add a delay for stability
  delay(500);
}