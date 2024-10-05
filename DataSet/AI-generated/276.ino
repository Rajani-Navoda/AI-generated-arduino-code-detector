#include <Wire.h>
#include <Adafruit_Sensor.h>
#include <Adafruit_ADXL343_U.h>

// Create two ADXL343 objects
Adafruit_ADXL343_Unified accel1 = Adafruit_ADXL343_Unified(0x53); // Default address
Adafruit_ADXL343_Unified accel2 = Adafruit_ADXL343_Unified(0x1D); // Alternative address

void setup() {
  Serial.begin(115200);
  Serial.println("ADXL343 Dual Sensor Test");

  // Initialize the first accelerometer (default address)
  if (!accel1.begin()) {
    Serial.println("No ADXL343 #1 detected ... Check your wiring!");
    while (1);
  }

  // Initialize the second accelerometer (alternative address)
  if (!accel2.begin()) {
    Serial.println("No ADXL343 #2 detected ... Check your wiring!");
    while (1);
  }

  // Set range and other configurations as needed
  accel1.setRange(ADXL343_RANGE_4_G);
  accel2.setRange(ADXL343_RANGE_4_G);
}

void loop() {
  sensors_event_t event1, event2;

  // Read data from the first accelerometer
  accel1.getEvent(&event1);
  Serial.print("Sensor 1 - X: "); Serial.print(event1.acceleration.x);
  Serial.print(" Y: "); Serial.print(event1.acceleration.y);
  Serial.print(" Z: "); Serial.print(event1.acceleration.z);
  Serial.println(" m/s^2");

  // Read data from the second accelerometer
  accel2.getEvent(&event2);
  Serial.print("Sensor 2 - X: "); Serial.print(event2.acceleration.x);
  Serial.print(" Y: "); Serial.print(event2.acceleration.y);
  Serial.print(" Z: "); Serial.print(event2.acceleration.z);
  Serial.println(" m/s^2");

  delay(500); // Delay for readability
}
