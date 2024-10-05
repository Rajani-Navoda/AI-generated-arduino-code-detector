// Define the analog pin for the MQ-135 sensor
const int MQ135_PIN = A0;

void setup() {
  // Start serial communication at 9600 baud
  Serial.begin(9600);
  Serial.println("MQ-135 Air Quality Sensor Test");
}

void loop() {
  // Read the analog value from the MQ-135 sensor
  int sensorValue = analogRead(MQ135_PIN);
  
  // Convert the sensor value to a voltage
  float voltage = sensorValue * (5.0 / 1023.0);
  
  // Print the sensor value and voltage to the serial monitor
  Serial.print("Sensor Value: ");
  Serial.print(sensorValue);
  Serial.print("\tVoltage: ");
  Serial.println(voltage, 2);  // Print voltage with two decimal places
  
  // Add a small delay to avoid flooding the serial monitor
  delay(1000);
}
