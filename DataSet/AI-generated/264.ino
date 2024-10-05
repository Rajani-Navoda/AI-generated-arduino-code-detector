const int analogPin = A0;      // Pin where the analog sensor is connected
const int numReadings = 10;    // Number of readings for averaging
int readings[numReadings];     // Array to store sensor readings
int readIndex = 0;             // Current reading index
int total = 0;                 // Sum of the readings
int average = 0;               // Average of readings
int mappedValue = 0;           // Variable to store the mapped value
int constrainedValue = 0;      // Variable to store the constrained value

void setup() {
  // Initialize Serial communication
  Serial.begin(9600);

  // Initialize all readings to 0
  for (int i = 0; i < numReadings; i++) {
    readings[i] = 0;
  }
}

void loop() {
  // Subtract the last reading from the total
  total = total - readings[readIndex];

  // Read the analog input from the sensor (value between 0 and 1023)
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

  // Map the average value from 0-1023 to 0-255 (or any desired range)
  mappedValue = map(average, 0, 1023, 0, 255);

  // Constrain the mapped value to a specific range, e.g., 50 to 200
  constrainedValue = constrain(mappedValue, 50, 200);

  // Print the original average, mapped value, and constrained value to Serial
  Serial.print("Average Value: ");
  Serial.print(average);
  Serial.print(" | Mapped Value: ");
  Serial.print(mappedValue);
  Serial.print(" | Constrained Value: ");
  Serial.println(constrainedValue);

  // Add a delay for stability
  delay(500);
}