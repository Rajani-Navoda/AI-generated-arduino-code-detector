
#include "SignalArduino.h"

SignalArduino::SignalArduino(const int* ledPins, int numLEDs)
  : _ledPins(ledPins), _numLEDs(numLEDs), _currentPattern(0), _lastUpdate(0) {
}

void SignalArduino::begin() {
  for (int i = 0; i < _numLEDs; i++) {
    pinMode(_ledPins[i], OUTPUT);
  }
}

void SignalArduino::setPattern(int pattern) {
  _currentPattern = pattern;
  _applyPattern(pattern);
}

void SignalArduino::update() {
  unsigned long currentTime = millis();
  
  // Example: Update based on a timer
  if (currentTime - _lastUpdate > 1000) {  // Update every 1 second
    _lastUpdate = currentTime;
    // Cycle through patterns or implement logic here
    // For demonstration, we'll just toggle between patterns
    setPattern((_currentPattern + 1) % 3);  // Example: Assuming 3 patterns
  }
}

void SignalArduino::_applyPattern(int pattern) {
  // Turn off all LEDs
  for (int i = 0; i < _numLEDs; i++) {
    digitalWrite(_ledPins[i], LOW);
  }

  // Apply the pattern
  switch (pattern) {
    case 0:
      // Example pattern: Turn on LED 0 and LED 1
      digitalWrite(_ledPins[0], HIGH);
      digitalWrite(_ledPins[1], HIGH);
      break;
    case 1:
      // Example pattern: Turn on LED 2 through LED 5
      for (int i = 2; i <= 5; i++) {
        digitalWrite(_ledPins[i], HIGH);
      }
      break;
    case 2:
      // Example pattern: All LEDs on
      for (int i = 0; i < _numLEDs; i++) {
        digitalWrite(_ledPins[i], HIGH);
      }
      break;
  }
}
