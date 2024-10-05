/*
  ACAN2517 Demo in loopback mode for Arduino Uno
  This sketch demonstrates using the MCP2517FD in loopback mode.
  
  Connections:
  - MCP2517FD SCK pin -> Arduino Uno pin 13
  - MCP2517FD MOSI pin -> Arduino Uno pin 11
  - MCP2517FD MISO pin -> Arduino Uno pin 12
  - MCP2517FD CS pin -> Arduino Uno pin 10
  - MCP2517FD INT pin -> Arduino Uno pin 2 (optional, for interrupts)
  
  This sketch assumes the use of the ACAN2517 library.
*/

#include <ACAN2517.h>

// MCP2517FD connections
const uint8_t MCP2517FD_CS = 10; // Chip Select pin
const uint8_t MCP2517FD_INT = 2; // Interrupt pin (optional)

// Create an instance of the ACAN2517 class
ACAN2517 can(MCP2517FD_CS, MCP2517FD_INT);

void setup() {
  Serial.begin(115200); // Initialize serial communication at 115200 baud
  
  // Initialize MCP2517FD
  Serial.println("Initializing MCP2517FD...");
  if (!can.begin(500000)) { // Initialize CAN bus with 500 kbps baud rate
    Serial.println("Failed to initialize MCP2517FD");
    while (1);
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
