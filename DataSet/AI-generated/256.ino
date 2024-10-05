#include <Arduino.h>

const int outputPin = 9; // Output pin for the sine wave signal
const int sampleRate = 1000; // Sample rate in Hz
const int amplitude = 127; // Amplitude of the sine wave (0-255 for 8-bit)
const int offset = 128; // Offset to center the wave (0-255 for 8-bit)

// Precomputed sine wave values
const int sineTable[360] = {
  // Values from 0 to 360 degrees
  128, 133, 138, 143, 148, 153, 157, 162, 167, 171, 176, 180, 184, 188, 192, 196,
  199, 203, 207, 210, 214, 217, 220, 222, 225, 227, 230, 232, 233, 235, 236, 237,
  238, 239, 239, 240, 240, 240, 239, 239, 238, 237, 236, 235, 233, 232, 230, 227,
  225, 222, 220, 217, 214, 210, 207, 203, 199, 196, 192, 188, 184, 180, 176, 171,
  167, 162, 157, 153, 148, 143, 138, 133, 128, 123, 118, 113, 108, 103, 99, 94,
  90, 86, 81, 76, 72, 67, 63, 58, 53, 48, 44, 39, 35, 30, 26, 21,
  16, 12, 7, 3, 0, -3, -7, -12, -16, -21, -26, -30, -35, -39, -44, -48,
  -53, -58, -63, -67, -72, -76, -81, -86, -90, -94, -99, -103, -108, -113, -118, -123,
  -128, -133, -138, -143, -148, -153, -157, -162, -167, -171, -176, -180, -184, -188,
  -192, -196, -199, -203, -207, -210, -214, -217, -220, -222, -225, -227, -230, -232,
  -233, -235, -236, -237, -238, -239, -239, -240, -240, -240, -239, -239, -238, -237,
  -236, -235, -233, -232, -230, -227, -225, -222, -220, -217, -214, -210, -207, -203,
  -199, -196, -192, -188, -184, -180, -176, -171, -167, -162, -157, -153, -148, -143,
  -138, -133, -128
};

void setup() {
  pinMode(outputPin, OUTPUT); // Set the output pin as an output
}

void loop() {
  for (int i = 0; i < 360; i++) {
    int sineValue = sineTable[i]; // Get the sine value from the table
    int pwmValue = offset + (amplitude * sineValue / 127); // Scale to 0-255
    analogWrite(outputPin, pwmValue); // Output the PWM value
    delayMicroseconds(1000000 / sampleRate); // Wait for the sample rate
  }
}
