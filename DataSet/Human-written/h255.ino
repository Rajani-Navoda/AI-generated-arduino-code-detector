/* --------------------------------------------------------------
	Example sketch to send value to DAC via serial interface. Open
	serial connection, type value between 0 and 4095 and press enter.
	Check newline (NL) terminator in your terminal.
	
	Author: Christoph Jurczyk
 -------------------------------------------------------------- */

#include <AD7390.h>

// Pins
#define DAC_CS 8

// DAC init
AD7390 dac(DAC_CS);

// Variables
String inString = "";


void setup() {
  Serial.begin(115200);
}


void loop() {
  while (Serial.available() > 0) {
    int inChar = Serial.read();
    if (isDigit(inChar)) {
      // convert the incoming byte to a char and add it to the string:
      inString += (char)inChar;
    }
    // if you get a newline, print the string, then the string's value:
    if (inChar == '\n') {
      Serial.print("Set value to: ");
      uint16_t value = inString.toInt();
      Serial.println(value);
      // clear the string for new input:
      inString = "";
      // set dac
      dac.writeValue(value);
    }
  }
}