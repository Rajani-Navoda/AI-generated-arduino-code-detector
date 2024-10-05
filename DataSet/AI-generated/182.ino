// Define joystick pins for the X axis and the button
#define JOYSTICK_X A0   // X-axis connected to A0
#define JOYSTICK_BTN 7  // Button connected to digital pin 7

// Define relay pin
#define RELAY_PIN 8     // Relay connected to digital pin 8

// Variable to keep track of relay state
bool relayState = false;

void setup() {
  // Initialize joystick button as input with pullup resistor
  pinMode(JOYSTICK_BTN, INPUT_PULLUP);

  // Initialize relay pin as output
  pinMode(RELAY_PIN, OUTPUT);

  // Set relay initially off
  digitalWrite(RELAY_PIN, LOW);

  // Start serial communication (optional for debugging)
  Serial.begin(9600);
  Serial.println("Joystick Relay Control Example - DFRobot Accessory Shield");
}

void loop() {
  // Read the analog value for the X axis
  int xValue = analogRead(JOYSTICK_X);

  // Read the button state (LOW when pressed)
  bool buttonPressed = !digitalRead(JOYSTICK_BTN);

  // Map the joystick X-axis value (0-1023) to control relay
  if (xValue > 512) {
    relayState = true;  // Turn the relay on if X-axis is moved to the right
  } else {
    relayState = false; // Turn the relay off if X-axis is moved to the left
  }

  // If the button is pressed, toggle the relay state
  if (buttonPressed) {
    relayState = !relayState;  // Toggle the relay state

    // Debounce delay to prevent multiple toggles from one press
    delay(200);
  }

  // Set the relay state based on the current relayState variable
  digitalWrite(RELAY_PIN, relayState ? HIGH : LOW);

  // Optional: Print joystick and relay values to the Serial Monitor
  Serial.print("X-axis: ");
  Serial.print(xValue);
  Serial.print("\tRelay: ");
  Serial.println(relayState ? "On" : "Off");

  // Small delay for smoother output
  delay(100);
}
