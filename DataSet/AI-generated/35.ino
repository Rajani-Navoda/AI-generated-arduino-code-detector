/*
  This example demonstrates how to set up an Arduino as a file server
  using the Ethernet shield. The server will serve a basic HTML file
  when accessed via a web browser.
*/

#include <SPI.h>
#include <Ethernet.h>

// MAC address and IP address (adjust as necessary)
byte mac[] = { 0xDE, 0xAD, 0xBE, 0xEF, 0xFE, 0xED };
IPAddress ip(192, 168, 1, 177);  // Change this to match your network setup

// Initialize the Ethernet server
EthernetServer server(80);

// HTML content to be served
const char* htmlContent = "HTTP/1.1 200 OK\r\n"
                          "Content-Type: text/html\r\n"
                          "Connection: close\r\n\r\n"
                          "<!DOCTYPE HTML>\r\n"
                          "<html>\r\n"
                          "<head><title>Arduino File Server</title></head>\r\n"
                          "<body>\r\n"
                          "<h1>Welcome to the Arduino File Server!</h1>\r\n"
                          "<p>This is a simple example of a file server using the Arduino and Ethernet shield.</p>\r\n"
                          "</body>\r\n"
                          "</html>\r\n";

void setup() {
  // Start serial communication
  Serial.begin(9600);

  // Initialize Ethernet
  Ethernet.begin(mac, ip);
  server.begin();
  Serial.print("Server is at ");
  Serial.println(Ethernet.localIP());
}

void loop() {
  // Listen for incoming clients
  EthernetClient client = server.available();
  if (client) {
    // Wait for the client to send data
    while (client.connected() && !client.available()) {
      delay(1);
    }

    // Send the HTML content to the client
    client.print(htmlContent);

    // Close the connection
    client.stop();
  }
}
