#include <Wire.h>
#include <ACROBOTIC_SSD1306.h>

static unsigned char const LOGO[] PROGMEM = {
    // Add your logo bitmap data here
};

void setup() {
  Wire.begin();
  oled.init();                      // Initialize the SSD1306 OLED display
  oled.clearDisplay();              // Clear the screen
  oled.drawBitmap(LOGO, 1024);      // Draw the logo
  oled.setTextXY(0, 1);              // Set cursor position
  oled.putString("Brightness Control");
}

unsigned char brightness = 0;

void loop() {
  oled.setBrightness(brightness);    // Set the brightness
  oled.setPageMode();
  oled.setTextXY(1, 10);
  oled.putNumber(brightness);         // Display the current brightness value
  delay(500);

  // Increment brightness value
  if (brightness < 255) {
    brightness += 51;                 // Increase brightness
  } else {
    brightness = 0;                   // Reset brightness after max
  }
}