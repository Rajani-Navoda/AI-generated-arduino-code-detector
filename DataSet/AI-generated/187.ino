#include <AceButton.h>

using namespace AceButton;

// Define the button and LED pins
const int buttonPin = 2;  // Pin for the button
const int ledPin = 13;     // Pin for the LED (built-in LED on many boards)

// Create a Button object
Button button(buttonPin);

void setup() {
  Serial.begin(9600);

  // Initialize button and LED
  button.init();
  button.setEventHandler(buttonEvent);
  pinMode(ledPin, OUTPUT);
}

void loop() {
  // Read button state
  button.read();
}

// Handle button events
void buttonEvent(AceButton* button, uint8_t eventType) {
  switch (eventType) {
    case AceButton::kEventPressed:
      Serial.println("Button pressed!");
      break;

    case AceButton::kEventReleased:
      Serial.println("Button released!");
      digitalWrite(ledPin, HIGH); // Turn on LED
      break;

    case AceButton::kEventClicked:
      // Clicked event ignored
      break;

    case AceButton::kEventDoubleClicked:
      Serial.println("Button double-clicked!");
      digitalWrite(ledPin, LOW);  // Turn off LED
      break;

    default:
      break;
  }
}
