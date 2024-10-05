#include <Wire.h>
#include <Adafruit_Sensor.h>
#include <Adafruit_ADXL343_U.h>

// Create an ADXL343 object
Adafruit_ADXL343_Unified accel = Adafruit_ADXL343_Unified();

volatile bool motionDetected = false;

void setup() {
  Serial.begin(115200);
  Serial.println("Adafruit ADXL343 Interrupts Example");

  // Initialize the accelerometer
  if (!accel.begin()) {
    Serial.println("No ADXL343 detected ... Check your wiring!");
    while (1);
  }

  // Set the range to ±4g
  accel.setRange(ADXL343_RANGE_4_G);

  // Set up the interrupt
  accel.setTap(ADXL343_TAP_SAMPLES_8, 100, 100);
  accel.setInt1Threshold(0x1F);  // Motion threshold
  accel.setInt1Duration(0x0A);    // Duration threshold

  // Enable the interrupts
  accel.setInterrupts(ADXL343_INT1_DATA_READY | ADXL343_INT1_MOTION);
  
  // Attach the interrupt to the digital pin
  attachInterrupt(digitalPinToInterrupt(2), motionISR, RISING);
}

void loop() {
  // Check if motion was detected
  if (motionDetected) {
    motionDetected = false; // Reset the flag

    // Read acceleration data
    sensors_event_t event;
    accel.getEvent(&event);
    
    // Display acceleration values
    Serial.print("X: "); Serial.print(event.acceleration.x);
    Serial.print(" m/s^2, Y: "); Serial.print(event.acceleration.y);
    Serial.print(" m/s^2, Z: "); Serial.print(event.acceleration.z);
    Serial.println(" m/s^2");
  }
}

// Interrupt Service Routine
void motionISR() {
  motionDetected = true;
}
