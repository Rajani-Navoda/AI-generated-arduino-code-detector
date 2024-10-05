#include <Wire.h>
#include <Adafruit_Sensor.h>
#include <Adafruit_ADXL345_U.h>

// Create an ADXL345 object
Adafruit_ADXL345_Unified accel = Adafruit_ADXL345_Unified();

void setup() {
  Serial.begin(115200);
  Serial.println("Adafruit ADXL345 Sensor Test");

  // Initialize the accelerometer
  if (!accel.begin()) {
    Serial.println("No ADXL345 detected ... Check your wiring!");
    while (1);
  }

  // Set the range to +-16g
  accel.setRange(ADXL345_RANGE_16_G);
  Serial.print("ADXL345 range set to: ");
  Serial.println(16);
}

void loop() {
  sensors_event_t event;
  accel.getEvent(&event);
  
  // Display acceleration values
  Serial.print("X: "); Serial.print(event.acceleration.x);
  Serial.print(" m/s^2, Y: "); Serial.print(event.acceleration.y);
  Serial.print(" m/s^2, Z: "); Serial.print(event.acceleration.z);
  Serial.println(" m/s^2");

  // Delay to slow down output
  delay(500);
}
