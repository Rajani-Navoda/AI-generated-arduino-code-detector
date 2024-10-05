#include <ACAN2517FD.h>

const uint8_t CS_PIN = 10;  // Chip Select pin

ACAN2517FD canBus(CS_PIN);

void setup() {
  Serial.begin(115200);

  if (!canBus.begin()) {
    Serial.println("Failed to initialize CAN bus.");
    while (1);
  }

  canBus.setLoopBack(true);

  Serial.println("CAN Bus Initialized and Loopback Mode Enabled.");
}

void loop() {
  CANMessage message;
  message.id = 0x123;
  message.length = 8;
  for (int i = 0; i < message.length; i++) {
    message.data[i] = i + 1;
  }

  if (!canBus.write(message)) {
    Serial.println("Failed to send CAN message.");
  }

  if (canBus.available()) {
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
  }

  delay(1000);
}
