#include <Mouse.h>  // Include the Mouse library

// Define pins for the joystick and buttons
#define JOYSTICK_X A0
#define JOYSTICK_Y A1
#define BUTTON_LEFT 2
#define BUTTON_RIGHT 3
#define BUTTON_UP 4
#define BUTTON_DOWN 5

// Joystick calibration
int centerX = 512;  // Center X value of joystick
int centerY = 512;  // Center Y value of joystick

void setup() {
  // Start the Mouse library
  Mouse.begin();

  // Initialize joystick pins as inputs
  pinMode(JOYSTICK_X, INPUT);
  pinMode(JOYSTICK_Y, INPUT);

  // Initialize button pins as inputs with pullup resistors
  pinMode(BUTTON_LEFT, INPUT_PULLUP);
  pinMode(BUTTON_RIGHT, INPUT_PULLUP);
  pinMode(BUTTON_UP, INPUT_PULLUP);
  pinMode(BUTTON_DOWN, INPUT_PULLUP);
}

void loop() {
  int xValue = analogRead(JOYSTICK_X);
  int yValue = analogRead(JOYSTICK_Y);

  // Read button states
  bool leftPressed = !digitalRead(BUTTON_LEFT);
  bool rightPressed = !digitalRead(BUTTON_RIGHT);
  bool upPressed = !digitalRead(BUTTON_UP);
  bool downPressed = !digitalRead(BUTTON_DOWN);

  // Calculate mouse movement based on joystick and button input
  int mouseX = 0;
  int mouseY = 0;

  // Joystick movement
  if (xValue < centerX - 100) {
    mouseX = -1;  // Move left
  } else if (xValue > centerX + 100) {
    mouseX = 1;   // Move right
  }

  if (yValue < centerY - 100) {
    mouseY = -1;  // Move up
  } else if (yValue > centerY + 100) {
    mouseY = 1;   // Move down
  }

  // Button-based movement
  if (leftPressed) {
    mouseX = -5;  // Fast left
  } else if (rightPressed) {
    mouseX = 5;   // Fast right
  }

  if (upPressed) {
    mouseY = -5;  // Fast up
  } else if (downPressed) {
    mouseY = 5;   // Fast down
  }

  // Move the mouse
  Mouse.move(mouseX, mouseY, 0);

  // Small delay to slow down movement
  delay(10);
}

void end() {
  Mouse.end();  // Ensure mouse control is released
}
