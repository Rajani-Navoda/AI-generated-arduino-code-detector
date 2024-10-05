// Define pin numbers
const int ledPin = 9;     // PWM pin connected to the LED
const int buttonPin = 8;  // Pin connected to the button

// Variables for fading effect
int brightness = 0;       // Initial LED brightness
int fadeAmount = 5;       // Amount to change brightness per step

// Variables for button state
bool fading = false;      // Track whether fading is active
bool lastButtonState = HIGH; // Previous button state
bool currentButtonState = HIGH; // Current button state

void setup() {
  // Set LED pin as output
  pinMode(ledPin, OUTPUT);
  
  // Set button pin as input with pull-up resistor
  pinMode(buttonPin, INPUT_PULLUP);
}

void loop() {
  // Read the current button state
  currentButtonState = digitalRead(buttonPin);
  
  // Check if the button state has changed from HIGH to LOW (pressed)
  if (lastButtonState == HIGH && currentButtonState == LOW) {
    // Toggle fading state
    fading = !fading;
    delay(200); // Simple debounce delay
  }
  
  // Update last button state
  lastButtonState = currentButtonState;
  
  // If fading is active, adjust brightness
  if (fading) {
    // Set LED brightness
    analogWrite(ledPin, brightness);

    // Change brightness for the next cycle
    brightness += fadeAmount;

    // Reverse the fading direction if brightness reaches its limits
    if (brightness <= 0 || brightness >= 255) {
      fadeAmount = -fadeAmount; // Reverse direction
    }

    // Delay for smooth fading
    delay(30);
  } else {
    // If fading is not active, ensure LED is off
    analogWrite(ledPin, 0);
  }
}
