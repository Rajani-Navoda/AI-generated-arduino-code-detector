/*
  This is a simple example of the aREST Library for the ESP8266 WiFi chip.
  See the README file for more details.
*/

#include <ESP8266WiFi.h>
#include <aREST.h>

// Replace these with your network credentials
const char* ssid = "your_SSID";
const char* password = "your_PASSWORD";

// Create an instance of the aREST class
aREST rest = aREST();

// Define the pin for the onboard LED
const int ledPin = 2;  // Onboard LED on most ESP8266 boards

void setup() {
  // Initialize serial communication
  Serial.begin(115200);
  while (!Serial) ;  // Wait for serial port to initialize

  // Connect to Wi-Fi
  WiFi.begin(ssid, password);
  Serial.print("Connecting to WiFi");
  while (WiFi.status() != WL_CONNECTED) {
    Serial.print(".");
    delay(500);
  }
  Serial.println("Connected!");
  Serial.print("IP address: ");
  Serial.println(WiFi.localIP());

  // Initialize the LED pin
  pinMode(ledPin, OUTPUT);

  // Initialize aREST
  rest.function("led_on", led_on);  // Define the function to turn an LED on
  rest.function("led_off", led_off); // Define the function to turn an LED off
}

void loop() {
  // Handle incoming client requests
  WiFiClient client = server.available();
  if (client) {
    rest.handle(client);
    client.stop(); // Close the connection
  }
}

// Define the functions that can be called remotely
int led_on(String args) {
  digitalWrite(ledPin, HIGH);  // Turn the LED on
  Serial.println("LED turned on");
  return 1; // Return success
}

int led_off(String args) {
  digitalWrite(ledPin, LOW);   // Turn the LED off
  Serial.println("LED turned off");
  return 1; // Return success
}
