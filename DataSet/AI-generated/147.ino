#include <Wire.h>
#include <Adafruit_Sensor.h>
#include <Adafruit_ADXL345_U.h>

// Create an instance of the ADXL345 sensor
Adafruit_ADXL345_U adxl = Adafruit_ADXL345_U();

void setup() {
  Serial.begin(9600);
  
  // Initialize the ADXL345 sensor
  if (!adxl.begin()) {
    Serial.println("Failed to initialize ADXL345");
    while (1); // Stop the program
  }

  // Set the sensor range (optional)
  adxl.setRange(ADXL345_RANGE_16G); // Set the range to ±16g
}

void loop() {
  sensors_event_t event;
  adxl.getEvent(&event);

  // Print the X, Y, and Z axis acceleration data
  Serial.print("X: ");
  Serial.print(event.acceleration.x);
  Serial.print(" m/s^2, Y: ");
  Serial.print(event.acceleration.y);
  Serial.print(" m/s^2, Z: ");
  Serial.print(event.acceleration.z);
  Serial.println(" m/s^2");

  // Delay to avoid flooding the Serial Monitor
  delay(500);
}
