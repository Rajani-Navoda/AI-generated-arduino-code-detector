#include <aREST.h>
#include <SPI.h>
#include <CC3000.h>

// Replace with your WiFi credentials
const char* ssid = "your_SSID";
const char* password = "your_PASSWORD";

// Define the CC3000 module pins
#define CC3000_SPI_CS   10
#define CC3000_SPI_IRQ   2
#define CC3000_SPI_RST   9

// Create an instance of the aREST class
aREST rest = aREST();

// Create an instance of the CC3000 class
CC3000 cc3000 = CC3000(CC3000_SPI_CS, CC3000_SPI_IRQ, CC3000_SPI_RST);

void setup() {
  // Initialize serial communication
  Serial.begin(115200);

  // Initialize the CC3000 WiFi module
  if (!cc3000.begin()) {
    Serial.println("CC3000 initialization failed!");
    while (1);
  }
  
  // Connect to the WiFi network
  if (!cc3000.connectToAP(ssid, password, 0)) {
    Serial.println("Failed to connect to WiFi network!");
    while (1);
  }
  
  // Print the IP address assigned by the network
  Serial.print("IP Address: ");
  Serial.println(cc3000.getIP());

  // Initialize the aREST library
  rest.function("led", ledControl);  // Add a function to control an LED
}

void loop() {
  // Handle aREST requests
  rest.handle();
}

// Function to control an LED
int ledControl(String command) {
  int ledPin = 13;  // Change this to your LED pin
  pinMode(ledPin, OUTPUT);
  if (command == "on") {
    digitalWrite(ledPin, HIGH);
    return 1;
  } else if (command == "off") {
    digitalWrite(ledPin, LOW);
    return 1;
  }
  return 0;
}
