// Define pin numbers
const int redLedPin = 2;
const int yellowLedPin = 3;
const int greenLedPin = 4;
const int pedestrianLedPin = 5;
const int buttonPin = 6;

// Define traffic light states
enum State {
  RED,
  YELLOW,
  GREEN,
  PEDESTRIAN
};

// Variables for state management
State currentState = RED;
unsigned long lastButtonPress = 0;
const unsigned long debounceDelay = 50; // Debounce delay for button press

void setup() {
  // Set LED pins as output
  pinMode(redLedPin, OUTPUT);
  pinMode(yellowLedPin, OUTPUT);
  pinMode(greenLedPin, OUTPUT);
  pinMode(pedestrianLedPin, OUTPUT);

  // Set button pin as input with pull-up resistor
  pinMode(buttonPin, INPUT_PULLUP);

  // Initialize LEDs to OFF
  updateTrafficLight();
}

void loop() {
  // Check if the button is pressed
  if (digitalRead(buttonPin) == LOW) {
    // Debounce button press
    if (millis() - lastButtonPress > debounceDelay) {
      lastButtonPress = millis();
      // Move to the next state
      currentState = (State)((currentState + 1) % 4);
      updateTrafficLight();
    }
  }
}

void updateTrafficLight() {
  // Turn off all LEDs
  digitalWrite(redLedPin, LOW);
  digitalWrite(yellowLedPin, LOW);
  digitalWrite(greenLedPin, LOW);
  digitalWrite(pedestrianLedPin, LOW);

  // Set the LEDs based on the current state
  switch (currentState) {
    case RED:
      digitalWrite(redLedPin, HIGH);
      break;
    case YELLOW:
      digitalWrite(yellowLedPin, HIGH);
      break;
    case GREEN:
      digitalWrite(greenLedPin, HIGH);
      break;
    case PEDESTRIAN:
      digitalWrite(pedestrianLedPin, HIGH);
      break;
  }
}
