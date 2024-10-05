#include <Adafruit_GFX.h>
#include <Adafruit_LEDBackpack.h>
#include <Adafruit_NeoPixel.h>

// Define the pin for the 8x8 dot-matrix display
#define MATRIX_I2C_ADDR 0x70  // I2C address for the dot-matrix display

// Define the pin for the WS2812 LEDs
#define LED_PIN 6
#define NUM_LEDS 16  // Number of WS2812 LEDs

// Create instances of the libraries
Adafruit_BitmapMatrix matrix = Adafruit_BitmapMatrix(MATRIX_I2C_ADDR);
Adafruit_NeoPixel strip = Adafruit_NeoPixel(NUM_LEDS, LED_PIN, NEO_GRB + NEO_KHZ800);

void setup() {
  // Initialize the dot-matrix display
  matrix.begin();
  matrix.setRotation(1); // Set rotation if needed
  
  // Initialize the WS2812 LEDs
  strip.begin();
  strip.show();  // Initialize all pixels to 'off'
}

void loop() {
  // Draw a simple pattern on the dot-matrix
  matrix.clear();
  matrix.drawPixel(0, 0, LED_ON);
  matrix.drawPixel(1, 1, LED_ON);
  matrix.drawPixel(2, 2, LED_ON);
  matrix.drawPixel(3, 3, LED_ON);
  matrix.writeDisplay();
  
  // Set colors for WS2812 LEDs
  for(int i = 0; i < NUM_LEDS; i++) {
    strip.setPixelColor(i, strip.Color(255, 0, 0));  // Red color
  }
  strip.show();  // Update the LEDs with the new colors
  
  delay(1000); // Wait for 1 second
  
  // Change colors for WS2812 LEDs
  for(int i = 0; i < NUM_LEDS; i++) {
    strip.setPixelColor(i, strip.Color(0, 255, 0));  // Green color
  }
  strip.show();  // Update the LEDs with the new colors
  
  delay(1000); // Wait for 1 second
}
