#include "A4963.h"

// Define addresses for fault, speed, and PWM
#define FAULT_ADDRESS 8
#define SPEED_ADDRESS 9
#define PWM_ADDRESS 10

uint8_t pwm_value = 0; // Store current PWM value

void setup() {
  // Start serial communication at 115200 baud
  Serial.begin(115200);
  
  // Initialize A4963 motor driver
  A4963.begin();
  
  // Set initial PWM value to 0
  A4963.setPWM(pwm_value);
}

void ping() {
  // Send a ping response to indicate the A4963 is active
  Serial.write("A4963");
}

void write() {
  uint8_t data[3];
  Serial.readBytes(data, 3);
  
  uint16_t address = data[0];
  uint16_t value = (uint16_t(data[1]) | uint16_t(data[2]) << 8);
  uint16_t result = 0;

  if (address < 8) {
    // Write to the A4963 register and store result
    result = A4963.write(address << 13, value);
  } else if (address == PWM_ADDRESS) {
    // Set the PWM value
    A4963.setPWM(value);
    pwm_value = value; // Update stored PWM value
  }
  
  // Send back the result of the write operation
  Serial.write(result & 0xFF);
  Serial.write(result >> 8);
}

void read() {
  uint8_t data[1];
  Serial.readBytes(data, 1);
  
  uint16_t address = data[0];
  uint16_t result = 0;

  if (address < 8) {
    // Read from the A4963 register and store result
    result = A4963.read(address << 13);
  } else if (address == PWM_ADDRESS) {
    // Return the current PWM value
    result = pwm_value;
  }

  // Send back the result of the read operation
  Serial.write(result & 0xFF);
  Serial.write(result >> 8);
}

void loop() {
  if (Serial.available()) { // Check if data is available to read
    uint8_t command = Serial.read();
    
    switch (command) {
      case 'p': // Ping command
        ping();
        break;
      case 'w': // Write command
        write();
        break;
      case 'r': // Read command
        read();
        break;
      default: 
        // Unknown command; do nothing or handle error
        break;
    }
  }
}
