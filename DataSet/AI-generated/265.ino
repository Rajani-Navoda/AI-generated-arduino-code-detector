// Define the pin where the digital sensor is connected
const int sensorPin = 2;

void setup() {
  // Initialize the Serial communication
  Serial.begin(9600);
  
  // Set the sensor pin as an input
  pinMode(sensorPin, INPUT);
}

void loop() {
  // Read the sensor value (inverted logic)
  int sensorValue = digitalRead(sensorPin);
  
  // Invert the signal
  int invertedSignal = !sensorValue;
  
  // Display the sensor status in the Serial Monitor
  if (invertedSignal == HIGH) {
    Serial.println("Sensor is ACTIVE");
  } else {
    Serial.println("Sensor is INACTIVE");
  }
  
  // Delay to avoid flooding the Serial Monitor
  delay(500);
}
