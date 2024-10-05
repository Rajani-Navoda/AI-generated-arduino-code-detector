#include <Arduino.h>

// Function to encode a URL
String urlEncode(const String &input) {
    String encoded = "";
    for (char c : input) {
        if (isalnum(c) || c == '-' || c == '_' || c == '.' || c == '~') {
            encoded += c; // Keep alphanumeric and certain characters
        } else {
            encoded += '%'; // Start percent-encoding
            encoded += String(c, HEX); // Convert to hexadecimal
        }
    }
    return encoded;
}

// Benchmark function
void benchmarkUrlEncoding(const String &input) {
    unsigned long startTime = millis();
    
    String result = urlEncode(input);
    
    unsigned long endTime = millis();
    Serial.print("Encoded URL: ");
    Serial.println(result);
    Serial.print("Time taken: ");
    Serial.print(endTime - startTime);
    Serial.println(" ms");
}

void setup() {
    Serial.begin(115200);
    while (!Serial); // Wait for serial connection

    String testString = "Hello World! This is a test for URL encoding.";
    
    // Run the benchmark
    benchmarkUrlEncoding(testString);
}

void loop() {
    // No ongoing operations
}
