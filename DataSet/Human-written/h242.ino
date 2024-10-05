#include <AD5254_asukiaaa.h>

AD5254_asukiaaa potentio(AD5254_ASUKIAAA_ADDR_A0_VDD_A1_VDD);

void setup() {
  Serial.begin(115200);
  potentio.begin();
}

void loop() {
  uint8_t value;
  for (uint8_t i = 0; i < 4; ++i) {
    String indexStr = String(i);
    if (potentio.readRDAC(i, &value) == 0) {
      Serial.println("RDAC of channel " + indexStr + " is " + String(value));
    } else {
      Serial.println("Cannot read RDAC of channel " + indexStr + ".");
    }
  }

  // Make sure the WP(write protect) is connected to VDD
  uint8_t targetChannel = 0;
  String channelStr = String(targetChannel);
  uint8_t targetValue = (millis() / 1000) % 256;
  if (potentio.writeRDAC(targetChannel, targetValue) == 0) {
    Serial.println("Update RDAC of channel " + channelStr + " to " + String(targetValue));
  } else {
    Serial.println("Cannot update RDAC of channel " + channelStr + ".");
  }

  delay(1000);
}