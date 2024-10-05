// Define joystick pins for the X, Y axes, and the button
#define JOYSTICK_X A0   // X-axis connected to A0
#define JOYSTICK_Y A1   // Y-axis connected to A1
#define JOYSTICK_BTN 7  // Button connected to digital pin 7

// Define buzzer pin
#define BUZZER_PIN 9    // Buzzer connected to pin 9

// Variable to track the buzzer's state
bool buzzerState = false;

void setup() {
  // Initialize joystick button as input with pullup resistor
  pinMode(JOYSTICK_BTN, INPUT_PULLUP);

  // Initialize buzzer pin as output
  pinMode(BUZZER_PIN, OUTPUT);

  // Start serial communication (optional for debugging)
  Serial.begin(9600);
  Serial.println("Joystick Buzzer Control Example - DFRobot Accessory Shield");
}

void loop() {
  // Read the analog values for the X and Y axes
  int xValue = analogRead(JOYSTICK_X);
  int yValue = analogRead(JOYSTICK_Y);

  // Map the joystick X-axis value (0-1023) to a frequency range (200 - 2000 Hz)
  int frequency = map(xValue, 0, 1023, 200, 2000);

  // Map the joystick Y-axis value (0-1023) to duration (50 - 500 ms)
  int duration = map(yValue, 0, 1023, 50, 500);

  // Read the button state (LOW when pressed)
  bool buttonPressed = !digitalRead(JOYSTICK_BTN);

  // If the button is pressed, toggle the buzzer state
  if (buttonPressed) {
    buzzerState = !buzzerState;  // Toggle the buzzer state

    // Debounce delay to prevent multiple toggles from one press
    delay(200);
  }

  // If the buzzer is on, play a tone
  if (buzzerState) {
    tone(BUZZER_PIN, frequency, duration);  // Play tone with the mapped frequency and duration
  } else {
    noTone(BUZZER_PIN);  // Turn off the buzzer
  }

  // Optional: Print joystick and buzzer values to the Serial Monitor
  Serial.print("X-axis: ");
  Serial.print(xValue);
  Serial.print("\tFrequency: ");
  Serial.print(frequency);
  Serial.print("\tY-axis: ");
  Serial.print(yValue);
  Serial.print("\tDuration: ");
  Serial.print(duration);
  Serial.println(buzzerState ? "\tBuzzer: On" : "\tBuzzer: Off");

  // Small delay for smoother output
  delay(100);
}
