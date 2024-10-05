// Include necessary libraries
#include <TimerOne.h>  // TimerOne library to handle interrupts
#include <ShiftRegister74HC595.h>  // Include a library for 74HC595 shift register

// Constants
const int latchPin = 10;  // Pin connected to ST_CP of 74HC595
const int clockPin = 13;  // Pin connected to SH_CP of 74HC595
const int dataPin = 11;   // Pin connected to DS of 74HC595

// Create an instance of ShiftRegister74HC595
ShiftRegister74HC595<1> sr(dataPin, clockPin, latchPin);

// Global variable to hold the current LED pattern
byte ledPattern = 0b10101010;

// ISR to update the 74HC595 shift register in the background
void updateLEDs() {
  sr.setAll(ledPattern);  // Shift out the LED pattern
}

void setup() {
  // Setup pins for shift register
  pinMode(latchPin, OUTPUT);
  pinMode(clockPin, OUTPUT);
  pinMode(dataPin, OUTPUT);
  
  // Initialize the Timer1 library, with a 1ms interrupt interval (1000Hz)
  Timer1.initialize(1000);
  
  // Attach the interrupt to the updateLEDs function
  Timer1.attachInterrupt(updateLEDs);
}

void loop() {
  // In the main loop, the LED pattern can be changed dynamically
  static unsigned long lastChange = 0;
  if (millis() - lastChange > 500) {
    lastChange = millis();
    
    // Toggle the LED pattern
    ledPattern = ~ledPattern;
  }
}
