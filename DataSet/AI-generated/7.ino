void setup() {
  // Initialize serial communication at 9600 baud rate
  Serial.begin(9600);
  Serial.println("Echo program started. Awaiting messages...");
}

void loop() {
  // Check if there is any data available to read from the serial port
  if (Serial.available() > 0) {
    // Read the incoming byte
    char receivedChar = Serial.read();

    // Echo the received character back to the sender
    Serial.print(receivedChar);
  }
}
