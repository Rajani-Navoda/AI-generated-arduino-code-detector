void setup() {
  Serial.begin(9600);  // Initialize Serial communication at 9600 baud
  randomSeed(analogRead(0));  // Initialize random seed using analog input
  Serial.println("Ready to send and receive data");
}

void loop() {
  // Generate random data between 0 and 255
  int randomData = random(0, 256);

  // Send random data over Serial
  Serial.write(randomData);

  // Delay to simulate transmission time
  delay(100);

  // Check if data is available to read
  if (Serial.available() > 0) {
    // Read the incoming byte
    int receivedData = Serial.read();

    // Echo the received data back
    Serial.print("Received: ");
    Serial.println(receivedData);

    // If the received data matches the sent data, confirm reception
    if (receivedData == randomData) {
      Serial.println("Data correctly received and echoed back.");
    } else {
      Serial.println("Mismatch in sent and received data.");
    }
  }

  // Small delay to prevent Serial flooding
  delay(500);
}
