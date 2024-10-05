// Define the RGB LED pin numbers on the DFRobot Accessory Shield
#define RED_PIN 6   // Pin connected to the Red LED
#define GREEN_PIN 5 // Pin connected to the Green LED
#define BLUE_PIN 3  // Pin connected to the Blue LED

void setup() {
  // Initialize RGB LED pins as outputs
  pinMode(RED_PIN, OUTPUT);
  pinMode(GREEN_PIN, OUTPUT);
  pinMode(BLUE_PIN, OUTPUT);

  // Start serial communication
  Serial.begin(9600);
  Serial.println("RGB Serial Control");
  Serial.println("Enter values in R,G,B format (0-255 for each color)");
}

void loop() {
  // Check if data is available on the Serial Monitor
  if (Serial.available()) {
    String input = Serial.readStringUntil('\n');  // Read until newline
    input.trim();  // Remove any leading/trailing whitespace
    
    // Parse the input
    int comma1 = input.indexOf(',');  // Find the first comma
    int comma2 = input.indexOf(',', comma1 + 1);  // Find the second comma
    
    if (comma1 > 0 && comma2 > 0) {
      // Extract RGB values as substrings and convert them to integers
      int red = input.substring(0, comma1).toInt();
      int green = input.substring(comma1 + 1, comma2).toInt();
      int blue = input.substring(comma2 + 1).toInt();
      
      // Check if the values are within range (0-255)
      if (red >= 0 && red <= 255 && green >= 0 && green <= 255 && blue >= 0 && blue <= 255) {
        // Set the RGB LED color
        setColor(red, green, blue);
        
        // Provide feedback to the Serial Monitor
        Serial.print("Setting RGB to: ");
        Serial.print("R=");
        Serial.print(red);
        Serial.print(", G=");
        Serial.print(green);
        Serial.print(", B=");
        Serial.println(blue);
      } else {
        Serial.println("Error: RGB values must be between 0 and 255.");
      }
    } else {
      Serial.println("Error: Please enter values in R,G,B format.");
    }
  }
}

// Function to set RGB color
void setColor(int red, int green, int blue) {
  analogWrite(RED_PIN, red);
  analogWrite(GREEN_PIN, green);
  analogWrite(BLUE_PIN, blue);
}
