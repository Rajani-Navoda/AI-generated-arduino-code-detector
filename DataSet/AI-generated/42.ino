/*
  This program echoes any line received on the serial line.
  A line is a sequence of ASCII characters terminated by a newline character ('\n').
  The line is echoed immediately after newline reception.
*/

#define MAX_LINE_LENGTH 100 // Maximum length of a line to be processed

void setup() {
  Serial.begin(9600); // Initialize serial communication at 9600 baud rate
}

void loop() {
  static char line[MAX_LINE_LENGTH]; // Buffer to store the received line
  static uint8_t index = 0;          // Index for the current position in the buffer

  while (Serial.available() > 0) {
    char c = Serial.read(); // Read a character from the serial input

    if (c == '\n') { // If a newline character is received
      line[index] = '\0'; // Null-terminate the line
      Serial.println(line); // Echo the line back to the serial output
      index = 0; // Reset the index for the next line
    } else {
      if (index < MAX_LINE_LENGTH - 1) {
        line[index++] = c; // Store the character in the buffer
      } else {
        // If the line exceeds the maximum length, discard the characters
        index = 0; // Reset the index
      }
    }
  }
}
