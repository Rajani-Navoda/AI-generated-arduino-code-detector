#include <RotaryEncoder.h>

// Define pin connections
#define ENCODER_CLK_PIN 32  // CLK (A pin)
#define ENCODER_DT_PIN 21   // DT (B pin)
#define ENCODER_SW_PIN 25   // SW (button pin)

// Create a RotaryEncoder instance
RotaryEncoder encoder(ENCODER_CLK_PIN, ENCODER_DT_PIN);

void setup() {
  Serial.begin(115200);
  Serial.println("Rotary Encoder Example");

  // Initialize the encoder
  encoder.setPosition(0);  // Set initial position to 0

  // Setup the switch pin
  pinMode(ENCODER_SW_PIN, INPUT_PULLUP);
}

void loop() {
  // Update the encoder
  encoder.tick();

  // Check for rotation
  int position = encoder.getPosition();
  
  // Print the current position
  Serial.print("Encoder Position: ");
  Serial.println(position);

  // Check if the button is pressed
  if (digitalRead(ENCODER_SW_PIN) == LOW) {
    Serial.println("Button pressed!");
    delay(200);  // Simple debounce
  }

  delay(100);  // Delay for stability
}
