#include <aREST.h>
#include <Bridge.h>
#include <YunServer.h>
#include <YunClient.h>

// Create an instance of the aREST class
aREST rest = aREST();

// Create an instance of the YunServer class
YunServer server(80);

void setup() {
  // Initialize serial communication
  Serial.begin(9600);
  while (!Serial);

  // Initialize the Bridge
  Bridge.begin();

  // Start the server
  server.begin();

  // Initialize the aREST library
  rest.function("led", ledControl);  // Add a function to control an LED
}

void loop() {
  // Handle aREST requests
  rest.handle();

  // Check for incoming clients
  YunClient client = server.accept();
  if (client) {
    // Read the request and process it
    rest.handleClient(client);
    client.stop();
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
