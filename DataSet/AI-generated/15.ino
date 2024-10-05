#if defined(ESP8266)
#include <ESP8266WiFi.h>
#else
#include <WiFi.h>
#endif

#include <DNSServer.h>
#include <aWOT.h>

// Set these to your network credentials
const char* ssid = "CaptivePortal";
const char* password = "password";

// Captive portal DNS server and web server
DNSServer dnsServer;
WiFiServer server(80);

void setup() {
  // Initialize serial communication
  Serial.begin(115200);

  // Initialize the WiFi in Access Point mode
  WiFi.softAP(ssid, password);

  // Print the IP address
  Serial.println("AP IP address: ");
  Serial.println(WiFi.softAPIP());

  // Set up DNS server to handle all requests and redirect them to the captive portal
  dnsServer.start(53, "*", WiFi.softAPIP());

  // Start the web server
  server.begin();
  Serial.println("Web server started.");
}

void loop() {
  // Handle DNS requests
  dnsServer.processNextRequest();

  // Handle client requests
  WiFiClient client = server.available();
  if (client) {
    Serial.println("New client connected.");

    // Read the request
    String request = "";
    while (client.connected() || client.available()) {
      if (client.available()) {
        char c = client.read();
        request += c;
        // Break if the request is complete
        if (c == '\n' && request.endsWith("\r\n\r\n")) {
          break;
        }
      }
    }

    // Respond with a basic HTML page
    String response = "HTTP/1.1 200 OK\r\n";
    response += "Content-Type: text/html\r\n";
    response += "Connection: close\r\n\r\n";
    response += "<!DOCTYPE HTML>\r\n";
    response += "<html>\r\n";
    response += "<h1>Welcome to the Captive Portal!</h1>\r\n";
    response += "<p>This is a simple captive portal example.</p>\r\n";
    response += "</html>\r\n";

    client.print(response);
    client.stop();
    Serial.println("Client disconnected.");
  }
}
