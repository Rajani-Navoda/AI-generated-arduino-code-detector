 #include <AD5254_asukiaaa.h>

AD5254_asukiaaa potentio(AD5254_ASUKIAAA_ADDR_A0_VDD_A1_VDD);

uint8_t targetChannel = 3;
uint8_t targetValue = 200;

void setup() {
  Serial.begin(115200);
  potentio.begin();
}

void loop() {
  uint8_t value;
  String channelStr = String(targetChannel);
  if (potentio.loadEEPROM(targetChannel, &value) == 0) {
    Serial.println("EEPROM of channel " + channelStr + " is " + String(value));
    if (value != targetValue) {
      if (potentio.saveEEPROM(targetChannel, targetValue) == 0) {
        Serial.println("Save EEPROM of channel " + channelStr + " to " + String(targetValue));
        Serial.println("If you cannot update value, make sure that WP pin is connected to VDD.");
      } else {
        Serial.println("Cannot save to EEPROM of channel " + channelStr + ".");
      }
    }
  } else {
    Serial.println("Cannot load EEPROM of channel " + channelStr + ".");
  }

  delay(5000);
}