#include <Wire.h>
#include <Adafruit_Sensor.h>
#include <Adafruit_AHTX0.h>

// Create an instance of the AHT sensor
Adafruit_AHTX0 aht;

void setup() {
  Serial.begin(115200);
  Serial.println("AHT20 Test");

  // Initialize the AHT sensor
  if (!aht.begin()) {
    Serial.println("Could not find AHT! Check wiring.");
    while (1);
  }
  Serial.println("AHT sensor initialized.");
}

void loop() {
  // Read temperature and humidity
  sensors_event_t humidity, temperature;
  aht.getEvent(&humidity, &temperature);  // Populate humidity and temperature events

  // Print the results to the Serial Monitor
  Serial.print("Temperature: ");
  Serial.print(temperature.temperature);
  Serial.println(" °C");
  
  Serial.print("Humidity: ");
  Serial.print(humidity.relative_humidity);
  Serial.println(" %");

  delay(2000); // Wait for 2 seconds before the next reading
}
