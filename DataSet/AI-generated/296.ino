#include <Arduino.h>
#include <SPI.h>
#include <Adafruit_GFX.h>
#include <AnimatedGIF.h>
#include <MatrixPanel_I2S_DMA.h>

// Define the LED matrix dimensions
#define WIDTH 64
#define HEIGHT 64

// Create the matrix panel object
MatrixPanel_I2S_DMA matrix(WIDTH, HEIGHT);

// Create the AnimatedGIF object
AnimatedGIF gif;

// Callback function for drawing GIF frames
void GIFDRAW(uint16_t *bitmap, int16_t x, int16_t y, int16_t width, int16_t height) {
  matrix.drawRGBBitmap(x, y, bitmap, width, height);
}

void setup() {
  Serial.begin(115200);
  matrix.begin();
  matrix.setBrightness(50); // Set brightness (0-255)
  matrix.fillScreen(0); // Clear the matrix
  
  // Start the GIF playback
  if (gif.begin(GIFDRAW)) {
    Serial.println("GIF started");
  } else {
    Serial.println("Failed to start GIF");
  }

  // Load GIF from program memory (FLASH)
  // Example: Load GIF from SPIFFS, SD, or stored in program memory.
  // gif.open("example.gif"); // Uncomment if using SPIFFS or SD
}

void loop() {
  // Update the GIF
  gif.update();
  
  // Add a delay to control refresh rate if needed
  delay(10);
}
