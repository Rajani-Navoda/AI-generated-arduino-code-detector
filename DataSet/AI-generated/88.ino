// Pin where the thermistor is connected
const int thermistorPin = A0;

// Thermistor constants
const float BETA = 3950; // Beta parameter for the thermistor
const float SERIES_RESISTOR = 10000; // Value of the series resistor in ohms

void setup() {
  Serial.begin(9600);
}

void loop() {
  // Read the analog value from the thermistor
  int rawValue = analogRead(thermistorPin);
  
  // Convert the analog value to resistance
  float resistance = SERIES_RESISTOR / (1023.0 / rawValue - 1.0);
  
  // Calculate temperature in Kelvin
  float temperatureK = 1.0 / (log(resistance / SERIES_RESISTOR) / BETA + 1.0 / 298.15);
  
  // Convert temperature to Celsius
  float temperatureC = temperatureK - 273.15;
  
  // Print the temperature to the Serial Monitor
  Serial.print("Temperature: ");
  Serial.print(temperatureC);
  Serial.println(" C");
  
  // Wait a bit before taking another reading
  delay(1000);
}
