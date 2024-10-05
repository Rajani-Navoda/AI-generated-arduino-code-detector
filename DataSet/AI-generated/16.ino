#include <SPI.h>
#include <SD.h>

// Define the pin for the SD card chip select (CS) line
const int chipSelect = 10;  // Change this to match your SD card module's CS pin

void setup() {
  Serial.begin(9600);

  // Initialize SD card
  if (!SD.begin(chipSelect)) {
    Serial.println("Initialization failed!");
    return;
  }
  Serial.println("Initialization done.");

  // Create a file and write data to it
  createAndWriteFile("/example.txt", "Hello, SD card!");

  // Read and display the content of the file
  readFile("/example.txt");

  // List all files in the root directory
  listFiles("/");
}

void loop() {
  // Nothing to do here
}

void createAndWriteFile(const char* filename, const char* data) {
  File file = SD.open(filename, FILE_WRITE);

  if (file) {
    Serial.print("Writing to ");
    Serial.println(filename);

    file.println(data);  // Write data to the file
    file.close();        // Close the file
    Serial.println("Write done.");
  } else {
    Serial.print("Error opening ");
    Serial.println(filename);
  }
}

void readFile(const char* filename) {
  File file = SD.open(filename);

  if (file) {
    Serial.print("Reading from ");
    Serial.println(filename);

    while (file.available()) {
      Serial.write(file.read());  // Read and display file content
    }
    file.close();  // Close the file
    Serial.println();
  } else {
    Serial.print("Error opening ");
    Serial.println(filename);
  }
}

void listFiles(const char* directory) {
  Serial.print("Listing files in ");
  Serial.println(directory);

  File dir = SD.open(directory);

  if (dir) {
    while (true) {
      File entry = dir.openNextFile();
      if (!entry) {
        break;  // No more files
      }
      Serial.print("File: ");
      Serial.println(entry.name());  // Print file name
      entry.close();  // Close the file
    }
    dir.close();  // Close the directory
  } else {
    Serial.print("Error opening ");
    Serial.println(directory);
  }
}
