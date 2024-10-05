/*
  This example demonstrates how to read pressure data from a Honeywell HSC Pressure Sensor
  and print it to the Serial Monitor.
*/

const int pressurePin = A0;  // Analog pin connected to Vout of the HSC sensor

// Constants for sensor calibration (These should be adjusted based on your sensor's datasheet)
const float Vcc = 5.0;          // Supply voltage for the sensor
const float maxPressure = 100.0; // Maximum pressure in PSI (or other units based on your sensor)
const int maxAnalogValue = 1023; // Maximum value for a 10-bit ADC

void setup() {
  Serial.begin(9600);
  // Initialize the analog pin as input (this is the default, so this line is optional)
  pinMode(pressurePin, INPUT);
}

void loop() {
  // Read the analog value from the sensor
  int analogValue = analogRead(pressurePin);

  // Convert the analog value to voltage
  float voltage = (analogValue / float(maxAnalogValue)) * Vcc;

  // Convert voltage to pressure
  float pressure = (voltage / Vcc) * maxPressure;

  // Print the pressure to the Serial Monitor
  Serial.print("Pressure: ");
  Serial.print(pressure);
  Serial.println(" PSI"); // Change unit based on your sensor's specification

  // Wait before the next reading
  delay(1000); // Delay for 1 second
}
