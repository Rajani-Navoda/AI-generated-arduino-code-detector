#include <Wire.h>
#include <Adafruit_LiquidCrystal.h>

// Define LCD pins
#define LCD_RS    7
#define LCD_ENABLE 8
#define LCD_D4    9
#define LCD_D5    10
#define LCD_D6    11
#define LCD_D7    12
#define LCD_BL    13

// Create LCD object
Adafruit_LiquidCrystal lcd(LCD_RS, LCD_ENABLE, LCD_D4, LCD_D5, LCD_D6, LCD_D7);

// Define analog pin for voltage measurement
const int analogPin = A1;

void setup() {
  // Initialize the LCD
  lcd.begin(16, 2);
  lcd.print("A-Star 32U4");

  // Initialize serial communication
  Serial.begin(9600);

  // Check if USB power is present
  if (isUSBPowerPresent()) {
    lcd.setCursor(0, 1);
    lcd.print("USB Power: Yes");
    Serial.println("USB Power: Yes");
  } else {
    lcd.setCursor(0, 1);
    lcd.print("USB Power: No ");
    Serial.println("USB Power: No ");
  }

  // Measure and display the voltage on VIN pin
  float vinVoltage = measureVinVoltage();
  lcd.setCursor(0, 1);
  lcd.print("VIN Voltage: ");
  lcd.print(vinVoltage);
  lcd.print("V");
  Serial.print("VIN Voltage: ");
  Serial.print(vinVoltage);
  Serial.println("V");
}

void loop() {
  // Nothing to do here
}

bool isUSBPowerPresent() {
  // Check if USB power is present by reading an appropriate pin
  // Note: Adjust as per your specific board and configuration
  // Here we assume we can detect USB power by reading an analog pin
  return analogRead(A0) > 512; // Example threshold, adjust as needed
}

float measureVinVoltage() {
  // Read the voltage from analog pin and convert to actual voltage
  int rawValue = analogRead(analogPin);
  // Assuming a reference voltage of 5V and a 10-bit ADC
  float voltage = (rawValue / 1023.0) * 5.0;
  return voltage;
}
