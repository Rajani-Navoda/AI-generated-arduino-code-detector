/*
  LoopBackDemo for Teensy 4.x CAN3 in CANFD Mode
  Configures the CAN3 module in loopback mode with CANFD enabled.
  The module will internally receive every CANFD frame it sends.
  
  No external hardware is required.
*/

#include <FlexCAN_T4.h>

// Create an instance of the FlexCAN library for CAN3
FlexCAN_T4<CAN3, RX_SIZE_256, TX_SIZE_16> CAN3;

// Define CANFD message object
CAN_message_t message;

void setup() {
  Serial.begin(115200); // Initialize serial communication at 115200 baud

  // Initialize CAN3 with default settings
  CAN3.begin();

  // Set CAN3 to loopback mode
  CAN3.setLoopBackMode(true);
  
  // Enable CANFD mode for CAN3
  CAN3.setCANFDMode(true);

  // Set the CANFD data phase bitrate (e.g., 2 Mbps)
  CAN3.setCANFDBaudRate(2000000); // 2 Mbps
  
  // Optionally, configure the standard bitrate if needed
  // CAN3.setBitRate(500000); // For example, set to 500 kbps for arbitration phase

  Serial.println("CAN3 Initialized and Loopback Mode with CANFD Enabled.");
}

void loop() {
  // Prepare a CANFD message
  message.id = 0x123; // CAN message ID
  message.len = 8;   // Message length (data length code)
  for (int i = 0; i < message.len; i++) {
    message.buf[i] = i + 1; // Fill message data with incremental values starting from 1
  }
  message.flags = CANFD; // Mark the message as CANFD

  // Send the CANFD message
  CAN3.write(message);

  // Check for received messages
  if (CAN3.read(message)) {
    Serial.print("Received CANFD message ID: 0x");
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
