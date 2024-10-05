#include <DHT.h>

// Define the DHT sensor type and the pin it is connected to
#define DHTPIN A0        // A0 pin for the DHT11 sensor on the DFRobot Accessory Shield
#define DHTTYPE DHT11    // DHT11 sensor

// Initialize the DHT sensor
DHT dht(DHTPIN, DHTTYPE);

void setup() {
  Serial.begin(9600);  // Start the serial communication
  dht.begin();         // Initialize the DHT sensor
  Serial.println("Environmental Monitor: Temperature and Humidity");
}

void loop() {
  // Wait a few seconds between measurements
  delay(2000);

  // Read humidity and temperature
  float humidity = dht.readHumidity();
  float temperature = dht.readTemperature();  // Celsius by default

  // Check if any reads failed and exit early (to try again)
  if (isnan(humidity) || isnan(temperature)) {
    Serial.println("Failed to read from DHT sensor!");
    return;
  }

  // Print the results to the Serial Monitor
  Serial.print("Humidity: ");
  Serial.print(humidity);
  Serial.print(" %\t");
  Serial.print("Temperature: ");
  Serial.print(temperature);
  Serial.println(" °C");

  // If you want the temperature in Fahrenheit, you can add this:
  float temperatureF = dht.readTemperature(true);
  Serial.print("Temperature: ");
  Serial.print(temperatureF);
  Serial.println(" °F");
}
