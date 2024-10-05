//——————————————————————————————————————————————————————————————————————————————
//  ACAN2515Tiny Demo in loopback mode
//  Example with ACAN2515TinySettings constructor with explicit bit rate settings
//——————————————————————————————————————————————————————————————————————————————

#include <ACAN2515Tiny.h>

//——————————————————————————————————————————————————————————————————————————————
//  MCP2515 connections:
//    - standard SPI pins for SCK, MOSI and MISO
//    - a digital output for CS
//    - interrupt input pin for INT
//——————————————————————————————————————————————————————————————————————————————

// Define MCP2515 connections
const int MCP2515_CS = 10;    // Chip Select pin for MCP2515
const int MCP2515_INT = 2;    // Interrupt pin for MCP2515

// Create an instance of the ACAN2515Tiny class
// Define the bit rate and other settings explicitly
ACAN2515TinySettings settings(500000,      // Bit rate: 500 kbps
                               ACAN2515TinySettings::Normal, // Operating mode: Normal
                               ACAN2515TinySettings::Disabled, // Transmit FIFO Retransmission Attempts: Disabled
                               ACAN2515TinySettings::ThreeAttempts, // Transmit FIFO Retransmission Attempts: Three Attempts
                               ACAN2515TinySettings::Disabled, // Transmit FIFO Acknowledge: Disabled
                               ACAN2515TinySettings::Disabled, // Receive FIFO Overflow: Disabled
                               ACAN2515TinySettings::Disabled  // Receive FIFO: Disabled
                              );
ACAN2515Tiny can(MCP2515_CS, MCP2515_INT, settings);

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
