/*
  Example for using the LAN8720 Ethernet module with ESP32.
  This sketch sets up a basic web server to demonstrate Ethernet connectivity.
*/

#include <ETH.h>

// Ethernet configuration
#define ETH_CLK_MODE ETH_CLOCK_GPIO0_IN  // Clock mode for LAN8720
#define ETH_PHY_ADDR  1                  // PHY address of the LAN8720
#define ETH_PHY_TYPE  ETH_PHY_LAN8720    // LAN8720 PHY type

// Function to handle incoming HTTP requests
void handleClient() {
  WiFiClient client = server.available();
  if (client) {
    String request = client.readStringUntil('\r');
    client.flush();

    // Simple response
    String response = "HTTP/1.1 200 OK\r\nContent-Type: text/html\r\n\r\n";
    response += "<!DOCTYPE HTML><html>";
    response += "<h1>ESP32 Ethernet Test</h1>";
    response += "<p>Ethernet is working!</p>";
    response += "</html>";

    client.print(response);
    delay(1);
    client.stop();
  }
}

void setup() {
  Serial.begin(115200);
  while (!Serial) ;  // Wait for serial port to initialize

  // Initialize Ethernet
  ETH.begin();
  ETH.config(IPAddress(192, 168, 1, 184), IPAddress(255, 255, 255, 0), IPAddress(192, 168, 1, 1));
  ETH.setHostname("ESP32");
  ETH.setPhyAddress(ETH_PHY_ADDR);
  ETH.setPhyType(ETH_PHY_TYPE);
  ETH.setClock(ETH_CLK_MODE);

  Serial.println("Ethernet initialized");
  
  // Start the server
  server.begin();
}

void loop() {
  handleClient();  // Handle incoming client requests
}
