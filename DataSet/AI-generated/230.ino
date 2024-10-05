// ACI_10K_an_example.ino

const int aciPin = A0; // Define the pin where the ACI is connected
const int resistorValue = 10000; // 10kΩ resistor value in ohms

void setup() {
  Serial.begin(9600); // Initialize serial communication at 9600 baud
}

void loop() {
  int sensorValue = analogRead(aciPin); // Read the analog input
  float voltage = sensorValue * (5.0 / 1023.0); // Convert to voltage (assuming 5V reference)
  
  // Print the results to the Serial Monitor
  Serial.print("Analog Value: ");
  Serial.print(sensorValue);
  Serial.print(" | Voltage: ");
  Serial.print(voltage);
  Serial.println(" V");

  delay(500); // Wait for 500 milliseconds before the next reading
}
