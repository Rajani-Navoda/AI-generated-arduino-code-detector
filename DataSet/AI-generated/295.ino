#include <LovyanGFX.hpp>
#include <Chimera.h>
#include <FS.h>
#include <SD.h>
#include <SPI.h>

LGFX gfx;  // Create a LovyanGFX object

// Constants
const char* sdPath = "/gif/";  // Path to the GIF files
File gifFile;
String gifFiles[50];  // Array to store GIF file names
int gifCount = 0;

// Function to initialize SD card
void initSD() {
  if (!SD.begin()) {
    Serial.println("SD Card initialization failed!");
    while (1);
  }
  Serial.println("SD Card initialized.");
}

// Function to load GIF files from SD card
void loadGifs() {
  File dir = SD.open(sdPath);
  if (!dir) {
    Serial.println("Failed to open GIF directory!");
    return;
  }

  while (true) {
    gifFile = dir.openNextFile();
    if (!gifFile) {
      break;  // No more files
    }
    String filename = gifFile.name();
    if (filename.endsWith(".gif")) {
      gifFiles[gifCount++] = filename;  // Store GIF file name
      Serial.println("Found GIF: " + filename);
    }
    gifFile.close();
  }
  dir.close();
  Serial.print("Total GIFs found: ");
  Serial.println(gifCount);
}

// Function to play GIF
void playGif(const String& filename) {
  gfx.fillScreen(TFT_BLACK);  // Clear screen before playing GIF
  if (!gfx.drawGif(filename.c_str())) {
    Serial.println("Failed to play GIF: " + filename);
  }
}

void setup() {
  Serial.begin(115200);
  gfx.init();  // Initialize display
  gfx.setRotation(1);  // Set display rotation
  initSD();  // Initialize SD card
  loadGifs();  // Load GIF files
}

void loop() {
  if (gifCount > 0) {
    for (int i = 0; i < gifCount; i++) {
      playGif(gifFiles[i]);  // Play each GIF in an endless loop
      delay(1000);  // Pause between GIFs (adjust as needed)
    }
  }
}
