// Define the pin for button A and the LED pin
const int buttonPin = 2; // Replace with actual pin for button A
const int ledPin = 4;    // Replace with actual pin for green LED

// Variables for button state
int buttonState = 0; // Current state of the button
int lastButtonState = 0; // Previous state of the button

// Timing variables for debouncing
unsigned long lastDebounceTime = 0; // Last time the button state was toggled
unsigned long debounceDelay = 50; // Debounce time; increase if the button is bouncing

// Method 1: Polling
void method1() {
  buttonState = digitalRead(buttonPin);
  if (buttonState == HIGH && lastButtonState == LOW) {
    // Button is pressed
    digitalWrite(ledPin, HIGH);
  } else if (buttonState == LOW && lastButtonState == HIGH) {
    // Button is released
    digitalWrite(ledPin, LOW);
  }
  lastButtonState = buttonState;
}

// Method 2: Interrupt
void buttonISR() {
  digitalWrite(ledPin, !digitalRead(ledPin)); // Toggle LED state
}

void setup() {
  // Initialize the LED pin as an output
  pinMode(ledPin, OUTPUT);

  // Initialize the button pin as an input with pull-up resistor
  pinMode(buttonPin, INPUT_PULLUP);

  // Attach interrupt to button pin
  attachInterrupt(digitalPinToInterrupt(buttonPin), buttonISR, CHANGE);
}

void loop() {
  // Method 3: State Change Detection
  int reading = digitalRead(buttonPin);
  if (reading != lastButtonState) {
    lastDebounceTime = millis(); // Reset debounce timer
  }

  if ((millis() - lastDebounceTime) > debounceDelay) {
    // If the state has changed after debouncing, toggle LED
    if (reading == LOW) {
      digitalWrite(ledPin, !digitalRead(ledPin)); // Toggle LED
    }
  }

  lastButtonState = reading;
}
