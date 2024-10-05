#include <Wire.h>
#include <Adafruit_GFX.h>
#include <Adafruit_ILI9341.h>
#include <SD.h>

// Pin definitions
const int BUTTON_A_PIN = 2;
const int BUTTON_B_PIN = 3;
const int BUTTON_C_PIN = 4;
const int LED1_PIN = 5;
const int LED2_PIN = 6;
const int LED3_PIN = 7;
const int SD_CS_PIN = 10;

// Create instances for LCD and SD card
Adafruit_ILI9341 lcd = Adafruit_ILI9341(8, 9);  // Replace with actual pins
File dataFile;

void setup() {
  // Initialize serial communication
  Serial.begin(9600);

  // Initialize LCD
  lcd.begin();
  lcd.setRotation(3);
  lcd.fillScreen(ILI9341_BLACK);
  lcd.setTextColor(ILI9341_WHITE);
  lcd.setTextSize(2);
  lcd.println("Initializing...");

  // Initialize SD card
  pinMode(SD_CS_PIN, OUTPUT);
  if (!SD.begin(SD_CS_PIN)) {
    lcd.println("SD Card failed");
    Serial.println("SD Card failed");
    while (1);  // Stop execution
  }
  
  // Initialize buttons and LEDs
  pinMode(BUTTON_A_PIN, INPUT_PULLUP);
  pinMode(BUTTON_B_PIN, INPUT_PULLUP);
  pinMode(BUTTON_C_PIN, INPUT_PULLUP);
  pinMode(LED1_PIN, OUTPUT);
  pinMode(LED2_PIN, OUTPUT);
  pinMode(LED3_PIN, OUTPUT);

  lcd.println("SD Card ready");

  // Open the file
  dataFile = SD.open("test.txt");
  if (!dataFile) {
    lcd.println("Failed to open file");
    Serial.println("Failed to open file");
    while (1);  // Stop execution
  }
  lcd.println("File opened");
}

void loop() {
  static char buffer[9];  // Buffer for 8 bytes + null terminator
  static int lastButtonState[3] = {HIGH, HIGH, HIGH};

  // Read button states
  int buttonState[3] = {
    digitalRead(BUTTON_A_PIN),
    digitalRead(BUTTON_B_PIN),
    digitalRead(BUTTON_C_PIN)
  };

  for (int i = 0; i < 3; i++) {
    if (buttonState[i] == LOW && lastButtonState[i] == HIGH) {
      // Button pressed
      delay(50);  // Debounce delay
      readFile();
    }
    lastButtonState[i] = buttonState[i];
  }
}

void readFile() {
  // Read 512 bytes from SD card
  byte buffer[512];
  dataFile.read(buffer, 512);

  // Read 8 bytes from the file
  dataFile.read(buffer, 8);
  buffer[8] = '\0';  // Null terminate the string

  // Display and print the result
  lcd.fillScreen(ILI9341_BLACK);
  lcd.setCursor(0, 0);
  lcd.print("Read: ");
  lcd.println(buffer);

  Serial.print("Read: ");
  Serial.println(buffer);

  // Toggle LEDs
  digitalWrite(LED1_PIN, !digitalRead(LED1_PIN));
  digitalWrite(LED2_PIN, !digitalRead(LED2_PIN));
  digitalWrite(LED3_PIN, !digitalRead(LED3_PIN));
}
