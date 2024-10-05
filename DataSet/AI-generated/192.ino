#include <Arduino.h>
#include <AceCommon.h>

using namespace ace_common;

// Create an instance of TimingStats to collect timing data
TimingStats stats;

// Function to collect sample data
void collectData() {
    stats.update(15);  // Simulated timing measurement
    stats.update(25);
    stats.update(35);
}

// Function to print collected statistics
void printStats() {
    Serial.print("Min: ");
    Serial.println(stats.getMin());

    Serial.print("Max: ");
    Serial.println(stats.getMax());

    Serial.print("Avg: ");
    Serial.println(stats.getAvg());

    Serial.print("Exp Decay Avg: ");
    Serial.println(stats.getExpDecayAvg());

    Serial.print("Count: ");
    Serial.println(stats.getCount());
}

void setup() {
    Serial.begin(115200);
    while (!Serial); // Wait for serial connection (especially for Leonardo/ProMicro)

    // Collect and print timing data
    collectData();
    printStats();
}

void loop() {
    // No ongoing operations in loop
}
