/*
  LoopBackDemo

  This demo runs on Teensy 3.1 / 3.2, 3.5, and 3.6
  The FlexCAN module is configured in loopback mode: it internally receives
  every CAN frame it sends.

  No external hardware required.
*/

#include <FlexCAN.h>

FlexCAN CANbus; // Create an instance of the FlexCAN class

void setup() {
  Serial.begin(115200); // Initialize serial communication

  // Initialize CAN bus in loopback mode
  CANbus.begin();
  CANbus.setBaudRate(500000); // Set CAN baud rate to 500 kbps
  CANbus.setLoopback(); // Enable loopback mode
  CANbus.enableFIFO(); // Enable FIFO for message reception
  
  Serial.println("CAN Loopback Demo Started");
}

void loop() {
  // Create a CAN message
  CAN_message_t message;
  message.id = 0x123; // Set CAN message ID
  message.ext = 0;    // Standard frame
  message.len = 8;    // Set message length
  for (int i = 0; i < 8; i++) {
    message.buf[i] = i; // Fill the message buffer with incremental values
  }

  // Send the CAN message
  CANbus.write(message);

  // Check if a message is available in the FIFO
  if (CANbus.available()) {
    CAN_message_t receivedMessage;
    CANbus.read(receivedMessage); // Read the message from FIFO

    // Print the received message details
    Serial.print("Received CAN message ID: 0x");
    Serial.print(receivedMessage.id, HEX);
    Serial.print(", Data: ");
    for (int i = 0; i < receivedMessage.len; i++) {
      Serial.print(receivedMessage.buf[i], HEX);
      Serial.print(" ");
    }
    Serial.println();
  }

  // Delay before sending the next message
  delay(1000); // 1 second delay
}
