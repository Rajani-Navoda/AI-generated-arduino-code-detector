const int buttonPin = 2; // Pin number for the button

void setup() {
  // Initialize the built-in LED as an output
  pinMode(LED_BUILTIN, OUTPUT);
  
  // Initialize the button pin as an input with an internal pull-up resistor
  pinMode(buttonPin, INPUT_PULLUP);
}

void loop() {
  // Check the state of the button
  if (digitalRead(buttonPin) == LOW) {
    // Button is pressed (LOW state)
    digitalWrite(LED_BUILTIN, HIGH); // Turn on the LED
  } else {
    // Button is not pressed (HIGH state)
    digitalWrite(LED_BUILTIN, LOW); // Turn off the LED
  }
}
