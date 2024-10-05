/*
  This example demonstrates basic use of the A-Star 32U4 Prime LCD.
  It prints the word "hi" on the first line of the LCD and prints the number 1234 on the second line.

  Note: This demo uses the standard A-Star 32U4 Prime LCD pins. To avoid damage or improper operation,
  if you have shields or other electronics connected, make sure they do not use those pins in a conflicting way.
*/

#include <Wire.h>          // Include the Wire library for I2C communication
#include <LiquidCrystal_I2C.h> // Include the LCD library for I2C LCDs

// Define the I2C address of the LCD
#define LCD_ADDRESS 0x27 // Adjust this to your LCD's I2C address if necessary

// Create an instance of the LiquidCrystal_I2C class
LiquidCrystal_I2C lcd(LCD_ADDRESS, 16, 2); // 16 columns and 2 rows

void setup() {
  lcd.begin();          // Initialize the LCD
  lcd.backlight();      // Turn on the backlight

  // Print "hi" on the first line
  lcd.setCursor(0, 0);  // Set the cursor to the beginning of the first line
  lcd.print("hi");

  // Print "1234" on the second line
  lcd.setCursor(0, 1);  // Set the cursor to the beginning of the second line
  lcd.print(1234);
}

void loop() {
  // Nothing to do here
}
