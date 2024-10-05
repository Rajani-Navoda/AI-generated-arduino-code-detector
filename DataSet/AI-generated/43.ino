/*
  This program sends blocks of random data with random size,
  transmits the blocks to a local loop, and receives the data
  from the same loop. The received data is checked against the
  transmitted data for errors.
*/

#define MAX_BLOCK_SIZE 255 // Maximum size of a data block

void setup() {
  Serial.begin(9600); // Initialize serial communication at 9600 baud rate
  randomSeed(analogRead(0)); // Initialize random seed based on analog noise
}

void loop() {
  // Generate random block size
  int blockSize = random(1, MAX_BLOCK_SIZE + 1);

  // Create an array to hold the data block
  byte dataBlock[MAX_BLOCK_SIZE];
  
  // Fill the block with random data
  for (int i = 0; i < blockSize; i++) {
    dataBlock[i] = random(0, 256);
  }

  // Send the block size first
  Serial.write((byte)blockSize);

  // Send the data block
  Serial.write(dataBlock, blockSize);

  // Wait for a while to simulate some processing delay
  delay(100);

  // Check if data is available to read
  if (Serial.available() > 0) {
    // Read the block size
    int receivedBlockSize = Serial.read();

    // Check if the received block size is valid
    if (receivedBlockSize <= MAX_BLOCK_SIZE && receivedBlockSize > 0) {
      byte receivedDataBlock[MAX_BLOCK_SIZE];
      
      // Wait until the full block is received
      int bytesRead = 0;
      while (bytesRead < receivedBlockSize) {
        if (Serial.available() > 0) {
          receivedDataBlock[bytesRead++] = Serial.read();
        }
      }

      // Compare received data with the transmitted data
      bool errorDetected = false;
      for (int i = 0; i < receivedBlockSize; i++) {
        if (dataBlock[i] != receivedDataBlock[i]) {
          errorDetected = true;
          break;
        }
      }

      // Report result
      if (errorDetected) {
        Serial.println("Error detected in received data.");
      } else {
        Serial.println("Data received correctly.");
      }
    } else {
      Serial.println("Invalid block size received.");
    }
  }

  // Wait before sending the next block
  delay(1000);
}
