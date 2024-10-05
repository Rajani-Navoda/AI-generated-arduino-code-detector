#include <FlexCAN.h>

// Define CAN bus speed
#define CAN_BUS_SPEED 500000

// Create a FlexCAN object
FlexCAN CANbus;

// Define CAN message object ID
const uint32_t CAN_ID = 0x123;

void setup() {
  // Initialize serial communication
  Serial.begin(9600);
  
  // Initialize FlexCAN
  CANbus.begin(CAN_BUS_SPEED);

  // Configure CAN message object
  CANbus.setFilter(CAN_ID, CAN_ID);
  
  // Set CAN module to loopback mode
  CANbus.setLoopback(true);

  // Start CAN bus
  CANbus.enableFIFO();
  CANbus.enable();
}

void loop() {
  // Create a CAN message
  CAN_message_t msg;
  msg.id = CAN_ID;
  msg.len = 8; // Number of data bytes
  for (int i = 0; i < msg.len; i++) {
    msg.buf[i] = i; // Fill with test data
  }
  
  // Send the CAN message
  CANbus.write(msg);

  // Print sent message to serial monitor
  Serial.print("Sent message with ID: ");
  Serial.print(msg.id, HEX);
  Serial.print(" Data: ");
  for (int i = 0; i < msg.len; i++) {
    Serial.print(msg.buf[i], HEX);
    Serial.print(" ");
  }
  Serial.println();
  
  // Wait for the message to be received
  delay(100);

  // Check if a message was received
  if (CANbus.available()) {
    CAN_message_t rxMsg;
    CANbus.read(rxMsg);
    
    // Print received message to serial monitor
    Serial.print("Received message with ID: ");
    Serial.print(rxMsg.id, HEX);
    Serial.print(" Data: ");
    for (int i = 0; i < rxMsg.len; i++) {
      Serial.print(rxMsg.buf[i], HEX);
      Serial.print(" ");
    }
    Serial.println();
  }

  // Wait before sending the next message
  delay(1000);
}
