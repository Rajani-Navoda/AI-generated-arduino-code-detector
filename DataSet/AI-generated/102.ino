#include <ACAN2517FD.h>

// Define CAN0 pins
const int CAN0_CS_PIN = 10;  // Chip Select for CAN0
const int CAN0_INT_PIN = 9;  // Interrupt for CAN0

// Define CAN1 pins
const int CAN1_CS_PIN = 8;   // Chip Select for CAN1
const int CAN1_INT_PIN = 7;  // Interrupt for CAN1

// Create CAN instances
ACAN2517FD can0;
ACAN2517FD can1;

// Message to be sent
ACAN2517FDMessage txMessage;
ACAN2517FDMessage rxMessage;

unsigned long frameCount = 0; // To count received frames

void setup() {
  // Initialize Serial communication
  Serial.begin(115200);
  while (!Serial) {
    ; // Wait for serial port to connect
  }
  
  // Initialize CAN0
  CANSettings settings0;
  settings0.mClockSource = ACAN2517FDSettings::ClockSource::External;
  settings0.mInterruptPin = CAN0_INT_PIN;
  settings0.mCS = CAN0_CS_PIN;
  if (!can0.begin(settings0)) {
    Serial.println("Failed to initialize CAN0");
    while (1); // Stop execution
  }
  Serial.println("CAN0 initialized");

  // Initialize CAN1
  CANSettings settings1;
  settings1.mClockSource = ACAN2517FDSettings::ClockSource::External;
  settings1.mInterruptPin = CAN1_INT_PIN;
  settings1.mCS = CAN1_CS_PIN;
  if (!can1.begin(settings1)) {
    Serial.println("Failed to initialize CAN1");
    while (1); // Stop execution
  }
  Serial.println("CAN1 initialized");

  // Set up the message for transmission
  txMessage.mID = 0x123; // CAN ID
  txMessage.mLength = 8; // Data length
  for (int i = 0; i < 8; i++) {
    txMessage.mData[i] = i; // Example data
  }

  // Set up filters for CAN1 to receive the remote frame
  CANFilter filter;
  filter.mID = 0x123; // CAN ID to filter
  filter.mMask = 0x7FF; // Mask to match all bits
  can1.setFilter(filter);
}

void loop() {
  // Send remote frame from CAN0
  can0.tryToSendRemoteFrame(txMessage);
  Serial.println("Sent remote frame");

  // Check if CAN1 has received any message
  if (can1.receive(rxMessage)) {
    Serial.print("Received message with ID: ");
    Serial.println(rxMessage.mID, HEX);
    frameCount++;
  }

  // Display received frame count
  Serial.print("Frames received: ");
  Serial.println(frameCount);

  delay(1000); // Delay to avoid flooding the serial monitor
}
