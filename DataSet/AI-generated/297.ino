#include <Adafruit_NeoPixel.h>
#include <AnimatedGIF.h>

// Define the number of LEDs on the shield
#define NUM_LEDS 70 // 5x14 grid
#define PIN 6 // Pin connected to the data input of the NeoPixel strip

Adafruit_NeoPixel strip(NUM_LEDS, PIN, NEO_GRB + NEO_KHZ800);
AnimatedGIF gif;

// GIF draw callback
void GIFDRAW(uint8_t *bitmap, uint8_t *palette, int16_t width, int16_t height, int16_t x, int16_t y) {
  for (int16_t j = 0; j < height; j++) {
    for (int16_t i = 0; i < width; i++) {
      uint8_t index = bitmap[j * width + i];
      uint32_t color = (index < 256) ? strip.Color(palette[index * 3], palette[index * 3 + 1], palette[index * 3 + 2]) : 0;
      if (x + i < NUM_LEDS) {
        strip.setPixelColor(x + i + (j * 5), color);
      }
    }
  }
  strip.show();
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
  // gif.open("example.gif"); // Uncomment to load GIF from SD or SPIFFS
}

void loop() {
  gif.update();
  delay(10); // Adjust the delay to control the frame rate
}
