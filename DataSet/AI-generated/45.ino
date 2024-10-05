//——————————————————————————————————————————————————————————————————————————————
//  ACAN2515 Demo in loopback mode for Adafruit Feather M0
//——————————————————————————————————————————————————————————————————————————————

#include <ACAN2515.h>
#include <wiring_private.h>

// MCP2515 connections
const uint8_t MCP2515_CS = 9; // Chip Select pin for MCP2515
const uint8_t MCP2515_INT = 8; // Interrupt pin for MCP2515

// Create an instance of the ACAN2515 class
ACAN2515 can1(MCP2515_CS, MCP2515_INT);

// CAN message to be sent and received
CANMessage message;

void setup() {
  Serial.begin(115200); // Initialize serial communication at 115200 baud
  
  // Initialize MCP2515
  Serial.println("Initializing MCP2515...");
  can1.begin(500000); // Initialize CAN bus with 500 kbps baud rate
  can1.setLoopbackMode(true); // Enable loopback mode

  // Configure the CAN message
  message.id = 0x123; // CAN message ID
  message.length = 8; // Message length
  for (int i = 0; i < 8; i++) {
    message.data[i] = i; // Fill message data with incremental values
  }

  Serial.println("MCP2515 Initialized and Loopback Mode Enabled.");
}

void loop() {
  // Send the CAN message
  can1.send(message);
  
  // Check for received messages
  if (can1.receive(message)) {
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
