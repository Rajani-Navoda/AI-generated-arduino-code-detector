#include <Arduino.h>

const int numPins = 8; // Number of encoder pins
int pinOrder[numPins] = {0, 1, 2, 3, 4, 5, 6, 7}; // Edit this array to match your pin order
String pinString[numPins] = {"PIN0", "PIN1", "PIN2", "PIN3", "PIN4", "PIN5", "PIN6", "PIN7"}; // Edit this to match the pin names

void setup() {
  Serial.begin(9600);
  
  // Print the mapping header
  Serial.println("// ACE128 Encoder Pin Mapping");
  Serial.println("const int encoderPinMap[] = {");

  // Generate the mapping table
  for (int i = 0; i < numPins; i++) {
    Serial.print("  ");
    Serial.print(pinOrder[i]);
    if (i < numPins - 1) {
      Serial.println(",");
    } else {
      Serial.println();
    }
  }
  
  Serial.println("};");
  
  // Print the pin names
  Serial.println("// Pin Names");
  Serial.println("const String encoderPinNames[] = {");
  for (int i = 0; i < numPins; i++) {
    Serial.print("  \"");
    Serial.print(pinString[i]);
    Serial.print("\"");
    if (i < numPins - 1) {
      Serial.println(",");
    } else {
      Serial.println();
    }
  }
  Serial.println("};");
}

void loop() {
  // Nothing to do here
}
