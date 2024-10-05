/*
  This example shows how to turn your A-Star 32U4 into a simple keyboard.
  The three on-board buttons (A, B, and C) can each be used to type their corresponding letter on your computer.
  An extra button can optionally be connected to pin 12 to type the letter D.
  
  This example uses the getSingleDebouncedPress function to monitor for press events on all the buttons simultaneously.
*/

#include <AStar32U4.h>

#define BUTTON_A_PIN 6   // Pin for button A
#define BUTTON_B_PIN 7   // Pin for button B
#define BUTTON_C_PIN 8   // Pin for button C
#define BUTTON_D_PIN 12  // Pin for extra button D (optional)

// Create Button objects
Button buttonA(BUTTON_A_PIN);
Button buttonB(BUTTON_B_PIN);
Button buttonC(BUTTON_C_PIN);
Button buttonD(BUTTON_D_PIN);

void setup() {
  // Initialize the button pins
  buttonA.begin();
  buttonB.begin();
  buttonC.begin();
  buttonD.begin();

  // Initialize Serial for debugging (optional)
  Serial.begin(9600);
}

void loop() {
  // Check for button presses with debouncing
  if (buttonA.getSingleDebouncedPress()) {
    sendKeyStroke('A');
  }

  if (buttonB.getSingleDebouncedPress()) {
    sendKeyStroke('B');
  }

  if (buttonC.getSingleDebouncedPress()) {
    sendKeyStroke('C');
  }

  if (buttonD.getSingleDebouncedPress()) {
    sendKeyStroke('D');
  }

  // Small delay to prevent overwhelming the CPU
  delay(10);
}

void sendKeyStroke(char key) {
  // Send the keystroke to the computer
  Keyboard.press(key);
  delay(50); // Short delay to ensure the key press is registered
  Keyboard.release(key);

  // Optional: Print the key press to the Serial Monitor for debugging
  Serial.print("Key pressed: ");
  Serial.println(key);
}
