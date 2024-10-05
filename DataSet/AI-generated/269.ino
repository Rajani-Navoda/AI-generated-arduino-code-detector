// Define the pin where the analog sensor is connected
const int analogSensorPin = A0;

void setup() {
  // Initialize Serial communication
  Serial.begin(9600);
}

void loop() {
  // Read the analog sensor value (range: 0 - 1023)
  int analogValue = analogRead(analogSensorPin);
  
  // Display the analog value in the Serial Monitor
  Serial.print("Analog sensor value: ");
  Serial.println(analogValue);
  
  // Delay to slow down the output rate
  delay(500);
}

