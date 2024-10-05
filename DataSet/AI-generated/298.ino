#include <Adafruit_NeoPixel.h>
#include <AnimatedGIF.h>

// Define the number of LEDs and the pin
#define NUM_LEDS 70 // Example for a 5x14 RGB LED matrix
#define PIN 6 // Pin connected to the data input of the NeoPixel strip

Adafruit_NeoPixel strip(NUM_LEDS, PIN, NEO_GRB + NEO_KHZ800);
AnimatedGIF gif;

// GIF draw callback function
void GIFDRAW(uint8_t *bitmap, uint8_t *palette, int16_t width, int16_t height, int16_t x, int16_t y) {
  for (int16_t j = 0; j < height; j++) {
    for (int16_t i = 0; i < width; i++) {
      uint8_t index = bitmap[j * width + i];
      if (index < 256) {
        uint32_t color = strip.Color(palette[index * 3], palette[index * 3 + 1], palette[index * 3 + 2]);
        if (x + i < NUM_LEDS) {
          strip.setPixelColor((y + j) * 5 + (x + i), color); // Map to appropriate LED
        }
      }
    }
  }
  strip.show(); // Update the LED matrix with the new colors
}

void setup() {
  strip.begin();
  strip.show();
  Serial.begin(115200);
  
  // Start the GIF player
  if (!gif.begin(GIFDRAW)) {
    Serial.println("Failed to start GIF player");
  }

  // Load your GIF here
  // gif.open("example.gif"); // Uncomment to load a GIF file
}

void loop() {
  gif.update(); // Continuously update the GIF playback
  delay(10); // Control the frame rate as needed
}
