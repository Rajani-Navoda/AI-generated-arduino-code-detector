/*
  ACAN2517 Loopback Demo for Teensy 3.5
  This sketch configures the MCP2517 CAN controller in loopback mode.
  No external interrupt is used.
  
  MCP2517 connections:
    SCK input of MCP2517 is connected to pin #32
    SDI input of MCP2517 is connected to pin #0
    SDO output of MCP2517 is connected to pin #1
    CS (Chip Select) input of MCP2517 should be connected to pin #10 (or any digital output pin)
*/

#include <ACAN2517.h>

// Define pin numbers
const uint8_t CS_PIN = 10;  // Chip Select pin

// Create an instance of the ACAN2517 class
ACAN2517 canBus(CS_PIN);

// Define a CAN message object
CANMessage message;

void setup() {
  Serial.begin(115200); // Initialize serial communication at 115200 baud

  // Initialize CAN bus
  if (!canBus.begin()) {
    Serial.println("Failed to initialize CAN bus.");
    while (1); // Halt if initialization fails
  }

  // Set CAN controller to loopback mode
  canBus.setLoopBack(true);

  Serial.println("CAN Bus Initialized and Loopback Mode Enabled.");
}

void loop() {
  // Prepare a CAN message
  message.id = 0x123; // CAN message ID (change as needed)
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
