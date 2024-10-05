#include <Wire.h>
#include <LiquidCrystal_I2C.h>

// Initialize the LCD
LiquidCrystal_I2C lcd(0x3F, 16, 2);

// LED pins
const int LED_USB_POWER = 8;
const int LED_USB_CONFIGURED = 9;
const int LED_USB_CONNECTED = 10;

void setup() {
  // Initialize serial communication
  Serial.begin(9600);

  // Initialize LCD
  lcd.begin();
  lcd.backlight();
  lcd.setCursor(0, 0);
  lcd.print("USB Status:");

  // Initialize LED pins
  pinMode(LED_USB_POWER, OUTPUT);
  pinMode(LED_USB_CONFIGURED, OUTPUT);
  pinMode(LED_USB_CONNECTED, OUTPUT);

  // Display initial status
  updateUSBStatus();
}

void loop() {
  updateUSBStatus();
  delay(1000);  // Check status every second
}

void updateUSBStatus() {
  // Detect USB power
  if (USBPowerStatus() == 1) {
    digitalWrite(LED_USB_POWER, HIGH);
  } else {
    digitalWrite(LED_USB_POWER, LOW);
  }

  // Detect USB configuration
  if (USBConfiguredStatus() == 1) {
    digitalWrite(LED_USB_CONFIGURED, HIGH);
  } else {
    digitalWrite(LED_USB_CONFIGURED, LOW);
  }

  // Detect USB connection to virtual serial port
  if (Serial.available() > 0) {
    digitalWrite(LED_USB_CONNECTED, HIGH);
  } else {
    digitalWrite(LED_USB_CONNECTED, LOW);
  }

  // Display status on LCD
  lcd.setCursor(0, 1);
  lcd.print("P:");
  lcd.print(digitalRead(LED_USB_POWER));
  lcd.print(" C:");
  lcd.print(digitalRead(LED_USB_CONFIGURED));
  lcd.print(" S:");
  lcd.print(digitalRead(LED_USB_CONNECTED));
}

// Placeholder functions for USB status detection
int USBPowerStatus() {
  // Replace with actual USB power detection logic
  return 1;
}

int USBConfiguredStatus() {
  // Replace with actual USB configuration detection logic
  return 1;
}
