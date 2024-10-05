/*
  ACAN2517FD Demo in Loopback Mode for ESP32
  Configures the ACAN2517FD CAN controller in loopback mode without using an interrupt pin.
  The module will internally receive every CAN frame it sends.
  
  No external hardware is required.
*/

#include <ACAN2517FD.h>

// Define CAN bus settings
const uint32_t CAN_SPEED = 1000000; // 1 Mbps

// Create an instance of the ACAN2517FD class
// Define pins: SPI CS, SPI SCK, SPI MISO, SPI MOSI
ACAN2517FD canBus(5, 18, 19, 23); // Example pins: adjust as needed

// Define CANFD message object
CANFDMessage message;

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
  // Prepare a CANFD message
  message.id = 0x123; // CAN message ID
  message.length = 8; // Message length
  for (int i = 0; i < message.length; i++) {
    message.data[i] = i + 1; // Fill message data with incremental values starting from 1
  }
  message.flags = CANFD; // Mark the message as CANFD

  // Send the CANFD message
  if (!canBus.write(message)) {
    Serial.println("Failed to send CANFD message.");
  }

  // Check for received messages
  while (canBus.read(message)) {
    Serial.print("Received CANFD message ID: 0x");
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
