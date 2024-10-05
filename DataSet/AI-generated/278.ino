#include <Wire.h>
#include <Adafruit_Sensor.h>
#include <Adafruit_ADXL343_U.h>

// Create an ADXL343 object
Adafruit_ADXL343_Unified accel = Adafruit_ADXL343_Unified(0x53); // Default I2C address

void setup() {
  Serial.begin(115200);
  Serial.println("Adafruit ADXL343 Sensor Test");

  // Initialize the accelerometer
  if (!accel.begin()) {
    Serial.println("No ADXL343 detected ... Check your wiring!");
    while (1);
  }

  // Set the range to ±4g
  accel.setRange(ADXL343_RANGE_4_G);
  Serial.print("ADXL343 range set to: ");
  Serial.println(4);
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
