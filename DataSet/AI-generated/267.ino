// Define the pin where the analog sensor is connected
const int sensorPin = A0;

// Variables for sensor values
int sensorValue = 0;
int mappedValue = 0;

void setup() {
  // Initialize the Serial communication
  Serial.begin(9600);
}

void loop() {
  // Read the analog sensor value (range: 0 - 1023)
  sensorValue = analogRead(sensorPin);
  
  // Map the sensor value to a desired range (e.g., 0 - 100)
  mappedValue = map(sensorValue, 0, 1023, 0, 100);
  
  // Constrain the mapped value to a specific range (e.g., 10 - 90)
  mappedValue = constrain(mappedValue, 10, 90);
  
  // Display the original and mapped/constrained sensor values in the Serial Monitor
  Serial.print("Raw sensor value: ");
  Serial.print(sensorValue);
  Serial.print("\tMapped & Constrained value: ");
  Serial.println(mappedValue);
  
  // Delay to slow down the output rate
  delay(500);
}
