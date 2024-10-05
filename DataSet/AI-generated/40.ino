/*
  This example demonstrates how to combine different colors on a WS2812 RGB LED strip.
  The strip will cycle through various colors and combinations to test the LEDs.
  
  Ensure you have the Adafruit NeoPixel library installed for this example to work.
*/

#include <Adafruit_NeoPixel.h>

#define LED_PIN    6    // Pin connected to the data input of the WS2812 strip
#define NUM_LEDS   30   // Number of LEDs in the strip (adjust this based on your strip)

// Create an instance of the Adafruit_NeoPixel class
Adafruit_NeoPixel strip = Adafruit_NeoPixel(NUM_LEDS, LED_PIN, NEO_GRB + NEO_KHZ800);

void setup() {
  strip.begin();  // Initialize the strip
  strip.show();   // Initialize all pixels to 'off'
}

void loop() {
  // Cycle through colors
  colorWipe(strip.Color(255, 0, 0), 50); // Red
  colorWipe(strip.Color(0, 255, 0), 50); // Green
  colorWipe(strip.Color(0, 0, 255), 50); // Blue
  
  colorWipe(strip.Color(255, 255, 0), 50); // Yellow
  colorWipe(strip.Color(0, 255, 255), 50); // Cyan
  colorWipe(strip.Color(255, 0, 255), 50); // Magenta

  // Combine all colors in a rainbow cycle
  rainbowCycle(20);
}

// Fill the entire strip with a single color
void colorWipe(uint32_t color, int wait) {
  for(int i=0; i<strip.numPixels(); i++) {
    strip.setPixelColor(i, color);
    strip.show();
    delay(wait);
  }
}

// Display a rainbow of colors across the entire strip
void rainbowCycle(int wait) {
  int i, j;
  for(j=0; j<256; j++) {
    for(i=0; i<strip.numPixels(); i++) {
      strip.setPixelColor(i, Wheel((i+j) & 255));
    }
    strip.show();
    delay(wait);
  }
}

// Generate a color wheel value
uint32_t Wheel(byte WheelPos) {
  WheelPos = 255 - WheelPos;
  if(WheelPos < 85) {
    return strip.Color(255 - WheelPos * 3, 0, WheelPos * 3);
  }
  if(WheelPos < 170) {
    WheelPos -= 85;
    return strip.Color(0, WheelPos * 3, 255 - WheelPos * 3);
  }
  WheelPos -= 170;
  return strip.Color(WheelPos * 3, 255 - WheelPos * 3, 0);
}
