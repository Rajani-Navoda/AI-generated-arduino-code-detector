// Define the pin where the analog sensor is connected
const int sensorPin = A0;

// Define the number of readings to smooth the signal
const int numReadings = 10;

// Array to store sensor readings
int readings[numReadings];

// Index of the current reading
int readIndex = 0;

// Variable to store the total of readings
int total = 0;

// Variable to store the average of readings
int average = 0;

void setup() {
  // Initialize the Serial communication
  Serial.begin(9600);

  // Initialize all readings to 0
  for (int i = 0; i < numReadings; i++) {
    readings[i] = 0;
  }
}

void loop() {
  // Subtract the last reading from the total
  total = total - readings[readIndex];

  // Read the current analog sensor value
  readings[readIndex] = analogRead(sensorPin);

  // Add the new reading to the total
  total = total + readings[readIndex];

  // Advance to the next index
  readIndex++;

  // If we're at the end of the array, wrap around to the beginning
  if (readIndex >= numReadings) {
    readIndex = 0;
  }

  // Calculate the average of the readings
  average = total / numReadings;

  // Display the smoothed sensor value in the Serial Monitor
  Serial.print("Smoothed sensor value: ");
  Serial.println(average);

  // Delay to slow down the output rate
  delay(100);
}
