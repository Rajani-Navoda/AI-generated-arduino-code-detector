/*
  This is a simple example of the aREST Library for Arduino (Uno/Mega/Due/Teensy)
  using the Ethernet library. This example illustrates how to make the board accessible from anywhere
  via the aREST cloud service.
*/

#include <SPI.h>
#include <Ethernet.h>
#include <aREST.h>

// MAC address and IP address (use your own settings)
byte mac[] = { 0xDE, 0xAD, 0xBE, 0xEF, 0xFE, 0xED };
IPAddress ip(192, 168, 1, 177);  // Static IP address

// Initialize the Ethernet client
EthernetServer server(80);

// Create an instance of the aREST class
aREST rest = aREST();

// Define the pin for an LED
const int ledPin = 13;  // Built-in LED on most Arduino boards

void setup() {
  // Start serial communication
  Serial.begin(9600);

  // Initialize Ethernet
  Ethernet.begin(mac, ip);
  server.begin();
  Serial.print("Server is at ");
  Serial.println(Ethernet.localIP());

  // Initialize the LED pin
  pinMode(ledPin, OUTPUT);

  // Initialize aREST
  rest.function("led_on", led_on);  // Register function to turn the LED on
  rest.function("led_off", led_off); // Register function to turn the LED off
}

void loop() {
  // Handle incoming client requests
  EthernetClient client = server.available();
  if (client) {
    rest.handle(client);
    client.stop(); // Close the connection
  }
}

// Define functions that can be called remotely
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
