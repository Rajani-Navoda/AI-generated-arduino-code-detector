#include <Wire.h>
#include <Adafruit_Sensor.h>
#include <Adafruit_AHRS.h>
#include <Adafruit_MPU6050.h>
#include <Adafruit_HMC5883_U.h>

// Create instances for the sensors
Adafruit_MPU6050 mpu;
Adafruit_HMC5883_Unified mag;
Adafruit_AHRS ahrs;

void setup() {
  Serial.begin(115200);
  Serial.println("9 DOF AHRS Example");

  // Initialize MPU6050
  if (!mpu.begin()) {
    Serial.println("Failed to find MPU6050 chip");
    while (1);
  }

  // Initialize HMC5883
  if (!mag.begin()) {
    Serial.println("Failed to find HMC5883 chip");
    while (1);
  }

  // Initialize AHRS
  if (!ahrs.begin()) {
    Serial.println("No AHRS detected ... Check your wiring!");
    while (1);
  }

  Serial.println("Sensors initialized.");
}

void loop() {
  // Update sensor readings
  sensors_event_t accel_event, mag_event;
  mpu.getEvent(&accel_event);
  mag.getEvent(&mag_event);

  // Update AHRS with the latest accelerometer and magnetometer data
  ahrs.update(accel_event.acceleration.x, accel_event.acceleration.y, accel_event.acceleration.z,
              mag_event.magnetic.x, mag_event.magnetic.y, mag_event.magnetic.z);

  // Read the Euler angles
  float roll = ahrs.getRoll();
  float pitch = ahrs.getPitch();
  float yaw = ahrs.getYaw();

  // Display angles in Serial Monitor
  Serial.print("Roll: "); Serial.print(roll);
  Serial.print(" Pitch: "); Serial.print(pitch);
  Serial.print(" Yaw: "); Serial.println(yaw);

  delay(100); // Update at 10Hz
}
