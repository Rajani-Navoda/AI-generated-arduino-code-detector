#include <Wire.h>
#include <Adafruit_GFX.h>
#include <Adafruit_SSD1306.h>

// Define OLED display parameters
#define SCREEN_WIDTH 128
#define SCREEN_HEIGHT 64

// Define the reset pin for the OLED (for most displays, this can be -1 if not connected)
#define OLED_RESET    -1
Adafruit_SSD1306 display(SCREEN_WIDTH, SCREEN_HEIGHT, &Wire, OLED_RESET);

void setup() {
  // Start serial communication
  Serial.begin(9600);
  Serial.println("OLED Display Example");

  // Initialize the display
  if (!display.begin(SSD1306_I2C_ADDRESS, OLED_RESET)) {
    Serial.println(F("SSD1306 allocation failed"));
    for (;;);  // Don't proceed, loop forever
  }

  // Clear the display buffer
  display.clearDisplay();
  
  // Set the text size and color
  display.setTextSize(1);      // Normal 1:1 pixel scale
  display.setTextColor(SSD1306_WHITE); // Draw white text

  // Display a message on the screen
  display.setCursor(0, 0);     // Start at top-left corner
  display.println("Hello, World!");
  
  // Show the DFRobot name
  display.setCursor(0, 16);
  display.println("DFRobot Shield");

  // Show a simple counter
  display.setCursor(0, 32);
  display.println("Counter:");
  display.display();            // Send buffer to the display
  delay(2000);
}

void loop() {
  // Clear the portion of the screen where the counter will be displayed
  display.fillRect(70, 32, 50, 8, SSD1306_BLACK);
  
  // Display a changing number on the screen
  static int counter = 0;
  display.setCursor(70, 32);   // Position the cursor for the counter
  display.print(counter);      // Print the counter value
  display.display();           // Refresh the display
  counter++;

  // Small delay to slow down the counter
  delay(500);
}
