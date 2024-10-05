#include <Wire.h>
#include <ACE128.h>

// Set the address of your module
#define ACE_ADDR 0x20 

ACE128 encoder(ACE_ADDR);  // Create an encoder object with the specified address

void setup() {
    Serial.begin(9600);  // Start serial communication at 9600 baud
    Wire.begin();        // Initialize I2C communication
    encoder.begin();     // Initialize the encoder
    Serial.println("ACE128 Demonstrator Started");
}

void loop() {
    // Update the encoder readings
    encoder.update();

    // Read and display values
    int pinValue = encoder.read();        // Raw gray-code from the pins
    int rawValue = encoder.getRaw();      // Mapped output (0-127)
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

    // Check if pin 13 is grounded to reset logical zero
    if (digitalRead(13) == LOW) {
        encoder.setLogicalZero(); // Set the logical zero based on current position
        Serial.println("Logical zero set.");
    }

    delay(100);  // Short delay for readability
}
