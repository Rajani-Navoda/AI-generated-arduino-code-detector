/*
  LoopBackDemo for Teensy 4.x CAN3
  Configures the CAN3 module in loopback mode.
  The module will internally receive every CAN frame it sends.
  
  No external hardware is required.
*/

#include <FlexCAN_T4.h>

// Create an instance of the FlexCAN library for CAN3
FlexCAN_T4<CAN3, RX_SIZE_256, TX_SIZE_16> CAN3;

// Define CAN message object
CAN_message_t message;

void setup() {
  Serial.begin(115200); // Initialize serial communication at 115200 baud

  // Initialize CAN3 with default settings
  CAN3.begin();

  // Set CAN3 to loopback mode
  CAN3.setLoopBackMode(true);
  
  // Optionally, configure the bitrate if needed
  // CAN3.setBaudRate(500000); // For example, set to 500 kbps
  
  Serial.println("CAN3 Initialized and Loopback Mode Enabled.");
}

void loop() {
  // Prepare a CAN message
  message.id = 0x789; // CAN message ID
  message.len = 8; // Message length
  for (int i = 0; i < message.len; i++) {
    message.buf[i] = i + 1; // Fill message data with incremental values starting from 1
  }

  // Send the CAN message
  CAN3.write(message);

  // Check for received messages
  if (CAN3.read(message)) {
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
