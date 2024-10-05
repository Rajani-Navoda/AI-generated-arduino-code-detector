/*
  ACAN2517 Demo in Loopback Mode for Teensy 3.5
  Using hardware SPI1 and an external interrupt for CAN message reception.
  
  MCP2517 connections:
    SCK input of MCP2517 is connected to pin #32
    SDI input of MCP2517 is connected to pin #0
    SDO output of MCP2517 is connected to pin #1
    CS (Chip Select) input of MCP2517 is connected to pin #10 (or any digital output pin)
    INT (Interrupt) output of MCP2517 is connected to pin #2 (or any digital input pin with interrupt capability)
  
  Note: Adjust the pin assignments and CAN speed according to your hardware setup.
*/

#include <ACAN2517.h>

// Define pin numbers
const uint8_t CS_PIN = 10;  // Chip Select pin
const uint8_t INT_PIN = 2;  // Interrupt pin

// Create an instance of the ACAN2517 class
ACAN2517 canBus(CS_PIN, INT_PIN);

// Define CAN message object
CANMessage message;

void setup() {
  Serial.begin(115200); // Initialize serial communication at 115200 baud

  // Initialize CAN bus with default settings
  if (!canBus.begin()) {
    Serial.println("Failed to initialize CAN bus.");
    while (1); // Halt if initialization fails
  }

  // Set CAN controller to loopback mode
  canBus.setLoopBack(true);

  // Attach interrupt service routine for CAN message reception
  attachInterrupt(digitalPinToInterrupt(INT_PIN), onCanMessageReceived, FALLING);

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
