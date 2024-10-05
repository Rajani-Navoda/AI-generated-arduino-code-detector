#include <AceButton.h>

using namespace AceButton;

// Define the button pin
const int buttonPin = 2; // Pin for the button

// Create a Button object
Button button(buttonPin);

void setup() {
  Serial.begin(9600);

  // Initialize button
  button.init();
  button.setEventHandler(buttonEvent);
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
      break;

    case AceButton::kEventClicked:
      Serial.println("Button clicked!");
      break;

    case AceButton::kEventDoubleClicked:
      Serial.println("Button double-clicked!");
      break;

    default:
      break;
  }
}
