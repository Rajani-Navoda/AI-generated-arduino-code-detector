#include <Wire.h>
#include <ACE128.h>

// Set the address of your module
#define ACE_ADDR 0x20 

ACE128 encoder(ACE_ADDR);  // Create an encoder object with the specified address

void setup() {
    Serial.begin(9600);  // Start serial communication at 9600 baud
    Wire.begin();        // Initialize I2C communication
    encoder.begin();     // Initialize the encoder
    Serial.println("ACE128 Basic Test Started");
}

void loop() {
    // Update the encoder readings
    encoder.update();

    // Read and display values
    int posValue = encoder.getPosition(); // Position in range -64 to +63
    int uposValue = encoder.getUPosition(); // Position in range 0 to 127
    int mposValue = encoder.getMPosition(); // Multiturn position -32768 to +32767

    // Print the values to the Serial Monitor
    Serial.print("pos = ");
    Serial.print(posValue);
    Serial.print("\tupos = ");
    Serial.print(uposValue);
    Serial.print("\tmpos = ");
    Serial.println(mposValue);

    delay(100);  // Short delay for readability
}
