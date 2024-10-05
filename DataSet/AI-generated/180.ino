// Define joystick pins for the X, Y axes, and the button
#define JOYSTICK_X A0   // X-axis connected to A0
#define JOYSTICK_Y A1   // Y-axis connected to A1
#define JOYSTICK_BTN 7  // Button connected to digital pin 7

// Define RGB LED pins
#define RED_PIN 6       // Red LED connected to pin 6
#define GREEN_PIN 5     // Green LED connected to pin 5
#define BLUE_PIN 3      // Blue LED connected to pin 3

// Variable to keep track of Blue LED state
bool blueLEDState = false;

void setup() {
  // Initialize joystick button as input with pullup resistor
  pinMode(JOYSTICK_BTN, INPUT_PULLUP);

  // Initialize RGB LED pins as outputs
  pinMode(RED_PIN, OUTPUT);
  pinMode(GREEN_PIN, OUTPUT);
  pinMode(BLUE_PIN, OUTPUT);

  // Start serial communication (optional for debugging)
  Serial.begin(9600);
  Serial.println("Joystick RGB Control Example - DFRobot Accessory Shield");
}

void loop() {
  // Read the analog values for the X and Y axes
  int xValue = analogRead(JOYSTICK_X);
  int yValue = analogRead(JOYSTICK_Y);

  // Map the joystick values (0-1023) to PWM range (0-255)
  int redValue = map(xValue, 0, 1023, 0, 255);
  int greenValue = map(yValue, 0, 1023, 0, 255);

  // Set the brightness of the Red and Green LEDs
  analogWrite(RED_PIN, redValue);
  analogWrite(GREEN_PIN, greenValue);

  // Read the button state (LOW when pressed)
  bool buttonPressed = !digitalRead(JOYSTICK_BTN);

  // If the button is pressed, toggle the Blue LED state
  if (buttonPressed) {
    blueLEDState = !blueLEDState;  // Toggle the Blue LED state
    digitalWrite(BLUE_PIN, blueLEDState ? HIGH : LOW);  // Turn the Blue LED on or off

    // Debounce delay to prevent multiple toggles from one press
    delay(200);
  }

  // Optional: Print joystick and RGB values to the Serial Monitor
  Serial.print("X-axis: ");
  Serial.print(xValue);
  Serial.print("\tY-axis: ");
  Serial.print(yValue);
  Serial.print("\tRed: ");
  Serial.print(redValue);
  Serial.print("\tGreen: ");
  Serial.print(greenValue);
  Serial.print("\tBlue: ");
  Serial.println(blueLEDState ? "On" : "Off");

  // Small delay for smoother output
  delay(100);
}
