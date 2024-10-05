
#include <Wire.h>
#include <YourModuleClasses.h> // Include necessary module headers

// Timing statistics variables
unsigned long minTime = ULONG_MAX;
unsigned long maxTime = 0;
unsigned long totalTime = 0;
unsigned long sampleCount = 0;

void benchmarkModule(ModuleClass& module) {
    unsigned long start = micros();
    module.render(); // Call the render function of the module
    unsigned long duration = micros() - start;

    // Update timing statistics
    if (duration < minTime) minTime = duration;
    if (duration > maxTime) maxTime = duration;
    totalTime += duration;
    sampleCount++;
}

void printStats() {
    if (sampleCount > 0) {
        Serial.print("Min: "); Serial.println(minTime);
        Serial.print("Max: "); Serial.println(maxTime);
        Serial.print("Avg: "); Serial.println(totalTime / sampleCount);
    }
}

void setup() {
    Serial.begin(115200);
    while (!Serial); // Wait for Serial to be ready

    // Initialize modules
    ModuleClass module1;
    module1.begin(); // Setup for your module class

    // Benchmark the module rendering
    for (int i = 0; i < 100; i++) {
        benchmarkModule(module1);
    }

    // Print timing statistics
    printStats();
}

void loop() {
    // Empty loop
}