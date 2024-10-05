
#include <Adafruit_NeoPixel.h>

// Pin where the data line of the WS2812 is connected
#define PIN 6

// Number of LEDs in the strip
#define NUM_LEDS 30

// Create an instance of the NeoPixel library
Adafruit_NeoPixel strip = Adafruit_NeoPixel(NUM_LEDS, PIN, NEO_GRB + NEO_KHZ800);

void setup() {
  // Initialize the LED strip
  strip.begin();
  strip.show(); // Initialize all pixels to off
}

void loop() {
  // Fade in
  for (int brightness = 0; brightness <= 255; brightness++) {
    setBrightness(brightness);
    delay(10); // Adjust the speed of the fade
  }

  // Fade out
  for (int brightness = 255; brightness >= 0; brightness--) {
    setBrightness(brightness);
    delay(10); // Adjust the speed of the fade
  }
}

void setBrightness(int brightness) {
  // Set the brightness of each pixel
  for (int i = 0; i < strip.numPixels(); i++) {
    strip.setPixelColor(i, strip.Color(brightness, brightness, brightness));
  }
  strip.show();
}