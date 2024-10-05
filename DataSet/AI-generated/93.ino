#include <Wire.h>
#include <Adafruit_LiquidCrystal.h>
#include <SPI.h>
#include <SD.h>

// Define LCD pins
#define LCD_RS    7
#define LCD_ENABLE 8
#define LCD_D4    9
#define LCD_D5    10
#define LCD_D6    11
#define LCD_D7    12

// Create LCD object
Adafruit_LiquidCrystal lcd(LCD_RS, LCD_ENABLE, LCD_D4, LCD_D5, LCD_D6, LCD_D7);

// Define buzzer pin
const int buzzerPin = 6;

// Define button pins
const int buttonAPin = 2;
const int buttonBPin = 3;

// Define microSD card pin
const int chipSelect = 4;

// Define menu options
enum MenuOption {
  OPTION_1,
  OPTION_2,
  OPTION_3,
  NUM_OPTIONS
};

MenuOption currentOption = OPTION_1;

void setup() {
  // Initialize LCD
  lcd.begin(16, 2);
  lcd.print("A-Star Demo");

  // Initialize buzzer
  pinMode(buzzerPin, OUTPUT);

  // Initialize buttons
  pinMode(buttonAPin, INPUT_PULLUP);
  pinMode(buttonBPin, INPUT_PULLUP);

  // Initialize microSD card
  if (!SD.begin(chipSelect)) {
    lcd.setCursor(0, 1);
    lcd.print("SD card failed");
    return;
  }

  // Main menu
  showMenu();
}

void loop() {
  // Check for button presses
  if (digitalRead(buttonAPin) == LOW) {
    handleButtonA();
    delay(200); // Debounce delay
  }
  if (digitalRead(buttonBPin) == LOW) {
    handleButtonB();
    delay(200); // Debounce delay
  }
}

void showMenu() {
  lcd.setCursor(0, 0);
  lcd.print("Select option:");
  lcd.setCursor(0, 1);
  lcd.print("1. Option 1");
  lcd.setCursor(0, 1);
  lcd.print("2. Option 2");
}

void handleButtonA() {
  switch (currentOption) {
    case OPTION_1:
      lcd.clear();
      lcd.print("Option 1 selected");
      // Add code for Option 1
      break;
    case OPTION_2:
      lcd.clear();
      lcd.print("Option 2 selected");
      // Add code for Option 2
      break;
    case OPTION_3:
      lcd.clear();
      lcd.print("Option 3 selected");
      // Add code for Option 3
      break;
  }
  // Play a sound
  tone(buzzerPin, 1000, 200);
}

void handleButtonB() {
  currentOption = static_cast<MenuOption>((currentOption + 1) % NUM_OPTIONS);
  showMenu();
}
