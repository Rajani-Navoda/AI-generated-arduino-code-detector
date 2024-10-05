/*
  LoopBackDemo for Teensy 4.x CAN1
  Configures the CAN1 module in loopback mode with a 615 kbps bitrate.
  The module will internally receive every CAN frame it sends.
  
  No external hardware is required.
*/

#include <FlexCAN_T4.h>

// Create an instance of the FlexCAN library for CAN1
FlexCAN_T4<CAN1, RX_SIZE_256, TX_SIZE_16> CAN1;

// CAN bit rate settings
const uint32_t CAN_BITRATE = 615000; // 615 kbps

void setup() {
  Serial.begin(115200); // Initialize serial communication at 115200 baud

  // Initialize CAN1 with the specified bit rate
  CAN1.begin();
  CAN1.setBaudRate(CAN_BITRATE);
  
  // Set CAN1 to loopback mode
  CAN1.setLoopBackMode(true);
  
  Serial.println("CAN1 Initialized and Loopback Mode Enabled at 615 kbps.");
}

void loop() {
  // Create a CAN message
  CAN_message_t message;
  message.id = 0x123; // CAN message ID
  message.len = 8; // Message length
  for (int i = 0; i < message.len; i++) {
    message.buf[i] = i; // Fill message data with incremental values
  }

  // Send the CAN message
  CAN1.write(message);

  // Check for received messages
  if (CAN1.read(message)) {
    Serial.print("Received CAN message ID: 0x");
    Serial.print(message.id, HEX);
    Serial.print(", Data: ");
    for (int i = 0; i < message.len; i++) {
      Serial.print(message.buf[i], HEX);
      Serial.print(" ");
    }
    Serial.println();
  }

  // Delay before sending the next message
  delay(1000); // 1 second delay
}
