#include <ShiftRegister74HC595.h>  // Include library for 74HC595 shift register

// Define pin connections
const int latchPin = 4;  // Latch pin for 74HC595
const int clockPin = 5;  // Clock pin for 74HC595
const int dataPin = 6;   // Data pin for 74HC595

// Define digit pins (connected directly to the microcontroller)
const int digitPins[4] = {7, 8, 9, 10};  // Pins for controlling each digit

// Create an instance of the ShiftRegister74HC595 class
ShiftRegister74HC595<1> sr(latchPin, clockPin, dataPin);  // 1 shift register (74HC595)

// 7-segment digit patterns (0-3)
const byte digitPatterns[] = {
  0b00111111, // 0
  0b00000110, // 1
  0b01011011, // 2
  0b01001111  // 3
};

// Array to hold the current digits to display
byte digitsToDisplay[4] = {0, 1, 2, 3};

// Brightness levels
int brightness = 0;
const int brightnessMax = 255;  // Maximum brightness (for PWM)

// Timing variables
unsigned long previousMillis = 0;
const long interval = 1000;  // 1 second interval for rotation and brightness adjustment

void setup() {
  // Initialize digit pins as outputs
  for (int i = 0; i < 4; i++) {
    pinMode(digitPins[i], OUTPUT);
    digitalWrite(digitPins[i], LOW);  // Initially turn off all digits
  }

  // Initialize the shift register
  sr.setAllLow();  // Clear all segments
}

void loop() {
  // Get the current time
  unsigned long currentMillis = millis();

  // Check if 1 second has passed
  if (currentMillis - previousMillis >= interval) {
    // Save the last time the display was updated
    previousMillis = currentMillis;

    // Scroll digits to the left
    scrollDigits();

    // Increment brightness
    updateBrightness();

    // Render the digits to the display
    renderDisplay();
  }
}

// Function to scroll the digits to the left
void scrollDigits() {
  // Shift all digits to the left
  byte firstDigit = digitsToDisplay[0];
  for (int i = 0; i < 3; i++) {
    digitsToDisplay[i] = digitsToDisplay[i + 1];
  }
  // Loop the first digit to the last position
  digitsToDisplay[3] = firstDigit;
}

// Function to update the brightness (using PWM on digit control pins)
void updateBrightness() {
  brightness += 51;  // Increment brightness by 51 (255/5 steps)
  if (brightness > brightnessMax) {
    brightness = 0;  // Wrap brightness back to 0
  }
}

// Function to render the digits to the display
void renderDisplay() {
  for (int digit = 0; digit < 4; digit++) {
    // Turn on the current digit
    digitalWrite(digitPins[digit], HIGH);

    // Send the digit's segment pattern to the shift register
    sr.setAll(digitPatterns[digitsToDisplay[digit]]);

    // Set brightness using PWM on the digit pin
    analogWrite(digitPins[digit], brightness);

    // Small delay to allow the digit to be visible (multiplexing)
    delay(5);

    // Turn off the digit after displaying it
    digitalWrite(digitPins[digit], LOW);
  }
}
