// Define the analog sensor pin
const int sensorPin = A0; // Analog pin A0

void setup() {
  // Initialize Serial communication at 9600 baud rate
  Serial.begin(9600);
  Serial.println("Starting Analog Data Logging...");
}

void loop() {
  // Read the analog value from the sensor
  int sensorValue = analogRead(sensorPin);

  // Print the sensor value to the Serial Monitor
  Serial.print("Sensor Value: ");
  Serial.println(sensorValue);

  // Delay to avoid flooding the Serial Monitor
  delay(1000); // 1 second delay
}
