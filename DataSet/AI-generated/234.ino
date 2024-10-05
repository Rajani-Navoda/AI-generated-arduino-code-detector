#include <Wire.h>
#include <Adafruit_GFX.h>
#include <Adafruit_SSD1306.h>

// Define the OLED display dimensions
#define SCREEN_WIDTH 128
#define SCREEN_HEIGHT 64

// Create an instance of the display
Adafruit_SSD1306 display(SCREEN_WIDTH, SCREEN_HEIGHT, &Wire, -1); // Adjust the last parameter if using a reset pin

void setup() {
  // Initialize the display
  display.begin(SSD1306_I2C_ADDRESS, 0x3C); // Change the address if needed
  display.clearDisplay(); // Clear the display buffer
  
  // Set text size and color
  display.setTextSize(1); // Change this for different text sizes
  display.setTextColor(WHITE); // Set text color to white

  // Display different string types
  char charArray[] = "Hello from char array!";
  String stringObject = "Hello from String object!";
  const char* constCharPointer = "Hello from const char*!";

  // Print char array
  display.setCursor(0, 0); 
  display.print(charArray);
  
  // Print String object
  display.setCursor(0, 20);
  display.print(stringObject);
  
  // Print const char*
  display.setCursor(0, 40);
  display.print(constCharPointer);

  // Update the display to show the text
  display.display(); 
}

void loop() {
  // Nothing to do here; text is static
}
