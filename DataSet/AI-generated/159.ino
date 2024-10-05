const int ledPin = 13;     // Pin number for the LED
const int buttonPin = 2;   // Pin number for the button

void setup() {
  // Initialize the LED pin as an output
  pinMode(ledPin, OUTPUT);
  
  // Initialize the button pin as an input with pull-up resistor
  pinMode(buttonPin, INPUT_PULLUP);
}

void loop() {
  // Read the state of the button
  bool buttonState = digitalRead(buttonPin);

  // Control the LED based on the button state
  if (buttonState == LOW) {
    // Button is pressed, turn on the LED
    digitalWrite(ledPin, HIGH);
  } else {
    // Button is not pressed, turn off the LED
    digitalWrite(ledPin, LOW);
  }
}
