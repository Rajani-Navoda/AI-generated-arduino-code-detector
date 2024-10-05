/*
  ACAN2515 Demo in Loopback Mode for Arduino
  Configures the ACAN2515 CAN controller in loopback mode.
  This example uses hardware SPI and does not use an interrupt pin.
  
  Note: Adjust the pin assignments and CAN speed according to your hardware setup.
*/

#include <SPI.h>
#include <ACAN2515.h>

// Define CAN speed
const uint32_t CAN_SPEED = 500000; // 500 kbps

// Create an instance of the ACAN2515 class
// Define pins: SPI CS, SPI SCK, SPI MISO, SPI MOSI
// Adjust these pin numbers based on your Arduino board setup
ACAN2515 canBus(10); // Example CS pin: adjust as needed

// Define CAN message object
CANMessage message;

void setup() {
  Serial.begin(115200); // Initialize serial communication at 115200 baud

  // Initialize CAN bus with specified settings
  if (!canBus.begin(CAN_SPEED)) {
    Serial.println("Failed to initialize CAN bus.");
    while (1); // Halt if initialization fails
  }

  // Set CAN controller to loopback mode
  canBus.setLoopBack(true);

  Serial.println("CAN Bus Initialized and Loopback Mode Enabled.");
}

void loop() {
  // Prepare a CAN message
  message.id = 0x123; // CAN message ID
  message.length = 8; // Message length
  for (int i = 0; i < message.length; i++) {
    message.data[i] = i + 1; // Fill message data with incremental values starting from 1
  }

  // Send the CAN message
  if (!canBus.write(message)) {
    Serial.println("Failed to send CAN message.");
  }

  // Check for received messages
  if (canBus.available()) {
    if (canBus.read(message)) {
      Serial.print("Received CAN message ID: 0x");
      Serial.print(message.id, HEX);
      Serial.print(", Data: ");
      for (int i = 0; i < message.length; i++) {
        Serial.print(message.data[i], HEX);
        Serial.print(" ");
      }
      Serial.println();
    }
  }

  // Delay before sending the next message
  delay(1000); // 1 second delay
}
