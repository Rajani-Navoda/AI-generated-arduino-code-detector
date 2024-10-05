// Define sensor pins
const int tempSensorPin = A0;  // LM35 temperature sensor connected to A0
const int lightSensorPin = A1; // LDR light sensor connected to A1
const int gasSensorPin = A2;   // MQ-2 gas sensor connected to A2

void setup() {
  // Start serial communication at 9600 baud
  Serial.begin(9600);
  Serial.println("Sensor Data Logging Started");
}

void loop() {
  // Read temperature from LM35 sensor
  int tempValue = analogRead(tempSensorPin);
  // Convert the analog reading to a voltage (0 - 1023 to 0 - 5V)
  float voltage = tempValue * (5.0 / 1023.0);
  // Convert the voltage to temperature in Celsius (LM35: 10mV per degree C)
  float temperatureC = voltage * 100;
  
  // Read light intensity from LDR sensor
  int lightValue = analogRead(lightSensorPin);
  
  // Read gas concentration from MQ-2 sensor
  int gasValue = analogRead(gasSensorPin);

  // Print sensor values to the serial monitor
  Serial.print("Temperature (C): ");
  Serial.print(temperatureC);
  Serial.print("\tLight Intensity: ");
  Serial.print(lightValue);
  Serial.print("\tGas Level: ");
  Serial.println(gasValue);

  // Add a delay between readings
  delay(1000); // 1 second delay
}
