/*
 Test Arduino MAX485 Aurora ABB connection
 by Mischianti Renzo <http://www.mischianti.org>

 https://www.mischianti.org/2020/08/20/abb-aurora-pv-inverter-library-for-arduino-esp8266-and-esp32/
*/

// Include the SoftwareSerial library to use a different serial port
#include <SoftwareSerial.h>

// Define the pins for MAX485
#define MAX485_RE_NEG 2
#define MAX485_DE 3

// Create a software serial port on pins 10 and 11
SoftwareSerial mySerial(10, 11); // RX, TX

void setup() {
  // Start serial communication with the PC
  Serial.begin(9600);
  while (!Serial) { ; } // Wait for serial port to connect

  // Start software serial communication with MAX485
  mySerial.begin(9600);

  // Initialize MAX485 control pins
  pinMode(MAX485_RE_NEG, OUTPUT);
  pinMode(MAX485_DE, OUTPUT);

  // Set MAX485 to receive mode
  digitalWrite(MAX485_RE_NEG, LOW);
  digitalWrite(MAX485_DE, LOW);
}

void loop() {
  // Send a command to the ABB Aurora inverter
  sendCommand();

  // Wait for a response and print it to the Serial Monitor
  if (mySerial.available()) {
    while (mySerial.available()) {
      char c = mySerial.read();
      Serial.print(c);
    }
  }

  // Delay before sending the next command
  delay(2000);
}

void sendCommand() {
  // Set MAX485 to transmit mode
  digitalWrite(MAX485_RE_NEG, HIGH);
  digitalWrite(MAX485_DE, HIGH);

  // Send a command (example command)
  mySerial.print("Your command here");

  // Set MAX485 back to receive mode
  digitalWrite(MAX485_RE_NEG, LOW);
  digitalWrite(MAX485_DE, LOW);
}
