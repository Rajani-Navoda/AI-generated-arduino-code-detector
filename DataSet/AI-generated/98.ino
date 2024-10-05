#include <ESP8266WiFi.h>
#include <WiFiClient.h>
#include <ESP8266WebServer.h>

// Replace with your network credentials
const char* ssid = "your_SSID";
const char* password = "your_PASSWORD";

// Create an instance of the web server
ESP8266WebServer server(80);

// RequestContext class definition
class RequestContext {
public:
  String url;
  String method;
  String headers;
  String body;
};

// Handle root endpoint
void handleRoot() {
  RequestContext requestContext;
  
  requestContext.url = server.uri();
  requestContext.method = server.method() == HTTP_GET ? "GET" : "POST";
  requestContext.headers = "Content-Type: application/json"; // Example header
  requestContext.body = server.arg("plain"); // Read the body of the request if POST

  // Log request details
  Serial.println("Request URL: " + requestContext.url);
  Serial.println("Request Method: " + requestContext.method);
  Serial.println("Request Headers: " + requestContext.headers);
  Serial.println("Request Body: " + requestContext.body);

  // Respond to the client
  server.send(200, "text/plain", "Request received and logged.");
}

void setup() {
  // Start the serial communication
  Serial.begin(115200);
  
  // Connect to Wi-Fi
  WiFi.begin(ssid, password);
  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
  }
  Serial.println("Connected to Wi-Fi!");

  // Define server routes
  server.on("/", HTTP_GET, handleRoot);
  server.on("/", HTTP_POST, handleRoot);

  // Start the server
  server.begin();
  Serial.println("Server started.");
}

void loop() {
  // Handle client requests
  server.handleClient();
}
