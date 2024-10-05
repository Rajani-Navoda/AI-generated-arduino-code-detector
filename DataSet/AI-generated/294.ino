#include <RotaryEncoder.h>

// Define pin connections
#define ENCODER_CLK_PIN 32  // CLK (A pin)
#define ENCODER_DT_PIN 21   // DT (B pin)
#define ENCODER_SW_PIN 25   // SW (button pin)

// Create a RotaryEncoder instance
RotaryEncoder encoder(ENCODER_CLK_PIN, ENCODER_DT_PIN);

// Variable to hold the selected number
int selectedNumber = 0;

void setup() {
  Serial.begin(115200);
  Serial.println("Number Selection Example");

  // Initialize the encoder
  encoder.setPosition(0);  // Start at 0

  // Setup the switch pin with internal pull-up
  pinMode(ENCODER_SW_PIN, INPUT_PULLUP);
}

void loop() {
  // Update the encoder
  encoder.tick();

  // Get the current position
  int currentPosition = encoder.getPosition();
  
  // Print the selected number
  Serial.print("Selected Number: ");
  Serial.println(currentPosition);

  // Check if the button is pressed
  if (digitalRead(ENCODER_SW_PIN) == LOW) {
    selectedNumber = currentPosition;  // Confirm the selection
    Serial.print("Number confirmed: ");
    Serial.println(selectedNumber);
    delay(200);  // Simple debounce
  }

  delay(100);  // Delay for stability
}
