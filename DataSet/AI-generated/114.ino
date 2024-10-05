#include <ACAN2515Tiny.h>

const int MCP2515_CS = 10;  // Chip Select pin for MCP2515
const int MCP2515_IRQ = 2;  // Interrupt pin for MCP2515

ACAN2515Tiny can(MCP2515_CS, MCP2515_IRQ);

void setup() {
  Serial.begin(115200);
  while (!Serial) { ; }

  if (!can.begin()) {
    Serial.println("Failed to initialize CAN interface!");
    while (1) { ; }
  }

  can.setLoopbackMode(true);
  can.enableFIFO();

  // Set up receive filters
  CANFilter filter;
  filter.id = 0x123;
  filter.mask = 0x7FF;
  can.setFilter(filter);
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
