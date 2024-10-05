/*
  ACAN2517FD Filter Demo in Loopback Mode for Teensy 3.5
  This sketch tests extended receive filters with the MCP2517FD in loopback mode.
  
  MCP2517FD connections:
    SCK input of MCP2517FD is connected to pin #32
    SDI input of MCP2517FD is connected to pin #0
    SDO output of MCP2517FD is connected to pin #1
    CS (Chip Select) input of MCP2517FD is connected to pin #10 (or any digital output pin)
    INT (Interrupt) output of MCP2517FD is connected to pin #2 (or any digital input pin with interrupt capability)
  
  Note: Adjust the pin assignments and CAN speed according to your hardware setup.
*/

#include <ACAN2517FD.h>

// Define pin numbers
const uint8_t CS_PIN = 10;  // Chip Select pin
const uint8_t INT_PIN = 2;  // Interrupt pin

// Create an instance of the ACAN2517FD class
ACAN2517FD canBus(CS_PIN, INT_PIN);

// Define CAN message object
CANMessage message;

// Define extended filters
const uint32_t FILTER_ID1 = 0x12345678; // Example extended filter ID
const uint32_t FILTER_ID2 = 0x87654321; // Another example extended filter ID

void setup() {
  Serial.begin(115200); // Initialize serial communication at 115200 baud

  // Initialize CAN bus with default settings
  if (!canBus.begin()) {
    Serial.println("Failed to initialize CAN bus.");
    while (1); // Halt if initialization fails
  }

  // Set CAN controller to loopback mode
  canBus.setLoopBack(true);

  // Configure extended receive filters
  canBus.setFilter(0, FILTER_ID1, 0xFFFFFFFF); // Filter 0 with ID1, mask for exact match
  canBus.setFilter(1, FILTER_ID2, 0xFFFFFFFF); // Filter 1 with ID2, mask for exact match

  // Attach interrupt service routine for CAN message reception
  attachInterrupt(digitalPinToInterrupt(INT_PIN), onCanMessageReceived, FALLING);

  Serial.println("CAN Bus Initialized, Loopback Mode Enabled, and Filters Configured.");
}

void loop() {
  // Prepare a CAN message
  message.id = 0x12345678; // CAN message ID (change as needed)
  message.length = 8; // Message length
  for (int i = 0; i < message.length; i++) {
    message.data[i] = i + 1; // Fill message data with incremental values starting from 1
  }

  // Send the CAN message
  if (!canBus.write(message)) {
    Serial.println("Failed to send CAN message.");
  }

  // Delay before sending the next message
  delay(1000); // 1 second delay
}

// Interrupt service routine for CAN message reception
void onCanMessageReceived() {
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
