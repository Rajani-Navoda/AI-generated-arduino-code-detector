/*
  This example demonstrates a simple keepalive mechanism.
  It periodically sends a keepalive signal to a server or logs the status.
*/

#include <SPI.h>
#include <Ethernet.h> // Include if using an Ethernet shield
//#include <WiFi.h>  // Uncomment if using a WiFi module

// Network settings (adjust these for your network)
byte mac[] = { 0xDE, 0xAD, 0xBE, 0xEF, 0xFE, 0xED }; // MAC address
IPAddress server(192, 168, 1, 100); // IP address of the server
EthernetClient client; // Uncomment if using an Ethernet shield

// Uncomment if using a WiFi module
//const char* ssid = "your_SSID";
//const char* password = "your_PASSWORD";
//WiFiClient client;

const int keepaliveInterval = 10000; // Interval in milliseconds (10 seconds)
unsigned long lastKeepaliveTime = 0;

void setup() {
  Serial.begin(9600);

  // Initialize network
  Ethernet.begin(mac);
  delay(1000); // Give the Ethernet shield time to initialize
  Serial.println("Connecting to network...");

  // Uncomment if using a WiFi module
  // WiFi.begin(ssid, password);
  // while (WiFi.status() != WL_CONNECTED) {
  //   delay(1000);
  //   Serial.print(".");
  // }
  // Serial.println("Connected to WiFi");

  // Connect to the server
  if (client.connect(server, 80)) {
    Serial.println("Connected to server");
  } else {
    Serial.println("Connection failed");
  }
}

void loop() {
  unsigned long currentTime = millis();

  if (currentTime - lastKeepaliveTime >= keepaliveInterval) {
    sendKeepalive();
    lastKeepaliveTime = currentTime;
  }

  // Check if the client is connected and handle any incoming data
  if (client.connected()) {
    if (client.available()) {
      String response = client.readStringUntil('\n');
      Serial.println("Server response: " + response);
    }
  } else {
    Serial.println("Disconnected from server");
    // Reconnect if needed
    if (client.connect(server, 80)) {
      Serial.println("Reconnected to server");
    }
  }
}

void sendKeepalive() {
  if (client.connected()) {
    Serial.println("Sending keepalive...");
    client.println("GET /keepalive HTTP/1.1");
    client.println("Host: 192.168.1.100");
    client.println("Connection: keep-alive");
    client.println();
  } else {
    Serial.println("Not connected to server");
  }
}
