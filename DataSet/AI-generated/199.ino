#include <Arduino.h>
#include "DirectModule.h"

// Pin definitions
const int digitPins[] = {2, 3, 4, 5}; // Pins for the digits
const int segmentPins[] = {6, 7, 8, 9, 10, 11, 12, 13}; // Pins for the segments

DirectModule ledModule(digitPins, segmentPins, sizeof(digitPins) / sizeof(digitPins[0]));

void setup() {
    // Initialize the LED module
    ledModule.begin();
}

void loop() {
    // Display digits 0 to 3
    for (int i = 0; i < 4; i++) {
        ledModule.displayDigit(i); // Display current digit
        delay(1000); // Wait for a second
    }

    // Rotate digits to the left and increment brightness
    for (int brightness = 0; brightness <= 255; brightness += 5) {
        for (int i = 0; i < 4; i++) {
            ledModule.setBrightness(brightness); // Set brightness
            ledModule.displayDigit(i); // Display current digit
            delay(250); // Short delay for rotation effect
        }
    }
}