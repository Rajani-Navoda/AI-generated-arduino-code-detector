#include <ACAN2517.h>

const uint8_t CS_PIN = 10;    // Chip Select pin
const uint8_t INT_PIN = 2;    // Interrupt pin

ACAN2517 canBus(CS_PIN);

volatile bool messageAvailable = false;

void setup() {
  Serial.begin(115200);

  pinMode(INT_PIN, INPUT_PULLUP);
  attachInterrupt(digitalPinToInterrupt(INT_PIN), onCanInterrupt, FALLING);

  SPI.begin(); // Initialize SPI with default pins for SPI1
  if (!canBus.begin()) {
    Serial.println("Failed to initialize CAN bus.");
    while (1);
  }

  // Set up receive filter
  CANFilter filter;
  filter.id = 0x123;
  filter.mask = 0x7FF;  // Standard 11-bit filter mask
  canBus.setFilter(0, filter);

  canBus.setLoopBack(true);

  Serial.println("CAN Bus Initialized, Loopback Mode Enabled, and Filters Set.");
}

void loop() {
  if (messageAvailable) {
    CANMessage message;
    if (canBus.read(message)) {
      Serial.print("Received CAN message ID: 0x");
      Serial.print(message.id, HEX);
      Serial.print(", Data: ");
      for (int i = 0; i < message.length; i++) {
        Serial.print(message.data[i], HEX);
        Serial.print(" ");
      }
      Serial.println();
    }
    messageAvailable = false;
  }

  CANMessage message;
  message.id = 0x123;
  message.length = 8;
  for (int i = 0; i < message.length; i++) {
    message.data[i] = i + 1;
  }

  if (!canBus.write(message)) {
    Serial.println("Failed to send CAN message.");
  }

  delay(1000);
}

void onCanInterrupt() {
  messageAvailable = true;
}
