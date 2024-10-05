#include <SPI.h>
#include <LoRa.h>

const int SS_PIN = 10;    // Pin for LoRa module's SS
const int RST_PIN = 9;    // Pin for LoRa module's RST
const int DIO0_PIN = 2;   // Pin for LoRa module's DIO0

void setup() {
  Serial.begin(9600);
  while (!Serial);

  Serial.println("LoRa Receiver");

  // Setup LoRa module
  LoRa.setPins(SS_PIN, RST_PIN, DIO0_PIN);
  if (!LoRa.begin(915E6)) {  // Set frequency to 915 MHz (change if needed)
    Serial.println("Starting LoRa failed!");
    while (1);
  }

  Serial.println("LoRa Initializing OK!");
}

void loop() {
  // Try to parse a packet
  int packetSize = LoRa.parsePacket();
  if (packetSize) {
    // Read the packet
    String receivedMessage = "";
    while (LoRa.available()) {
      receivedMessage += (char)LoRa.read();
    }

    // Print the received message
    Serial.print("Received: ");
    Serial.println(receivedMessage);
  }

  delay(1000);
}
