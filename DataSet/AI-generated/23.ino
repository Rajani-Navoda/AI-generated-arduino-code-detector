/*******************************************************************************
*
* (c) 2021 Copyright A-Vision Software
*
* File description :        Arduino dot-matrix display control example
*
* Created by       :        Arnold Velzel
* Created on       :        08-10-2021
*
*******************************************************************************/

#include <LedControl.h>  // Include the LedControl library for controlling the dot-matrix display

// Pin Definitions for MAX7219
#define DATA_IN   4
#define CLK        5
#define LOAD       6
#define MAX_DEVICES 1  // Number of MAX7219 modules in the chain

// Create a LedControl object
LedControl lc = LedControl(DATA_IN, CLK, LOAD, MAX_DEVICES);

void setup() {
  // Initialize the LedControl library
  lc.shutdown(0, false);       // Wake up the display
  lc.setIntensity(0, 8);        // Set brightness level (0 is minimum, 15 is maximum)
  lc.clearDisplay(0);           // Clear the display
}

void loop() {
  // Example patterns to display on the dot-matrix

  // Draw a vertical line
  for (int i = 0; i < 8; i++) {
    lc.setRow(0, i, B11111111);  // Turn on all columns in row i
    delay(100);                   // Wait for 100 ms
  }
  
  delay(1000);  // Wait for 1 second
  
  // Clear the display
  lc.clearDisplay(0);
  
  // Draw a moving dot
  for (int i = 0; i < 8; i++) {
    lc.setRow(0, i, B00000001);  // Turn on the rightmost column in row i
    delay(200);                  // Wait for 200 ms
    lc.setRow(0, i, B00000000);  // Turn off the column
  }
  
  delay(1000);  // Wait for 1 second
}
