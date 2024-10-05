// Define a class named Thermistor
class Thermistor {
  private:
    int pin;          // Analog pin connected to the thermistor
    float beta;       // Beta value for the thermistor
    float resistanceAt25C; // Resistance of the thermistor at 25°C

  public:
    // Constructor to initialize the thermistor
    Thermistor(int p, float b, float r) : pin(p), beta(b), resistanceAt25C(r) {}

    // Function to read and calculate temperature
    float readTemperature() {
      int rawValue = analogRead(pin);
      float resistance = (1023.0 / rawValue - 1.0) * resistanceAt25C;
      float temperature = 1.0 / (log(resistance / resistanceAt25C) / beta + 1.0 / 298.15) - 273.15;
      return temperature;
    }

    // Function to print the temperature to the Serial Monitor
    void printTemperature() {
      float temperature = readTemperature();
      Serial.print("Temperature: ");
      Serial.print(temperature);
      Serial.println(" C");
    }
};

// Create an instance of Thermistor for pin A0
Thermistor myThermistor(A0, 3950, 10000);

void setup() {
  Serial.begin(9600);
  Serial.println("Thermistor readings:");
}

void loop() {
  myThermistor.printTemperature(); // Call the member function to print temperature
  delay(2000);  // Delay between readings
}
