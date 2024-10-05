#include <RotaryEncoder.h>

// Define pin connections
#define ENCODER_CLK_PIN 32  // CLK (A pin)
#define ENCODER_DT_PIN 21   // DT (B pin)
#define ENCODER_SW_PIN 25   // SW (button pin)

// Create a RotaryEncoder instance
RotaryEncoder encoder(ENCODER_CLK_PIN, ENCODER_DT_PIN);

// Variables for acceleration detection
int lastPosition = 0;
unsigned long lastUpdateTime = 0;

void setup() {
  Serial.begin(115200);
  Serial.println("Rotary Encoder Acceleration Test");

  // Initialize the encoder
  encoder.setPosition(0);  // Set initial position to 0

  // Setup the switch pin
  pinMode(ENCODER_SW_PIN, INPUT_PULLUP);
}

void loop() {
  // Update the encoder
  encoder.tick();

  // Get the current position
  int currentPosition = encoder.getPosition();
  unsigned long currentTime = millis();
  
  // Check for acceleration
  if (currentPosition != lastPosition) {
    unsigned long timeDiff = currentTime - lastUpdateTime;
    int positionChange = currentPosition - lastPosition;

    Serial.print("Position: ");
    Serial.print(currentPosition);
    Serial.print(" Change: ");
    Serial.print(positionChange);
    Serial.print(" Time: ");
    Serial.print(timeDiff);
    Serial.println(" ms");

    // Adjust output based on speed of rotation
    if (timeDiff < 100) {
      Serial.println("Fast rotation detected!");
    } else if (timeDiff < 500) {
      Serial.println("Moderate rotation detected.");
    } else {
      Serial.println("Slow rotation detected.");
    }

    // Update last values
    lastPosition = currentPosition;
    lastUpdateTime = currentTime;
  }

  // Check if the button is pressed
  if (digitalRead(ENCODER_SW_PIN) == LOW) {
    Serial.println("Button pressed!");
    delay(200);  // Simple debounce
  }

  delay(50);  // Delay for stability
}
