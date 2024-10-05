#include <Wire.h>
#include <Adafruit_Sensor.h>
#include <Adafruit_ADXL343_U.h>

Adafruit_ADXL343_Unified accel = Adafruit_ADXL343_Unified(0x53); // Default address

void setup() {
  Serial.begin(115200);
  Serial.println("ADXL343 Offset Calibration Example");

  // Initialize the accelerometer
  if (!accel.begin()) {
    Serial.println("No ADXL343 detected ... Check your wiring!");
    while (1);
  }

  // Read the current accelerometer values
  sensors_event_t event;
  accel.getEvent(&event);
  
  // Display current reading
  Serial.print("Current Reading - X: "); Serial.print(event.acceleration.x);
  Serial.print(", Y: "); Serial.print(event.acceleration.y);
  Serial.print(", Z: "); Serial.print(event.acceleration.z);
  Serial.println(" m/s^2");

  // Calculate offsets to zero the sensor
  int8_t offsetX = round(-event.acceleration.x * 256); // Convert to offset value
  int8_t offsetY = round(-event.acceleration.y * 256); // Convert to offset value
  int8_t offsetZ = round((1.0 - event.acceleration.z) * 256); // Convert to offset value

  // Set the offsets
  accel.setOffset(offsetX, offsetY, offsetZ);
  
  // Print the offsets
  Serial.print("Offsets - X: "); Serial.print(offsetX);
  Serial.print(", Y: "); Serial.print(offsetY);
  Serial.print(", Z: "); Serial.println(offsetZ);
}

void loop() {
  // Periodically read the sensor values
  sensors_event_t event;
  accel.getEvent(&event);

  // Display calibrated values
  Serial.print("Calibrated - X: "); Serial.print(event.acceleration.x);
  Serial.print(", Y: "); Serial.print(event.acceleration.y);
  Serial.print(", Z: "); Serial.print(event.acceleration.z);
  Serial.println(" m/s^2");

  delay(500); // Delay for readability
}
