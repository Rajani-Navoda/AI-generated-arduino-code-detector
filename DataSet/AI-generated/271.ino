#include <Wire.h>
#include <Adafruit_Sensor.h>
#include <Adafruit_LSM303_Accel.h>
#include <Adafruit_LSM303_Mag.h>
#include <Adafruit_L3GD20_U.h>

// Create sensor objects
Adafruit_LSM303_Accel_Unified accel = Adafruit_LSM303_Accel_Unified(30301);
Adafruit_LSM303_Mag_Unified mag = Adafruit_LSM303_Mag_Unified(30302);
Adafruit_L3GD20_Unified gyro = Adafruit_L3GD20_Unified(20);

// Sensor event variables
sensors_event_t accel_event;
sensors_event_t mag_event;
sensors_event_t gyro_event;

void setup(void) {
  Serial.begin(115200);
  Serial.println("Adafruit 9DOF AHRS Example");

  // Initialize accelerometer
  if (!accel.begin()) {
    Serial.println("No LSM303 detected ... Check your wiring!");
    while (1);
  }

  // Initialize magnetometer
  if (!mag.begin()) {
    Serial.println("No LSM303 detected ... Check your wiring!");
    while (1);
  }

  // Initialize gyroscope
  if (!gyro.begin()) {
    Serial.println("No L3GD20 detected ... Check your wiring!");
    while (1);
  }
}

void loop(void) {
  // Get sensor events
  accel.getEvent(&accel_event);
  mag.getEvent(&mag_event);
  gyro.getEvent(&gyro_event);

  // Display sensor data
  Serial.print("Accelerometer: X: "); Serial.print(accel_event.acceleration.x);
  Serial.print(" Y: "); Serial.print(accel_event.acceleration.y);
  Serial.print(" Z: "); Serial.println(accel_event.acceleration.z);

  Serial.print("Magnetometer: X: "); Serial.print(mag_event.magnetic.x);
  Serial.print(" Y: "); Serial.print(mag_event.magnetic.y);
  Serial.print(" Z: "); Serial.println(mag_event.magnetic.z);

  Serial.print("Gyroscope: X: "); Serial.print(gyro_event.gyro.x);
  Serial.print(" Y: "); Serial.print(gyro_event.gyro.y);
  Serial.print(" Z: "); Serial.println(gyro_event.gyro.z);

  delay(500);
}
