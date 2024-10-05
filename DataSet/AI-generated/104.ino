// Define the analog pins where the soil moisture sensors are connected
const int soilMoisturePin1 = A0;  // Analog pin for the first soil moisture sensor
const int soilMoisturePin2 = A1;  // Analog pin for the second soil moisture sensor

void setup() {
  // Initialize Serial communication
  Serial.begin(9600);
  
  // Print a message to indicate setup is complete
  Serial.println("Soil Moisture Sensor Test");
}

void loop() {
  // Read the analog values from the soil moisture sensors
  int moistureValue1 = analogRead(soilMoisturePin1);
  int moistureValue2 = analogRead(soilMoisturePin2);
  
  // Print the values to the Serial Monitor
  Serial.print("Soil Moisture Sensor 1: ");
  Serial.print(moistureValue1);
  Serial.print(" | Soil Moisture Sensor 2: ");
  Serial.println(moistureValue2);
  
  // Wait for a second before taking the next reading
  delay(1000);
}
