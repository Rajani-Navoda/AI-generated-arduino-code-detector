/*
  Author: Your Name
  Description: Display a bitmap image on an OLED display
*/

#include <Wire.h>
#include <ACROBOTIC_SSD1306.h>

// Bitmap data for the image
static unsigned char const myBitmap[] PROGMEM = {
  // Your bitmap data here (replace with actual hex values)
  0x00, 0x00, 0x00, 0x00, // Example data (should be replaced)
  0xFF, 0xFF, 0xFF, 0xFF, // More data...
  // Add more rows as needed...
};

void setup() {
  Wire.begin();
  oled.init();                     // Initialize SSD1306 OLED display
  oled.clearDisplay();             // Clear the screen
  oled.drawBitmap(myBitmap, 128, 64); // Width and height of the image
  oled.display();                  // Update the display to show the image
}

void loop() {
  // Nothing to do here for a static image
}
