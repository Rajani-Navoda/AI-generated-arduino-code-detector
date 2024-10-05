#include <MD_MAX72XX.h>
#include <SPI.h>

// Define the number of devices in the chain
#define MAX_DEVICES 1

// Define the hardware type
#define HARDWARE_TYPE MD_MAX72XX::FC16_HW

// Define the pin connections
#define DATA_PIN   D7
#define CLK_PIN    D6
#define CS_PIN     D5

// Create an instance of the MD_MAX72XX class
MD_MAX72XX mx = MD_MAX72XX(HARDWARE_TYPE, DATA_PIN, CLK_PIN, CS_PIN);

void setup() {
  // Initialize the display
  mx.begin();
  
  // Clear the display
  mx.clear();
}

void loop() {
  // Loop through the alphabet
  for (char letter = 'A'; letter <= 'Z'; letter++) {
    // Display each letter
    mx.clear();
    displayChar(letter);
    
    // Wait for a while
    delay(1000);
  }
}

// Function to display a character
void displayChar(char c) {
  // Define the font for the alphabet
  static const uint8_t font[][8] = {
    // Add your 8x8 font data for A-Z here
    // Example: {0x7E, 0x11, 0x11, 0x11, 0x7E, 0x00, 0x00, 0x00}, // A
    // Add data for other characters
  };
  
  // Get the index of the character
  if (c >= 'A' && c <= 'Z') {
    int index = c - 'A';
    // Display the character
    mx.writeFont(font[index]);
  }
}
