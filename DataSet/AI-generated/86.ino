#include <ACAN2517FD.h>

// Define MCP2517FD connections
#define MCP2517FD_SCK_PIN 32
#define MCP2517FD_SDI_PIN 0
#define MCP2517FD_SDO_PIN 1
#define MCP2517FD_CS_PIN  10
#define MCP2517FD_INT_PIN 9

// Create a settings object for the MCP2517FD
ACAN2517FDSettings settings(MCP2517FD_CS_PIN, MCP2517FD_INT_PIN);

// Create a driver object for the MCP2517FD
ACAN2517FD can1;

void setup() {
  // Initialize serial communication
  Serial.begin(115200);

  // Initialize the CAN controller
  if (!can1.begin(settings)) {
    Serial.println("CAN initialization failed!");
    while (1);
  }

  // Set the number of transmission attempts to 3
  settings.mControllerTransmitFIFORetransmissionAttempts = ACAN2517Settings::ThreeAttempts;

  // Start the CAN controller
  can1.begin(settings);

  Serial.println("CAN initialized successfully with ThreeAttempts setting.");
}

void loop() {
  // Create a CAN message
  CANMessage txMessage;
  txMessage.id = 0x123;
  txMessage.length = 8;
  for (int i = 0; i < 8; i++) {
    txMessage.data[i] = i;
  }

  // Send the CAN message
  if (can1.tryWrite(txMessage)) {
    Serial.println("Message sent successfully.");
  } else {
    Serial.println("Message failed to send.");
  }

  // Wait for a while
  delay(1000);
}
