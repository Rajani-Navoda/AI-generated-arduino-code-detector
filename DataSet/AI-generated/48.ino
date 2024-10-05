/*
  ACAN2517FD Demo in loopback mode for Arduino Uno (without INT pin)
  This sketch demonstrates using the MCP2517FD in loopback mode without using the interrupt pin.
  
  Connections:
  - MCP2517FD SCK pin -> Arduino Uno pin 13
  - MCP2517FD MOSI pin -> Arduino Uno pin 11
  - MCP2517FD MISO pin -> Arduino Uno pin 12
  - MCP2517FD CS pin -> Arduino Uno pin 10
  
  This sketch assumes the use of the ACAN2517FD library.
*/

#include <ACAN2517FD.h>

// MCP2517FD connections
const uint8_t MCP2517FD_CS = 10; // Chip Select pin

// Create an instance of the ACAN2517FD class
ACAN2517FD can(MCP2517FD_CS);

void setup() {
  Serial.begin(115200); // Initialize serial communication at 115200 baud
  
  // Initialize MCP2517FD
  Serial.println("Initializing MCP2517FD...");
  if (!can.begin(500000)) { // Initialize CAN bus with 500 kbps baud rate
    Serial.println("Failed to initialize MCP2517FD");
    while (1); // Halt execution if initialization fails
  }
  can.setLoopbackMode(true); // Enable loopback mode
  
  Serial.println("MCP2517FD Initialized and Loopback Mode Enabled.");
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
