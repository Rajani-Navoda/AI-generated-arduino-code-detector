#include <SPI.h>
#include <mcp2517fd.h>

// Define MCP2517FD chip select and interrupt pins
#define MCP2517FD_CS   4  // SPI Chip Select pin
#define MCP2517FD_INT  5  // Interrupt pin

// Create an instance of the MCP2517FD object
MCP2517FD mcp2517fd;

// Setup function
void setup() {
  Serial.begin(115200);
  while (!Serial) ;  // Wait for serial port to initialize

  // Initialize SPI
  SPI.begin();

  // Initialize MCP2517FD
  mcp2517fd.begin(MCP2517FD_CS, MCP2517FD_INT);

  // Set MCP2517FD to CAN FD mode
  mcp2517fd.setMode(MCP2517FD_MODE_NORMAL);

  // Set CAN FD bitrate
  mcp2517fd.setBitrate(500000, 2000000);  // 500 kbps for CAN 2.0B, 2 Mbps for CAN FD

  Serial.println("MCP2517FD initialized and configured");
}

void loop() {
  // Create a CAN FD message
  CANFDMessage message;
  message.id = 0x123;       // CAN ID
  message.extended = false; // Standard CAN ID
  message.rtr = false;      // Data frame (not remote request frame)
  message.len = 8;          // Data length
  for (int i = 0; i < message.len; i++) {
    message.data[i] = i;    // Test data
  }

  // Send the CAN FD message
  mcp2517fd.sendMessage(message);

  // Wait for 1 second
  delay(1000);

  // Check for received messages
  if (mcp2517fd.available()) {
    CANFDMessage receivedMessage;
    mcp2517fd.readMessage(receivedMessage);

    Serial.print("Received message: ID=");
    Serial.print(receivedMessage.id, HEX);
    Serial.print(" Data=");
    for (int i = 0; i < receivedMessage.len; i++) {
      Serial.print(" ");
      Serial.print(receivedMessage.data[i], HEX);
    }
    Serial.println();
  }
}
