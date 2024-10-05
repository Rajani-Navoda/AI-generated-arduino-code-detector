#include <Wire.h>
#include <Adafruit_Sensor.h>
#include <Adafruit_ADXL345_U.h>

// Create an instance of the ADXL345 sensor
Adafruit_ADXL345_U adxl = Adafruit_ADXL345_U();

void setup() {
  Serial.begin(9600);
  
  // Initialize the ADXL345 sensor
  if (!adxl.begin()) {
    Serial.println("Failed to initialize ADXL345");
    while (1);
  }

  // Set the sensor to FIFO mode and configure settings
  adxl.setRange(ADXL345_RANGE_16G); // Set the range to 16G
  adxl.setDataRate(ADXL345_DATARATE_100HZ); // Set data rate to 100 Hz

  // Configure FIFO mode
  adxl.writeRegister(ADXL345_FIFO_CTL, ADXL345_FIFO_MODE_FIFO | ADXL345_FIFO_SAMPLES_33);
}

void loop() {
  // Read FIFO data
  int16_t x, y, z;
  int numSamples = 0;

  // Read samples from FIFO
  while (adxl.getFIFOAvailable()) {
    // Read data from FIFO
    adxl.read();
    x = adxl.getX();
    y = adxl.getY();
    z = adxl.getZ();
    
    // Print the data
    Serial.print("X: "); Serial.print(x); Serial.print(" ");
    Serial.print("Y: "); Serial.print(y); Serial.print(" ");
    Serial.print("Z: "); Serial.println(z);

    numSamples++;
    if (numSamples >= 33) break; // Stop after reading 33 samples
  }

  // Delay to avoid flooding the Serial Monitor
  delay(1000);
}
