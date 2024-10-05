const int analogPin = A0;  // Pin where the analog sensor is connected
const int numReadings = 10; // Number of readings for averaging
int readings[numReadings];   // Array to store sensor readings
int readIndex = 0;           // Current reading index
int total = 0;               // Sum of the readings
int average = 0;             // Average of readings

void setup() {
  // Initialize the Serial communication
  Serial.begin(9600);
  
  // Initialize all the readings to 0
  for (int i = 0; i < numReadings; i++) {
    readings[i] = 0;
  }
}

void loop() {
  // Subtract the last reading from the total
  total = total - readings[readIndex];

  // Read the analog input from the sensor
  readings[readIndex] = analogRead(analogPin);

  // Add the new reading to the total
  total = total + readings[readIndex];

  // Advance to the next position in the array
  readIndex = readIndex + 1;

  // If the array is full, wrap around to the beginning
  if (readIndex >= numReadings) {
    readIndex = 0;
  }

  // Calculate the average of the readings
  average = total / numReadings;

  // Print the average value to the Serial Monitor
  Serial.print("Average analog value: ");
  Serial.println(average);

  // Add a delay for stability
  delay(500);
}