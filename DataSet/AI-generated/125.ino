const int buttonPin = 2;  // Pin connected to the button
const int ledPin = 13;    // Pin connected to the LED

void setup() {
  // Initialize the button pin as an input with an internal pull-up resistor
  pinMode(buttonPin, INPUT_PULLUP);
  
  // Initialize the LED pin as an output
  pinMode(ledPin, OUTPUT);
  
  // Start with the LED off
  digitalWrite(ledPin, LOW);
}

void loop() {
  // Read the state of the button pin
  int buttonState = digitalRead(buttonPin);
  
  // Check if the button is pressed
  if (buttonState == LOW) {
    // Button is pressed, turn the LED on
    digitalWrite(ledPin, HIGH);
  } else {
    // Button is not pressed, turn the LED off
    digitalWrite(ledPin, LOW);
  }
}
