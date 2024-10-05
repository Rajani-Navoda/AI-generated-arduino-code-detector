//——————————————————————————————————————————————————————————————————————————————
//  ACAN2515Tiny Demo in loopback mode
//  This sketch is designed for a Teensy 3.5, using SPI0 (named SPI)
//——————————————————————————————————————————————————————————————————————————————

#include <ACAN2515Tiny.h>

//——————————————————————————————————————————————————————————————————————————————
//  MCP2515 connections: adapt these settings to your design
//  This sketch is designed for a Teensy 3.5, using SPI0 (named SPI)
//  But standard Teensy 3.5 SPI0 pins are not used
//    SCK input of MCP2515 is connected to pin #27
//    SI input of MCP2515 is connected to pin #28
//    SO output of MCP2515 is connected to pin #39
//  User code should configure MCP2515_IRQ pin as external interrupt
//——————————————————————————————————————————————————————————————————————————————

const int MCP2515_CS = 10;  // Chip Select pin for MCP2515
const int MCP2515_IRQ = 2;  // Interrupt pin for MCP2515

// Create an instance of the ACAN2515Tiny class
ACAN2515Tiny can(MCP2515_CS, MCP2515_IRQ);

void setup() {
  // Start serial communication for debugging
  Serial.begin(115200);
  while (!Serial) { ; } // Wait for serial port to connect

  // Initialize CAN controller
  if (!can.begin()) {
    Serial.println("Failed to initialize CAN interface!");
    while (1) { ; } // Halt the program if CAN initialization fails
  }

  // Enable loopback mode
  can.setLoopbackMode(true);

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
