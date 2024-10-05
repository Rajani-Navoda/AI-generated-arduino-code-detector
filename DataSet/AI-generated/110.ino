//——————————————————————————————————————————————————————————————————————————————
//  ACAN2515Tiny Demo in loopback mode for Adafruit Feather M0
//——————————————————————————————————————————————————————————————————————————————

#include <ACAN2515Tiny.h>
#include <wiring_private.h>

//——————————————————————————————————————————————————————————————————————————————
//  MCP2515 connections: adapt these settings to your design
//  This sketch is designed for an Adafruit Feather M0, using SERCOM1
//  Standard Adafruit Feather M0 SPI pins are not used
//    SCK input of MCP2515 is connected to pin #12
//    SI input of MCP2515 is connected to pin #11
//    SO output of MCP2515 is connected to pin #10
//  - output pin for CS (MCP2515_CS)
//  - interrupt input pin for INT (MCP2515_INT)
//——————————————————————————————————————————————————————————————————————————————

const int MCP2515_CS = 9;    // Chip Select pin for MCP2515
const int MCP2515_INT = 2;   // Interrupt pin for MCP2515

// Create an instance of the ACAN2515Tiny class
ACAN2515Tiny can(MCP2515_CS, MCP2515_INT);

void setup() {
  // Start serial communication for debugging
  Serial.begin(115200);
  while (!Serial) { ; } // Wait for serial port to connect

  // Initialize CAN controller
  if (!can.begin()) {
    Serial.println("Failed to initialize CAN interface!");
    while (1) { ; } // Halt the program if CAN initialization fails
  }

  // Set the CAN bitrate to 500 kbps
  can.setBitrate(500000);

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

