#include <Wire.h>

// H3LIS331DL I2C address
#define H3LIS331DL_ADDR 0x18

// H3LIS331DL Registers
#define CTRL_REG1 0x20
#define OUT_X_L 0x28
#define OUT_X_H 0x29
#define OUT_Y_L 0x2A
#define OUT_Y_H 0x2B
#define OUT_Z_L 0x2C
#define OUT_Z_H 0x2D

void setup() {
  Serial.begin(9600);
  Wire.begin();

  // Initialize the H3LIS331DL sensor
  Wire.beginTransmission(H3LIS331DL_ADDR);
  Wire.write(CTRL_REG1);
  Wire.write(0x27); // 0x27 is a common configuration for active mode with all axes enabled
  Wire.endTransmission();
}

void loop() {
  int16_t x, y, z;

  // Read X-axis data
  Wire.beginTransmission(H3LIS331DL_ADDR);
  Wire.write(OUT_X_L | 0x80); // Use the auto-increment mode
  Wire.endTransmission();
  Wire.requestFrom(H3LIS331DL_ADDR, 2);
  x = Wire.read();
  x |= Wire.read() << 8;

  // Read Y-axis data
  Wire.beginTransmission(H3LIS331DL_ADDR);
  Wire.write(OUT_Y_L | 0x80); // Use the auto-increment mode
  Wire.endTransmission();
  Wire.requestFrom(H3LIS331DL_ADDR, 2);
  y = Wire.read();
  y |= Wire.read() << 8;

  // Read Z-axis data
  Wire.beginTransmission(H3LIS331DL_ADDR);
  Wire.write(OUT_Z_L | 0x80); // Use the auto-increment mode
  Wire.endTransmission();
  Wire.requestFrom(H3LIS331DL_ADDR, 2);
  z = Wire.read();
  z |= Wire.read() << 8;

  // Print out the values
  Serial.print("X: ");
  Serial.print(x);
  Serial.print(" Y: ");
  Serial.print(y);
  Serial.print(" Z: ");
  Serial.println(z);

  delay(500);
}
