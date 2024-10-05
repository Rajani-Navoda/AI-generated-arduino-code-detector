#include <ACAN2517FD.h>

// Define MCP2517FD connections
const int MCP2517FD_CS_PIN = 10;  // Change to the actual CS pin
const int MCP2517FD_INT_PIN = 9;  // Change to the actual INT pin

// Create an instance of the CAN driver
ACAN2517FD can;

void setup() {
  // Initialize serial communication
  Serial.begin(115200);
  while (!Serial) {
    ; // Wait for serial port to connect
  }
  
  // Initialize CAN with SPI1
  CANSettings settings;
  settings.mClockSource = ACAN2517FDSettings::ClockSource::External;
  settings.mControllerTransmitFIFORetransmissionAttempts = ACAN2517FDSettings::ThreeAttempts; // Use ThreeAttempts setting
  settings.mInterruptPin = MCP2517FD_INT_PIN;
  settings.mCS = MCP2517FD_CS_PIN;
  
  // Initialize CAN bus
  if (!can.begin (settings)) {
    Serial.println("Failed to initialize CAN bus");
    while (1); // Stop execution
  }
  Serial.println("CAN bus initialized");
  
  // Set up a message to send
  ACAN2517FDMessage message;
  message.mID = 0x123;  // CAN ID
  message.mLength = 8; // Data length
  message.mData[0] = 0x11;
  message.mData[1] = 0x22;
  message.mData[2] = 0x33;
  message.mData[3] = 0x44;
  message.mData[4] = 0x55;
  message.mData[5] = 0x66;
  message.mData[6] = 0x77;
  message.mData[7] = 0x88;
  
  // Send the message
  if (!can.tryToSend (message)) {
    Serial.println("Failed to send CAN message");
  } else {
    Serial.println("CAN message sent");
  }
}

void loop() {
  // Loop code here
}
