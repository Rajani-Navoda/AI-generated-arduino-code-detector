#include <Arduino.h>
#include <CRC32.h> // Assuming you have a CRC32 library

void setup() {
    Serial.begin(115200);
    while (!Serial); // Wait for serial connection

    String data = "Hello, CRC!";
    Serial.print("Original data: ");
    Serial.println(data);

    // Calculate CRC
    uint32_t crc = CRC32::calculate(data.c_str(), data.length());
    Serial.print("CRC32: ");
    Serial.println(crc, HEX); // Print CRC in hexadecimal format

    // Simulating sending data and CRC
    // In a real application, you'd send both over a communication channel.

    // Verification
    uint32_t receivedCrc = crc; // Simulating received CRC
    if (CRC32::validate(data.c_str(), data.length(), receivedCrc)) {
        Serial.println("CRC validation successful!");
    } else {
        Serial.println("CRC validation failed!");
    }
}

void loop() {
    // No ongoing operations
}
