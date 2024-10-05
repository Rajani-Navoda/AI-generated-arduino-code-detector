#if defined(ESP8266)
#include <ESP8266WiFi.h>
#else
#include <WiFi.h>
#endif

#include <ESPAsyncWebServer.h>  // For ESP8266 and ESP32, use the AsyncWebServer library

// Replace with your network credentials
const char* ssid = "YourSSID";
const char* password = "YourPassword";

// Create an instance of the web server
AsyncWebServer server(80);

void setup() {
  // Initialize serial communication
  Serial.begin(115200);

  // Connect to Wi-Fi
  WiFi.begin(ssid, password);
  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
  }
  Serial.println("\nConnected to Wi-Fi");

  // Serve the root page
  server.on("/", HTTP_GET, [](AsyncWebServerRequest *request){
    request->send(200, "text/html", "<h1>Welcome to the Custom Server!</h1>");
  });

  // Handle 404 Not Found
  server.onNotFound([](AsyncWebServerRequest *request){
    request->send(404, "text/html", "<h1>404 Not Found</h1><p>The requested resource was not found on this server.</p>");
  });

  // Start the server
  server.begin();
}

void loop() {
  // No need to put any code here for this example
}
