#include <math.h>

// Number of thermistors
const int numThermistors = 4;

// Analog pins connected to thermistors
const int thermistorPins[numThermistors] = {A0, A1, A2, A3};

// Thermistor calibration parameters
const float beta = 3950;   // Beta value for the thermistor (specific to your thermistor)
const float resistanceAt25C = 10000; // Resistance of the thermistor at 25°C (10kΩ is common)

// Read analog pin and convert to temperature
float readTemperature(int pin) {
  int rawValue = analogRead(pin);
  float resistance = (1023.0 / rawValue - 1.0) * resistanceAt25C;
  float temperature = 1.0 / (log(resistance / resistanceAt25C) / beta + 1.0 / 298.15) - 273.15;
  return temperature;
}

void setup() {
  Serial.begin(9600);
  Serial.println("Thermistor readings:");
}

void loop() {
  for (int i = 0; i < numThermistors; i++) {
    float temperature = readTemperature(thermistorPins[i]);
    Serial.print("Thermistor ");
    Serial.print(i);
    Serial.print(": ");
    Serial.print(temperature);
    Serial.println(" C");
  }
  Serial.println();
  delay(2000);  // Delay between readings
}
