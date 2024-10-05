#include <FlexCAN_T4.h>

// Create CAN objects for CAN1, CAN2, and CAN3
FlexCAN_T4<CAN1, RX_SIZE_256, TX_SIZE_16> Can1;
FlexCAN_T4<CAN2, RX_SIZE_256, TX_SIZE_16> Can2;
FlexCAN_T4<CAN3, RX_SIZE_256, TX_SIZE_16> Can3;

// CAN message objects
CAN_message_t msg;

// Setup function
void setup() {
  Serial.begin(115200);
  while (!Serial) ;  // Wait for serial port to initialize

  // Initialize CAN buses
  Can1.begin();
  Can2.begin();
  Can3.begin();

  // Set CAN bitrate (500 kbps in this example)
  Can1.setBaudRate(500000);
  Can2.setBaudRate(500000);
  Can3.setBaudRate(500000);

  // Set filters (optional)
  Can1.setFilter(0x123, 0x7FF);  // CAN ID filter for CAN1
  Can2.setFilter(0x456, 0x7FF);  // CAN ID filter for CAN2
  Can3.setFilter(0x789, 0x7FF);  // CAN ID filter for CAN3

  // Send test message
  msg.id = 0x123;      // CAN ID
  msg.len = 8;         // Data length
  for (int i = 0; i < msg.len; i++) {
    msg.buf[i] = i;    // Test data
  }
  
  Can1.write(msg);    // Send message on CAN1
  Can2.write(msg);    // Send message on CAN2
  Can3.write(msg);    // Send message on CAN3
  
  Serial.println("CAN messages sent");
}

void loop() {
  // Check if any CAN bus has received a message
  if (Can1.available()) {
    Can1.read(msg);
    Serial.print("CAN1 received message: ID=");
    Serial.print(msg.id, HEX);
    Serial.print(" Data=");
    for (int i = 0; i < msg.len; i++) {
      Serial.print(" ");
      Serial.print(msg.buf[i], HEX);
    }
    Serial.println();
  }

  if (Can2.available()) {
    Can2.read(msg);
    Serial.print("CAN2 received message: ID=");
    Serial.print(msg.id, HEX);
    Serial.print(" Data=");
    for (int i = 0; i < msg.len; i++) {
      Serial.print(" ");
      Serial.print(msg.buf[i], HEX);
    }
    Serial.println();
  }

  if (Can3.available()) {
    Can3.read(msg);
    Serial.print("CAN3 received message: ID=");
    Serial.print(msg.id, HEX);
    Serial.print(" Data=");
    for (int i = 0; i < msg.len; i++) {
      Serial.print(" ");
      Serial.print(msg.buf[i], HEX);
    }
    Serial.println();
  }
}
