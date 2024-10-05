// Define the pins for the three user LEDs on the A-Star 32U4
const int greenLedPin = 4;  // Replace with actual pin for green LED
const int yellowLedPin = 5; // Replace with actual pin for yellow LED
const int redLedPin = 6;    // Replace with actual pin for red LED

void setup() {
  // Initialize the LED pins as outputs
  pinMode(greenLedPin, OUTPUT);
  pinMode(yellowLedPin, OUTPUT);
  pinMode(redLedPin, OUTPUT);

  // Initialize LEDs to be off
  digitalWrite(greenLedPin, LOW);
  digitalWrite(yellowLedPin, LOW);
  digitalWrite(redLedPin, LOW);
}

void loop() {
  // Turn on all LEDs
  digitalWrite(greenLedPin, HIGH);
  digitalWrite(yellowLedPin, HIGH);
  digitalWrite(redLedPin, HIGH);

  // Wait for one second
  delay(1000);

  // Turn off all LEDs
  digitalWrite(greenLedPin, LOW);
  digitalWrite(yellowLedPin, LOW);
  digitalWrite(redLedPin, LOW);

  // Wait for one second
  delay(1000);
}
