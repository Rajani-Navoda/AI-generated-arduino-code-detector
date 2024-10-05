#include <MD_Parola.h>
#include <MD_MAX72XX.h>
#include <SPI.h>

// Define the hardware type, number of devices, and SPI pins
#define HARDWARE_TYPE MD_MAX72XX::FC16_HW
#define MAX_DEVICES 4

#define DATA_PIN 13  // D7 on ESP8266
#define CS_PIN 15    // D8 on ESP8266
#define CLK_PIN 14   // D5 on ESP8266

// Create a new Parola object
MD_Parola matrixDisplay = MD_Parola(HARDWARE_TYPE, DATA_PIN, CLK_PIN, CS_PIN, MAX_DEVICES);

void setup() {
  // Initialize the display
  matrixDisplay.begin();
  matrixDisplay.setIntensity(5);  // Set brightness (0-15)
  matrixDisplay.displayText("HELLO", PA_CENTER, 100, 0, PA_SCROLL_LEFT, PA_SCROLL_LEFT);
}

void loop() {
  // Animate the text
  if (matrixDisplay.displayAnimate()) {
    // Once the text has finished scrolling, display next message
    matrixDisplay.displayText("ESP8266", PA_CENTER, 100, 0, PA_SCROLL_LEFT, PA_SCROLL_LEFT);
  }
}
