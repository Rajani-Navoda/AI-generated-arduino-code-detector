#include <LedControl.h>  // Include the LedControl library

// Pin Definitions for MAX7219 (could be different for other drivers)
#define DATA_IN   4
#define CLK         5
#define LOAD        6
#define MAX_DEVICES 1  // Number of MAX7219 modules in the chain

// Create a LedControl object
LedControl lc = LedControl(DATA_IN, CLK, LOAD, MAX_DEVICES);

void setup() {
  // Initialize the LedControl library
  lc.shutdown(0, false);       // Wake up displays
  lc.setIntensity(0, 8);        // Set brightness level (0 is min, 15 is max)
  lc.clearDisplay(0);           // Clear display register
}

void loop() {
  // Example: Draw a pattern on the dot-matrix display

  // Draw a vertical line
  for (int i = 0; i < 8; i++) {
    lc.setRow(0, i, B11111111);  // Set all columns in row i to ON
    delay(100);                   // Wait for 100 ms
  }
  
  delay(1000);  // Wait for 1 second
  
  // Clear the display
  lc.clearDisplay(0);
  
  // Draw a moving dot
  for (int i = 0; i < 8; i++) {
    lc.setRow(0, i, B00000001);  // Set the rightmost column in row i to ON
    delay(200);                  // Wait for 200 ms
    lc.setRow(0, i, B00000000);  // Turn off the column
  }
  
  delay(1000);  // Wait for 1 second
}
