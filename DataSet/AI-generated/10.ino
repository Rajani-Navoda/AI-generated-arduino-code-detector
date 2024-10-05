#include <aREST.h>
#include <Adafruit_BLE_UART.h>  // Include Adafruit BLE UART library

// Create an instance of the aREST class
aREST rest = aREST();

// Create an instance of the Adafruit BLE UART class
Adafruit_BLE_UART ble_uart;

// Example function to be controlled via aREST
void ledOn() {
  digitalWrite(LED_BUILTIN, HIGH);  // Turn on the LED
  rest.answer("LED is ON");
}

void ledOff() {
  digitalWrite(LED_BUILTIN, LOW);   // Turn off the LED
  rest.answer("LED is OFF");
}

void setup() {
  // Initialize Serial communication
  Serial.begin(9600);

  // Initialize the LED pin
  pinMode(LED_BUILTIN, OUTPUT);

  // Initialize BLE UART
  ble_uart.begin();
  
  // Initialize aREST
  rest.function("ledon", ledOn);
  rest.function("ledoff", ledOff);

  Serial.println("Setup complete. Waiting for commands...");
}

void loop() {
  // Check if there's data available from BLE UART
  ble_uart.process();
  
  // Process aREST commands
  rest.process();
  
  // Small delay to avoid flooding the loop
  delay(100);
}
