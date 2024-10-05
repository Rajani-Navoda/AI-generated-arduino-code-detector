// Define the RGB LED pin numbers on the DFRobot Accessory Shield
#define RED_PIN 6   // Pin connected to the Red LED
#define GREEN_PIN 5 // Pin connected to the Green LED
#define BLUE_PIN 3  // Pin connected to the Blue LED

void setup() {
  // Initialize RGB LED pins as outputs
  pinMode(RED_PIN, OUTPUT);
  pinMode(GREEN_PIN, OUTPUT);
  pinMode(BLUE_PIN, OUTPUT);

  Serial.begin(9600);  // Start serial communication
  Serial.println("Hello World RGB - DFRobot Accessory Shield");
}

void loop() {
  // Show some basic colors

  // Red
  setColor(255, 0, 0);  // Max red, no green, no blue
  delay(1000);          // Hold for 1 second

  // Green
  setColor(0, 255, 0);  // Max green, no red, no blue
  delay(1000);

  // Blue
  setColor(0, 0, 255);  // Max blue, no red, no green
  delay(1000);

  // Yellow (Red + Green)
  setColor(255, 255, 0);
  delay(1000);

  // Cyan (Green + Blue)
  setColor(0, 255, 255);
  delay(1000);

  // Magenta (Red + Blue)
  setColor(255, 0, 255);
  delay(1000);

  // White (Red + Green + Blue)
  setColor(255, 255, 255);
  delay(1000);

  // Turn off the LED
  setColor(0, 0, 0);  // All components off
  delay(1000);
}

// Function to set RGB color
void setColor(int red, int green, int blue) {
  analogWrite(RED_PIN, red);
  analogWrite(GREEN_PIN, green);
  analogWrite(BLUE_PIN, blue);
}
