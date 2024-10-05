/*
 * Same as DirectDemo, with the segment and digit pins connected directly to the
 * microcontroller. Uses the DirectFast4Module class which utilizes the
 * <digitalWriteFast.h> library.
 *
 * Supported microcontroller environments:
 *  * AUNITER_MICRO_CUSTOM_DIRECT: SparkFun Pro Micro
 */

#include <Arduino.h>
#include "DirectFast4Module.h"

// Pin definitions
const int digitPins[] = {2, 3, 4, 5}; // Pins for the digits
const int segmentPins[] = {6, 7, 8, 9, 10, 11, 12, 13}; // Pins for the segments

DirectFast4Module ledModule(digitPins, segmentPins, sizeof(digitPins) / sizeof(digitPins[0]));

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

    // Rotate digits to the left with increased brightness
    for (int brightness = 0; brightness <= 255; brightness += 5) {
        for (int i = 0; i < 4; i++) {
            ledModule.setBrightness(brightness); // Set brightness
            ledModule.displayDigit(i); // Display current digit
            delay(250); // Short delay for rotation effect
        }
    }
}
