#include <CoapSimple.h>
#include <WiFi.h>
#include <WiFiClientSecure.h>
#include <ArduinoJson.h>

// Replace with your network credentials
const char* ssid = "YOUR_SSID";
const char* password = "YOUR_PASSWORD";

// CoAP Server details
const char* coapServer = "coap://your-1nce-endpoint";
const int coapPort = 5684; // Default port for CoAPs

// DTLS credentials
const char* dtlsClientCert = "-----BEGIN CERTIFICATE-----\n..."; // Your client certificate
const char* dtlsClientKey = "-----BEGIN PRIVATE KEY-----\n..."; // Your private key
const char* dtlsCaCert = "-----BEGIN CERTIFICATE-----\n..."; // Your CA certificate

WiFiClientSecure wifiClient;
CoapClient coapClient;

void setup() {
  Serial.begin(115200);
  WiFi.begin(ssid, password);
  
  // Wait for WiFi connection
  while (WiFi.status() != WL_CONNECTED) {
    delay(1000);
    Serial.print(".");
  }
  Serial.println("Connected to WiFi");

  // Configure WiFiClientSecure with DTLS credentials
  wifiClient.setCertificate(dtlsClientCert);
  wifiClient.setPrivateKey(dtlsClientKey);
  wifiClient.setCACert(dtlsCaCert);

  // Initialize CoAP client
  coapClient.begin(coapServer, coapPort, wifiClient);
}

void loop() {
  // Send CoAP GET request
  String path = "/sensor/data";
  int ret = coapClient.get(path);
  
  if (ret == 200) {
    Serial.println("CoAP GET request successful");

    // Process response payload
    String payload = coapClient.responsePayload();
    Serial.print("Payload: ");
    Serial.println(payload);

    // Optionally compress payload (Energy Saver feature)
    String compressedPayload = compressPayload(payload);
    Serial.print("Compressed Payload: ");
    Serial.println(compressedPayload);

    // Send compressed payload if needed
    // coapClient.post("/sensor/data", compressedPayload);
  } else {
    Serial.print("CoAP GET request failed with error code: ");
    Serial.println(ret);
  }

  delay(5000); // Wait before sending next request
}

// Function to compress payload (example, replace with actual compression logic)
String compressPayload(String payload) {
  // Dummy compression example (replaces with actual logic)
  return payload.substring(0, min(payload.length(), 10)); // Truncate for demonstration
}
