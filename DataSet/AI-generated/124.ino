#include <WiFi.h>       // Include the WiFi library (or another library for your network)
#include <WiFiUdp.h>    // Include the UDP library
#include <zlib.h>       // Include zlib for data compression

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
  
  // Compress the message
  String compressedMessage = compressData(message);

  // Send compressed data
  udp.beginPacket(udpServer, udpPort);
  udp.write((const uint8_t*)compressedMessage.c_str(), compressedMessage.length());
  udp.endPacket();

  // Print sent message
  Serial.println("Sent compressed message");

  // Wait for a bit
  delay(10000); // Send data every 10 seconds
}

String compressData(const String& data) {
  // Create a buffer for the compressed data
  uLongf compressedSize = compressBound(data.length());
  byte* compressedData = new byte[compressedSize];

  // Compress data
  if (compress(compressedData, &compressedSize, (const byte*)data.c_str(), data.length()) != Z_OK) {
    Serial.println("Compression failed");
    delete[] compressedData;
    return "";
  }

  // Convert compressed data to a String
  String compressedString((char*)compressedData, compressedSize);
  delete[] compressedData;
  
  return compressedString;
}
