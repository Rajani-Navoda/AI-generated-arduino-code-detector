#include <Wire.h>
#include <Adafruit_Sensor.h>
#include <Adafruit_LSM303_Accel.h>
#include <Adafruit_LSM303_Mag.h>

// Create the accelerometer and magnetometer objects
Adafruit_LSM303_Accel_Unified accel = Adafruit_LSM303_Accel_Unified(30301);
Adafruit_LSM303_Mag_Unified mag = Adafruit_LSM303_Mag_Unified(30302);

// Function to calculate heading
float getHeading(sensors_event_t *magEvent) {
  // Calculate heading in degrees
  float heading = (atan2(magEvent->magnetic.y, magEvent->magnetic.x) * 180) / M_PI;
  // Normalize to 0-360 degrees
  if (heading < 0) {
    heading = 360 + heading;
  }
  return heading;
}

// Function to calculate pitch and roll
void getPitchRoll(sensors_event_t *accelEvent, float *pitch, float *roll) {
  // Calculate pitch and roll
  *pitch = (atan2(accelEvent->acceleration.y, accelEvent->acceleration.z) * 180.0) / M_PI;
  *roll = (atan2(-accelEvent->acceleration.x, sqrt(accelEvent->acceleration.y * accelEvent->acceleration.y + accelEvent->acceleration.z * accelEvent->acceleration.z)) * 180.0) / M_PI;
}

void setup(void) {
  Serial.begin(9600);
  Serial.println("Adafruit 9DOF Pitch Roll Heading Example");

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
}

void loop(void) {
  // Create sensor event objects
  sensors_event_t accelEvent;
  sensors_event_t magEvent;

  // Get the latest accelerometer and magnetometer data
  accel.getEvent(&accelEvent);
  mag.getEvent(&magEvent);

  // Calculate pitch and roll
  float pitch, roll;
  getPitchRoll(&accelEvent, &pitch, &roll);

  // Calculate heading
  float heading = getHeading(&magEvent);

  // Display pitch, roll, and heading
  Serial.print("Pitch: "); Serial.print(pitch); Serial.print(" degrees, ");
  Serial.print("Roll: "); Serial.print(roll); Serial.print(" degrees, ");
  Serial.print("Heading: "); Serial.print(heading); Serial.println(" degrees");

  // Delay before next reading
  delay(500);
}
