#include <Wire.h>
#include <Adafruit_Sensor.h>
#include <Adafruit_ADXL343_U.h>

// Create an ADXL343 object
Adafruit_ADXL343_Unified accel = Adafruit_ADXL343_Unified(0x53); // Default I2C address

void setup() {
  Serial.begin(115200);
  Serial.println("ADXL343 Single Tap Detection Example");

  // Initialize the accelerometer
  if (!accel.begin()) {
    Serial.println("No ADXL343 detected ... Check your wiring!");
    while (1);
  }

  // Set the range to ±4g
  accel.setRange(ADXL343_RANGE_4_G);
  
  // Configure the tap detection
  accel.setTap(ADXL343_TAP_SAMPLES_8, 100, 100); // 8 samples, thresholds for tap detection
}

void loop() {
  // Check for tap events
  if (accel.tapped()) {
    Serial.println("Single Tap Detected!");
  }
  
  delay(100); // Small delay for readability
}
