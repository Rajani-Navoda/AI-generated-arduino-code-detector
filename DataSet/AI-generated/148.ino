#include <Wire.h>

// H3LIS331DL I2C address
#define H3LIS331DL_ADDRESS 0x18 // Adjust if needed

// Register addresses
#define H3LIS331DL_CTRL_REG1 0x20
#define H3LIS331DL_OUT_X_L 0x28
#define H3LIS331DL_OUT_X_H 0x29
#define H3LIS331DL_OUT_Y_L 0x2A
#define H3LIS331DL_OUT_Y_H 0x2B
#define H3LIS331DL_OUT_Z_L 0x2C
#define H3LIS331DL_OUT_Z_H 0x2D

// Calibration offsets (to be determined)
float xOffset = 0;
float yOffset = 0;
float zOffset = 0;

// Calibration factor (adjust as needed)
const float sensitivity = 0.004; // Sensitivity in g/LSB (check datasheet)

// Initialize the sensor
void setup() {
  Serial.begin(9600);
  Wire.begin();

  // Initialize H3LIS331DL
  Wire.beginTransmission(H3LIS331DL_ADDRESS);
  Wire.write(H3LIS331DL_CTRL_REG1);
  Wire.write(0x57); // Enable all axes, set to normal mode
  Wire.endTransmission();

  // Perform calibration
  calibrateSensor();
}

void loop() {
  // Read and print calibrated values
  float x, y, z;
  readAccelerometer(x, y, z);

  Serial.print("X: ");
  Serial.print(x, 2);
  Serial.print(" g, Y: ");
  Serial.print(y, 2);
  Serial.print(" g, Z: ");
  Serial.print(z, 2);
  Serial.println(" g");

  delay(500);
}

// Function to read raw accelerometer data
void readAccelerometer(float &x, float &y, float &z) {
  Wire.beginTransmission(H3LIS331DL_ADDRESS);
  Wire.write(H3LIS331DL_OUT_X_L | 0x80); // Auto-increment
  Wire.endTransmission();
  Wire.requestFrom(H3LIS331DL_ADDRESS, 6);

  int16_t xRaw = Wire.read() | (Wire.read() << 8);
  int16_t yRaw = Wire.read() | (Wire.read() << 8);
  int16_t zRaw = Wire.read() | (Wire.read() << 8);

  x = (xRaw - xOffset) * sensitivity;
  y = (yRaw - yOffset) * sensitivity;
  z = (zRaw - zOffset) * sensitivity;
}

// Function to calibrate the sensor
void calibrateSensor() {
  long xSum = 0, ySum = 0, zSum = 0;
  const int numSamples = 100;

  Serial.println("Calibrating... Please keep the sensor still.");
  
  for (int i = 0; i < numSamples; i++) {
    float x, y, z;
    readAccelerometer(x, y, z);
    xSum += x;
    ySum += y;
    zSum += z;
    delay(50);
  }

  xOffset = xSum / numSamples;
  yOffset = ySum / numSamples;
  zOffset = zSum / numSamples;

  Serial.println("Calibration complete.");
  Serial.print("X Offset: "); Serial.println(xOffset);
  Serial.print("Y Offset: "); Serial.println(yOffset);
  Serial.print("Z Offset: "); Serial.println(zOffset);
}
