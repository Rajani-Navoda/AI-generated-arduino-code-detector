#include <Wire.h>
#include <Adafruit_SSD1306.h>
#include <DHT.h>

// Define DHT11 sensor pin and type
#define DHTPIN A0        // DHT11 data pin connected to A0
#define DHTTYPE DHT11    // DHT11 type

// Create a DHT object
DHT dht(DHTPIN, DHTTYPE);

// Define OLED display settings
#define SCREEN_WIDTH 128  // OLED display width, in pixels
#define SCREEN_HEIGHT 64   // OLED display height, in pixels
#define OLED_RESET -1      // Reset pin (not used)

// Create an OLED display object
Adafruit_SSD1306 display(SCREEN_WIDTH, SCREEN_HEIGHT, &Wire, OLED_RESET);

void setup() {
  // Start serial communication for debugging
  Serial.begin(9600);

  // Initialize the DHT11 sensor
  dht.begin();

  // Initialize the OLED display
  display.begin(SSD1306_I2C_ADDRESS, OLED_RESET);
  display.clearDisplay();
  display.setTextSize(1);
  display.setTextColor(SSD1306_WHITE);
  display.setCursor(0, 0);
  display.println("Temp & Humidity");
  display.display(); // Show the title
  delay(2000); // Wait for 2 seconds
}

void loop() {
  // Read temperature and humidity values
  float humidity = dht.readHumidity();
  float temperature = dht.readTemperature();

  // Check if readings failed
  if (isnan(humidity) || isnan(temperature)) {
    Serial.println("Failed to read from DHT sensor!");
    return;
  }

  // Clear the display
  display.clearDisplay();

  // Display the temperature and humidity
  display.setCursor(0, 0);
  display.print("Humidity: ");
  display.print(humidity);
  display.println(" %");

  display.print("Temp: ");
  display.print(temperature);
  display.println(" *C");

  // Update the display
  display.display();

  // Print to Serial Monitor for debugging
  Serial.print("Humidity: ");
  Serial.print(humidity);
  Serial.print("%\tTemperature: ");
  Serial.print(temperature);
  Serial.println("°C");

  // Wait for a bit before the next reading
  delay(2000); // Read every 2 seconds
}
