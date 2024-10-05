// Define analog pins connected to X, Y, and Z axis
const int xPin = A0; // Analog pin for X axis
const int yPin = A1; // Analog pin for Y axis
const int zPin = A2; // Analog pin for Z axis

// Calibration values (These may need adjustment)
const float vcc = 5.0; // Supply voltage to the sensor
const float adcMax = 1023.0; // Maximum value from the ADC (10-bit resolution)

void setup() {
  // Initialize Serial Monitor
  Serial.begin(9600);
}

void loop() {
  // Read raw values from the analog pins
  int xRaw = analogRead(xPin);
  int yRaw = analogRead(yPin);
  int zRaw = analogRead(zPin);

  // Convert the raw readings to voltage
  float xVoltage = (xRaw / adcMax) * vcc;
  float yVoltage = (yRaw / adcMax) * vcc;
  float zVoltage = (zRaw / adcMax) * vcc;

  // Convert the voltage to acceleration (in g's)
  // Assuming the accelerometer is 0.3V/g, adjust as necessary for your sensor
  float xAcceleration = (xVoltage - (vcc / 2)) / 0.3;
  float yAcceleration = (yVoltage - (vcc / 2)) / 0.3;
  float zAcceleration = (zVoltage - (vcc / 2)) / 0.3;

  // Print the results to Serial Monitor
  Serial.print("X: ");
  Serial.print(xAcceleration);
  Serial.print(" g, Y: ");
  Serial.print(yAcceleration);
  Serial.print(" g, Z: ");
  Serial.print(zAcceleration);
  Serial.println(" g");

  // Delay for a short period
  delay(500);
}
