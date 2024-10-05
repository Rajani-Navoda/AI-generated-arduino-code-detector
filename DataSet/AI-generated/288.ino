#include <Wire.h>
#include <Adafruit_Sensor.h>
#include <Adafruit_AHTX0.h>
#include <Adafruit_GFX.h>
#include <Adafruit_SSD1306.h>

// OLED display dimensions
#define SCREEN_WIDTH 128
#define SCREEN_HEIGHT 64

// Create instances for the AHT sensor and OLED display
Adafruit_AHTX0 aht;
Adafruit_SSD1306 display(SCREEN_WIDTH, SCREEN_HEIGHT, &Wire, -1);

void setup() {
  Serial.begin(115200);
  Serial.println("AHT20 OLED Demo");

  // Initialize the AHT sensor
  if (!aht.begin()) {
    Serial.println("Could not find AHT! Check wiring.");
    while (1);
  }
  Serial.println("AHT sensor initialized.");

  // Initialize the OLED display
  display.begin(SSD1306_I2C_ADDRESS, 0x3C);  // Change address if necessary
  display.clearDisplay();
  display.setTextSize(1);
  display.setTextColor(SSD1306_WHITE);
}

void loop() {
  // Read temperature and humidity
  sensors_event_t humidity, temperature;
  aht.getEvent(&humidity, &temperature);  // Populate humidity and temperature events

  // Clear the display
  display.clearDisplay();

  // Display temperature and humidity on OLED
  display.setCursor(0, 0);
  display.print("Temperature: ");
  display.print(temperature.temperature);
  display.println(" °C");
  
  display.print("Humidity: ");
  display.print(humidity.relative_humidity);
  display.println(" %");

  // Update the display
  display.display();

  // Print to Serial Monitor
  Serial.print("Temperature: ");
  Serial.print(temperature.temperature);
  Serial.println(" °C");
  
  Serial.print("Humidity: ");
  Serial.print(humidity.relative_humidity);
  Serial.println(" %");

  delay(2000); // Wait for 2 seconds before the next reading
}
