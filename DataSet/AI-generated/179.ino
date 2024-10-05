// Define joystick pins for the X and Y axes, and the button
#define JOYSTICK_X A0   // X-axis connected to A0
#define JOYSTICK_Y A1   // Y-axis connected to A1
#define JOYSTICK_BTN 7  // Button connected to digital pin 7

void setup() {
  // Initialize serial communication for debugging
  Serial.begin(9600);

  // Initialize joystick button as input with a pullup resistor
  pinMode(JOYSTICK_BTN, INPUT_PULLUP);

  Serial.println("Joystick Example - DFRobot Accessory Shield");
}

void loop() {
  // Read the analog values for the X and Y axes
  int xValue = analogRead(JOYSTICK_X);
  int yValue = analogRead(JOYSTICK_Y);

  // Read the button state (LOW when pressed, HIGH when not pressed)
  bool buttonPressed = !digitalRead(JOYSTICK_BTN);

  // Print the joystick X and Y positions to the Serial Monitor
  Serial.print("X-axis: ");
  Serial.print(xValue);
  Serial.print("\tY-axis: ");
  Serial.print(yValue);

  // Print button state
  if (buttonPressed) {
    Serial.println("\tButton: Pressed");
  } else {
    Serial.println("\tButton: Not Pressed");
  }

  // Delay to make it easier to read the output
  delay(200);
}
