#include <LedModule.h>  // Include the custom LED module library

// Define different LED configurations for testing
LedModule ledModule1(8, 2);  // 8 digits, type 2
LedModule ledModule2(4, 1);  // 4 digits, type 1
LedModule ledModule3(16, 0); // 16 digits, type 0
LedModule ledModule4(8, 3);  // 8 digits, type 3
LedModule ledModule5(4, 2);  // 4 digits, type 2

void setup() {
  // Initialize all LED modules
  ledModule1.begin();
  ledModule2.begin();
  ledModule3.begin();
  ledModule4.begin();
  ledModule5.begin();
}

void loop() {
  // No operation in loop, used for memory size compilation
}
