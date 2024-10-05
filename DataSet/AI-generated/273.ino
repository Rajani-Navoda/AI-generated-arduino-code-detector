#include <Wire.h>
#include <Adafruit_Sensor.h>
#include <Adafruit_LSM303_Accel.h>
#include <Adafruit_LSM303_Mag.h>
#include <Adafruit_L3GD20_U.h>

// Create sensor objects
Adafruit_LSM303_Accel_Unified accel = Adafruit_LSM303_Accel_Unified(30301);
Adafruit_LSM303_Mag_Unified mag = Adafruit_LSM303_Mag_Unified(30302);
Adafruit_L3GD20_Unified gyro = Adafruit_L3GD20_Unified(20);

void setup() {
  Serial.begin(115200);
  Serial.println("Adafruit 9DOF Tester");

  // Initialize the accelerometer
  if (!accel.begin()) {
    Serial.println("No LSM303 accelerometer detected!");
    while (1);
  }

  // Initialize the magnetometer
  if (!mag.begin()) {
    Serial.println("No LSM303 magnetometer detected!");
    while (1);
  }

  // Initialize the gyroscope
  if (!gyro.begin()) {
    Serial.println("No L3GD20 gyroscope detected!");
    while (1);
  }
}

void loop() {
  // Read accelerometer data
  sensors_event_t accelEvent;
  accel.getEvent(&accelEvent);
  
  // Read magnetometer data
  sensors_event_t magEvent;
  mag.getEvent(&magEvent);
  
  // Read gyroscope data
  sensors_event_t gyroEvent;
  gyro.getEvent(&gyroEvent);

  // Display accelerometer values
  Serial.print("Accel X: "); Serial.print(accelEvent.acceleration.x);
  Serial.print(", Y: "); Serial.print(accelEvent.acceleration.y);
  Serial.print(", Z: "); Serial.print(accelEvent.acceleration.z);
  
  // Display magnetometer values
  Serial.print(" | Mag X: "); Serial.print(magEvent.magnetic.x);
  Serial.print(", Y: "); Serial.print(magEvent.magnetic.y);
  Serial.print(", Z: "); Serial.print(magEvent.magnetic.z);
  
  // Display gyroscope values
  Serial.print(" | Gyro X: "); Serial.print(gyroEvent.gyro.x);
  Serial.print(", Y: "); Serial.print(gyroEvent.gyro.y);
  Serial.print(", Z: "); Serial.print(gyroEvent.gyro.z);
  
  Serial.println();

  // Delay to slow down output
  delay(500);
}
