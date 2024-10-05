#include <ACAN.h>      // For the Teensy 3.x builtin CAN
#include <ACAN2515Tiny.h>  // For the external MCP2515

static const uint32_t CAN_BIT_RATE = 1000 * 1000;

const int MCP2515_CS = 10;  // Chip Select pin for MCP2515
const int MCP2515_IRQ = 2;  // Interrupt pin for MCP2515

ACAN2515Tiny can(MCP2515_CS, MCP2515_IRQ);
ACANSettings settings(CAN_BIT_RATE);

void setup() {
  Serial.begin(115200);
  while (!Serial) { ; }

  if (!can.begin(settings)) {
    Serial.println("Failed to initialize MCP2515 CAN interface!");
    while (1) { ; }
  }

  can.setLoopbackMode(true);
  can.enableFIFO();
}

void loop() {
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

  delay(1000);
}
