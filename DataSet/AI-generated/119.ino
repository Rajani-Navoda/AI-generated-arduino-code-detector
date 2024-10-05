#include <aREST.h>
#include <WiFi.h>

// Replace with your WiFi credentials
const char* ssid = "your_SSID";
const char* password = "your_PASSWORD";

// Create an instance of the aREST class
aREST rest = aREST();

// Create an instance of the WiFi class
WiFiServer server(80);

void setup() {
  // Initialize serial communication
  Serial.begin(115200);

  // Connect to WiFi network
  WiFi.begin(ssid, password);

  // Wait for connection
  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
  }
  Serial.println("Connected to WiFi!");

  // Print the IP address assigned by the network
  Serial.print("IP Address: ");
  Serial.println(WiFi.localIP());

  // Start the server
  server.begin();

  // Initialize the aREST library
  rest.function("led", ledControl);  // Add a function to control an LED
}

void loop() {
  // Handle aREST requests
  rest.handle();

  // Check for incoming clients
  WiFiClient client = server.available();
  if (client) {
    // Read the request and process it
    rest.handleClient(client);
  }
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
