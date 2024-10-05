#include <FlexCAN.h>

FlexCAN CAN0(500000); // Initialize CAN0 with 500 kbps
FlexCAN CAN1(500000); // Initialize CAN1 with 500 kbps

// Define CAN message
CAN_message_t txMsg;
CAN_message_t rxMsg;

void setup() {
  // Initialize Serial for debugging
  Serial.begin(9600);
  while (!Serial) {
    ; // Wait for Serial to be ready
  }

  // Initialize CAN0 and CAN1
  CAN0.begin();
  CAN1.begin();

  // Set CAN0 and CAN1 pins
  CAN0.setPins(3, 4); // CAN0TX: pin #3, CAN0RX: pin #4
  CAN1.setPins(33, 34); // CAN1TX: pin #33, CAN1RX: pin #34

  // Configure CAN0 and CAN1
  CAN0.setBaudRate(500000);
  CAN1.setBaudRate(500000);

  // Set CAN0 and CAN1 to open-collector and enable pullups
  CAN0.setFilter(0x000, 0x000);
  CAN1.setFilter(0x000, 0x000);
  
  // Set up message for sending
  txMsg.id = 0x123; // CAN ID
  txMsg.len = 8; // Data length
  for (int i = 0; i < 8; i++) {
    txMsg.buf[i] = i; // Example data
  }

  // Start sending messages
  CAN0.sendMessage(txMsg);
}

void loop() {
  // Check if there's a message available
  if (CAN1.readMessage(rxMsg)) {
    // Print the received message
    Serial.print("Received message ID: ");
    Serial.print(rxMsg.id, HEX);
    Serial.print(" Data: ");
    for (int i = 0; i < rxMsg.len; i++) {
      Serial.print(rxMsg.buf[i], HEX);
      Serial.print(" ");
    }
    Serial.println();
  }

  // Send a new message every 1 second
  delay(1000);
  CAN0.sendMessage(txMsg);
}
