#include <Adafruit_GFX.h>
#include <Adafruit_ILI9341.h> // Replace with your display library
#include <AnimatedGIF.h>

// Define the display dimensions
#define SCREEN_WIDTH 240
#define SCREEN_HEIGHT 320

// Create display object
Adafruit_ILI9341 tft = Adafruit_ILI9341(/* parameters here */);
AnimatedGIF gif;

// GIF draw callback function
void GIFDRAW(uint8_t *bitmap, uint8_t *palette, int16_t width, int16_t height, int16_t x, int16_t y) {
  for (int16_t j = 0; j < height; j++) {
    for (int16_t i = 0; i < width; i++) {
      uint8_t index = bitmap[j * width + i];
      uint32_t color = (index < 256) ? tft.color565(palette[index * 3], palette[index * 3 + 1], palette[index * 3 + 2]) : 0;
      if (x + i < SCREEN_WIDTH && y + j < SCREEN_HEIGHT) {
        tft.drawPixel(x + i, y + j, color); // Draw the pixel on the display
      }
    }
  }
}

void setup() {
  tft.begin();
  tft.setRotation(3); // Set the rotation if needed
  tft.fillScreen(ILI9341_BLACK); // Clear the screen
  Serial.begin(115200);

  // Start the GIF player
  if (!gif.begin(GIFDRAW)) {
    Serial.println("Failed to start GIF player");
  }

  // Load your GIF here
  // gif.open("example.gif"); // Uncomment to load GIF from SPIFFS or SD
}

void loop() {
  gif.update(); // Continuously update the GIF playback
  delay(10); // Control the frame rate
}
