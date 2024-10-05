#include <AceButton.h>

using namespace AceButton;

// Define the button pin
const int BUTTON_PIN = 2; // Pin for the button

// Create a Button object
Button button(BUTTON_PIN);

void setup() {
  Serial.begin(9600);

  // Initialize the button with pull-up resistor
  button.init();
  button.setEventHandler(buttonEvent);
  
  // Set the button pin as INPUT_PULLUP
  pinMode(BUTTON_PIN, INPUT_PULLUP);
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
      digitalWrite(LED_BUILTIN, HIGH); // Turn on the built-in LED
      break;

    case AceButton::kEventReleased:
      Serial.println("Button released!");
      digitalWrite(LED_BUILTIN, LOW);  // Turn off the built-in LED
      break;

    default:
      break;
  }
}
