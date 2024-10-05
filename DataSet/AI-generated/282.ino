#include <Wire.h>
#include <Adafruit_Sensor.h>
#include <Adafruit_ADXL375.h>

// Create an ADXL375 object
Adafruit_ADXL375 accel = Adafruit_ADXL375(0x1D); // Default I2C address

void setup() {
  Serial.begin(115200);
  Serial.println("ADXL375 Sensor Test");

  // Set I2C clock speed to 20KHz
  Wire.setClock(20000); // Set I2C speed to 20KHz

  // Initialize the accelerometer
  if (!accel.begin()) {
    Serial.println("No ADXL375 detected ... Check your wiring!");
    while (1);
  }

  // Set the range to ±16g
  accel.setRange(ADXL375_RANGE_16_G);
  Serial.print("ADXL375 range set to: ");
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
