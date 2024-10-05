//——————————————————————————————————————————————————————————————————————————————
//  ACAN2515 / ACAN Demo
//  ACAN2515 uses hardware SPI and an external interrupt pin
//  This sketch runs only on a Teensy 3.x
//  It uses the Teensy 3.x builtin CAN0 interface for testing intensive
//  communication with a MCP2515 CAN controller.
//  The builtin CAN0 interface and the MCP2515 controller should be connected
//  through transceivers.
//  Note that the Tx and Rx alternate pins are used for the Teensy builtin CAN0.
//——————————————————————————————————————————————————————————————————————————————

#include <ACAN2515.h>

// Define the pins for MCP2515 connections
const int MCP2515_CS = 10;   // Chip Select pin
const int MCP2515_INT = 2;   // Interrupt pin

// Create an instance of the ACAN2515 class
ACAN2515 can(MCP2515_CS, MCP2515_INT);

void setup() {
  // Start serial communication
  Serial.begin(115200);
  while (!Serial) { ; } // Wait for serial port to connect
  
  // Start CAN communication
  if (!can.begin()) {
    Serial.println("Failed to initialize CAN interface!");
    while (1) { ; } // Halt the program if CAN initialization fails
  }
  
  // Set the CAN controller to operate at 500 kbps
  can.setBitrate(500000);

  // Set CAN filters and masks if necessary
  // can.setFilters(...);
  
  // Start listening for CAN messages
  can.enableFIFO();
}

void loop() {
  // Check for incoming CAN messages
  if (can.receive()) {
    CANMessage message;
    if (can.getMessage(message)) {
      Serial.print("Message received: ");
      Serial.print("ID: ");
      Serial.print(message.id, HEX);
      Serial.print(" Data: ");
      for (int i = 0; i < message.length; i++) {
        Serial.print(message.data[i], HEX);
        Serial.print(" ");
      }
      Serial.println();
    }
  }
  
  // Create a test CAN message and send it
  CANMessage testMessage;
  testMessage.id = 0x123;
  testMessage.length = 8;
  for (int i = 0; i < testMessage.length; i++) {
    testMessage.data[i] = i;
  }
  
  if (can.send(testMessage)) {
    Serial.println("Test message sent!");
  } else {
    Serial.println("Failed to send test message!");
  }

  delay(1000); // Wait for 1 second before sending the next message
}
