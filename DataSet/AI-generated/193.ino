#include <Arduino.h>
#include <AceCommon.h>

void setup() {
    Serial.begin(115200);
    while (!Serial); // Wait for serial connection

    // Output SIZEOF section
    Serial.println("SIZEOF");
    Serial.print("sizeof(AceCommon): ");
    Serial.println(sizeof(AceCommon));
    // Add more sizeof() statements as needed

    // Output BENCHMARKS section
    Serial.println("BENCHMARKS");
    
    // Example of a benchmark function
    benchmarkFunction("exampleFunction");
    
    Serial.println("END");
}

void benchmarkFunction(const char* name) {
    unsigned long startTime = micros();
    
    // Call the function to benchmark
    // exampleFunction();
    
    unsigned long endTime = micros();
    unsigned long duration = endTime - startTime;
    
    // Print min, avg, max values (this is simplified)
    Serial.print(name);
    Serial.print(" ");
    Serial.print(duration); // Replace with actual calculations
    Serial.print(" ..."); // Placeholder for other metrics
}

void loop() {
    // No continuous operation
}
