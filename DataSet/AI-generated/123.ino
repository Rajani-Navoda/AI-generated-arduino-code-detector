#include <WiFi.h>        // Include the WiFi library (or another library for your network)
#include <WiFiUdp.h>     // Include the UDP library

const char* ssid = "YOUR_SSID";        // Replace with your Wi-Fi SSID
const char* password = "YOUR_PASSWORD"; // Replace with your Wi-Fi password

// 1NCE UDP server settings
const char* udpServer = "your-1nce-endpoint"; // Replace with the actual 1NCE server address
const int udpPort = 12345; // Replace with the port number provided by 1NCE

WiFiUDP udp; // Create a UDP instance

void setup() {
  Serial.begin(115200);

  // Connect to Wi-Fi
  WiFi.begin(ssid, password);
  while (WiFi.status() != WL_CONNECTED) {
    delay(1000);
    Serial.print(".");
  }
  Serial.println("Connected to Wi-Fi");

  // Start UDP
  udp.begin(udpPort);
}

void loop() {
  // Example data to send
  String message = "Hello, 1NCE!";
  
  // Send data
  udp.beginPacket(udpServer, udpPort);
  udp.print(message);
  udp.endPacket();

  // Print sent message
  Serial.println("Sent message: " + message);

  // Wait for a bit
  delay(10000); // Send data every 10 seconds
}
