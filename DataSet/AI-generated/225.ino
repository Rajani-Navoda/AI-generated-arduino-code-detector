#include <ACE128.h>  // Include the ACE128 library

#define ACE128_ARDUINO_PINS  // Uncomment this for Arduino pin mapping

ACE128 encoder;  // Create an encoder object

void setup() {
    Serial.begin(9600);  // Start serial communication
    encoder.begin();  // Initialize the encoder
}

void loop() {
    // Update the encoder
    encoder.update();

    // Read the current values
    int pinValue = encoder.read();      // Raw gray-code from the pins
    int rawValue = encoder.getRaw();    // Mapped output (0-127)
    int posValue = encoder.getPosition(); // Position in range -64 to +63
    int uposValue = encoder.getUPosition(); // Position in range 0 to 127
    int mposValue = encoder.getMPosition(); // Multiturn position -32768 to +32767

    // Print the values to the Serial Monitor
    Serial.print("pin = ");
    Serial.print(pinValue);
    Serial.print("\traw = ");
    Serial.print(rawValue);
    Serial.print("\tpos = ");
    Serial.print(posValue);
    Serial.print("\tupos = ");
    Serial.print(uposValue);
    Serial.print("\tmpos = ");
    Serial.println(mposValue);

    delay(100);  // Short delay for readability
}
