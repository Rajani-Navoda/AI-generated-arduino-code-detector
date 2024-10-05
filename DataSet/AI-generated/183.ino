// Define RGB LED pins
#define RED_PIN 6   // Red LED connected to pin 6
#define GREEN_PIN 5 // Green LED connected to pin 5
#define BLUE_PIN 3  // Blue LED connected to pin 3

// Define potentiometer pin
#define POT_PIN A2  // Potentiometer connected to A2

void setup() {
  // Initialize RGB LED pins as outputs
  pinMode(RED_PIN, OUTPUT);
  pinMode(GREEN_PIN, OUTPUT);
  pinMode(BLUE_PIN, OUTPUT);

  // Initialize the potentiometer pin as input
  pinMode(POT_PIN, INPUT);

  // Initialize serial communication (optional for debugging)
  Serial.begin(9600);

  // Seed the random number generator using an unconnected analog pin
  randomSeed(analogRead(A3));

  Serial.println("Potentiometer RGB Random Brightness Example - DFRobot Accessory Shield");
}

void loop() {
  // Read the potentiometer value (0-1023)
  int potValue = analogRead(POT_PIN);

  // Map the potentiometer value to a delay range (100 - 1000 ms)
  int delayTime = map(potValue, 0, 1023, 100, 1000);

  // Generate random brightness values for each color (0-255)
  int redValue = random(0, 256);
  int greenValue = random(0, 256);
  int blueValue = random(0, 256);

  // Set the RGB LED to random brightness levels
  analogWrite(RED_PIN, redValue);
  analogWrite(GREEN_PIN, greenValue);
  analogWrite(BLUE_PIN, blueValue);

  // Optional: Print the potentiometer and RGB values to the Serial Monitor
  Serial.print("Potentiometer: ");
  Serial.print(potValue);
  Serial.print("\tRed: ");
  Serial.print(redValue);
  Serial.print("\tGreen: ");
  Serial.print(greenValue);
  Serial.print("\tBlue: ");
  Serial.print(blueValue);
  Serial.print("\tDelay: ");
  Serial.println(delayTime);

  // Wait for the delay based on the potentiometer value
  delay(delayTime);
}
