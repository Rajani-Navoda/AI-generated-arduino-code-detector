//——————————————————————————————————————————————————————————————————————————————
//  ACAN2515Tiny Tiny Demo in loopback mode
//——————————————————————————————————————————————————————————————————————————————

#include <ACAN2515Tiny.h>

//——————————————————————————————————————————————————————————————————————————————
//  MCP2515 connections:
//    - standard SPI pins for SCK, MOSI and MISO
//    - a digital output for CS
//    - interrupt input pin for INT
//——————————————————————————————————————————————————————————————————————————————
// If you use CAN-BUS shield (http://wiki.seeedstudio.com/CAN-BUS_Shield_V2.0/) with Arduino Uno,
// use B connections for MISO, MOSI, SCK, #9 or #10 for CS (as you want),
// #2 or #3 for INT (as you want).
//——————————————————————————————————————————————————————————————————————————————

const int MCP2515_CS = 10;   // Chip Select pin
const int MCP2515_INT = 2;   // Interrupt pin

// Create an instance of the ACAN2515Tiny class
ACAN2515Tiny can(MCP2515_CS, MCP2515_INT);

void setup() {
  // Start serial communication
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
