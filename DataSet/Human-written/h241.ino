 #include <AD5254_asukiaaa.h>

AD5254_asukiaaa potentio(AD5254_ASUKIAAA_ADDR_A0_VDD_A1_VDD);

void setup() {
  Serial.begin(115200);
  potentio.begin();
}

void loop() {
  uint8_t value;
  for (uint8_t targetChannel = 0; targetChannel < 4; ++targetChannel) {
    String channelStr = String(targetChannel);
    if (potentio.readRDAC(targetChannel, &value) == 0) {
      Serial.println("RDAC of channel " + channelStr + " is " + String(value));
    } else {
      Serial.println("Cannot read RDAC of channel " + channelStr + ".");
    }
  }

  for (uint8_t targetChannel = 0; targetChannel < 4; ++targetChannel) {
    String channelStr = String(targetChannel);
    if (potentio.loadEEPROM(targetChannel, &value) == 0) {
      Serial.println("EEPROM of channel " + channelStr + " is " + String(value));
    } else {
      Serial.println("Cannot load of channel " + channelStr + ".");
    }
  }

  Serial.println("at " + String(millis()));

  delay(5000);
}