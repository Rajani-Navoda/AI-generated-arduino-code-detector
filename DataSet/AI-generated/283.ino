#include <Wire.h>
#include <Adafruit_Sensor.h>
#include <Adafruit_AHRS.h>

// Create an instance of the AHRS
Adafruit_AHRS ahrs;

// BLE initialization variables
// Include your BLE library and define BLE services/characteristics here

void setup() {
  Serial.begin(115200);
  Serial.println("AHRS Calibration Example");

  // Initialize the AHRS
  if (!ahrs.begin()) {
    Serial.println("No AHRS detected ... Check your wiring!");
    while (1);
  }

  // Set the calibration state (if needed)
  ahrs.setCalibrationEnabled(true);
}

void loop() {
  // Update AHRS readings
  ahrs.update();

  // Read the Euler angles
  float roll = ahrs.getRoll();
  float pitch = ahrs.getPitch();
  float yaw = ahrs.getYaw();

  // Send the angles over BLE (replace with your BLE characteristic)
  // bleCharacteristic.setValue(roll, pitch, yaw);
  
  // Display angles in Serial Monitor
  Serial.print("Roll: "); Serial.print(roll);
  Serial.print(" Pitch: "); Serial.print(pitch);
  Serial.print(" Yaw: "); Serial.println(yaw);

  delay(100); // Update at 10Hz
}
