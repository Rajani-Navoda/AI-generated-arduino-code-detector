// Pin Definitions
const int ledPin = 13;       // Pin for the LED (flashing light)
const int buzzerPin = 8;     // Pin for the buzzer (siren)

void setup() {
  pinMode(ledPin, OUTPUT);   // Set LED pin as an output
  pinMode(buzzerPin, OUTPUT); // Set buzzer pin as an output
}

void loop() {
  // Flash the LED
  for (int i = 0; i < 10; i++) {
    digitalWrite(ledPin, HIGH); // Turn LED on
    tone(buzzerPin, 1000);      // Play siren sound at 1000 Hz
    delay(100);                 // Wait for 100 ms
    digitalWrite(ledPin, LOW);  // Turn LED off
    noTone(buzzerPin);          // Stop the siren sound
    delay(100);                 // Wait for 100 ms
  }
  
  // Create a longer break
  delay(1000); // Wait for 1 second
}
