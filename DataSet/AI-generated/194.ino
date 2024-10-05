#include <Arduino.h>
#include <AceCommon.h>

void setup() {
    Serial.begin(115200);
    while (!Serial); // Wait for serial connection

    Serial.println("SIZEOF");
    
    // Example: Measure the sizes of various components
    Serial.print("sizeof(AceCommon): ");
    Serial.println(sizeof(AceCommon));

    Serial.print("sizeof(TimingStats): ");
    Serial.println(sizeof(TimingStats));

    Serial.print("sizeof(Button): ");
    Serial.println(sizeof(Button));

    // Add more components as needed
    Serial.print("sizeof(OtherComponent): ");
    Serial.println(sizeof(OtherComponent)); // Replace with actual class names

    Serial.println("END");
}

void loop() {
    // No ongoing operations
}
