#include <SPI.h>
#include <WiFi101.h>
#include <aREST.h>

// Replace with your network credentials
const char* ssid = "your_SSID";
const char* password = "your_PASSWORD";

// Initialize aREST library
aREST rest = aREST();

void setup() {
  // Initialize serial communication
  Serial.begin(9600);

  // Connect to Wi-Fi
  WiFi.begin(ssid, password);
  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
  }
  Serial.println("Connected to Wi-Fi");

  // Initialize the aREST library
  rest.nodeName("ArduinoMK1000");
  rest.function("led", ledControl);  // Bind function to aREST

  // Start a REST server
  rest.begin();
}

void loop() {
  // Update the REST server
  rest.handleClient();
}

int ledControl(String command) {
  if (command == "on") {
    digitalWrite(LED_BUILTIN, HIGH);
    return 1;
  } else if (command == "off") {
    digitalWrite(LED_BUILTIN, LOW);
    return 0;
  }
  return -1;
}
