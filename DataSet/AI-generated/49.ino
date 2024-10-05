/*
  ACAN2515 Demo in loopback mode for Arduino
  This sketch demonstrates using the MCP2515 in loopback mode
  with explicit bit rate settings.
  
  Connections:
  - MCP2515 SCK pin -> Arduino pin 13
  - MCP2515 MOSI pin -> Arduino pin 11
  - MCP2515 MISO pin -> Arduino pin 12
  - MCP2515 CS pin -> Arduino pin 10
  - MCP2515 INT pin -> Arduino pin 2 (for interrupts)
  
  This sketch assumes the use of the ACAN2515 library.
*/

#include <ACAN2515.h>

// MCP2515 connections
const uint8_t MCP2515_CS = 10; // Chip Select pin
const uint8_t MCP2515_INT = 2; // Interrupt pin

// Create an instance of the ACAN2515 class with explicit bit rate settings
ACAN2515Settings settings(500000); // 500 kbps bit rate
ACAN2515 can(MCP2515_CS, MCP2515_INT);

void setup() {
  Serial.begin(115200); // Initialize serial communication at 115200 baud
  
  // Initialize MCP2515
  Serial.println("Initializing MCP2515...");
  if (!can.begin(settings)) { // Initialize CAN bus with specified settings
    Serial.println("Failed to initialize MCP2515");
    while (1); // Halt execution if initialization fails
  }
  can.setLoopbackMode(true); // Enable loopback mode
  
  Serial.println("MCP2515 Initialized and Loopback Mode Enabled.");
}

void loop() {
  // Create a CAN message
  CANMessage message;
  message.id = 0x123; // CAN message ID
  message.length = 8; // Message length
  for (int i = 0; i < 8; i++) {
    message.data[i] = i; // Fill message data with incremental values
  }

  // Send the CAN message
  can.send(message);
  
  // Check for received messages
  if (can.receive(message)) {
    Serial.print("Received CAN message ID: 0x");
    Serial.print(message.id, HEX);
    Serial.print(", Data: ");
    for (int i = 0; i < message.length; i++) {
      Serial.print(message.data[i], HEX);
      Serial.print(" ");
    }
    Serial.println();
  }

  // Delay before sending the next message
  delay(1000); // 1 second delay
}
