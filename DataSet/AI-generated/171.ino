#include <Accessories.h>
#include <Commanders.h>

// Define DCC addresses for each LED
#define DCC_LED1_ID 1001
#define DCC_LED2_ID 1002
#define DCC_LED3_ID 1003
#define DCC_LED4_ID 1004
#define DCC_LED5_ID 1005

// Define the LEDs
AccessoryLight led1;
AccessoryLight led2;
AccessoryLight led3;
AccessoryLight led4;
AccessoryLight led5;

// Define the ports for the LEDs
PortOnePin port1;
PortOnePin port2;
PortOnePin port3;
PortOnePin port4;
PortOnePin port5;

void setup() {
  // Initialize the Commanders and Accessories libraries
  Commanders::begin(LED_BUILTIN);  // Using the onboard LED for diagnostics
  Accessories::begin();

  // Initialize the ports for the LEDs
  port1.begin(2, DIGITAL);
  port2.begin(3, DIGITAL);
  port3.begin(4, DIGITAL);
  port4.begin(5, DIGITAL);
  port5.begin(6, DIGITAL);

  // Initialize the LED accessories
  led1.begin(&port1, DCC_LED1_ID);
  led2.begin(&port2, DCC_LED2_ID);
  led3.begin(&port3, DCC_LED3_ID);
  led4.begin(&port4, DCC_LED4_ID);
  led5.begin(&port5, DCC_LED5_ID);

  // Initialize the DCC Commander for controlling the LEDs
  DccCommander.begin(0x00, 0x00, digitalPinToInterrupt(3), true); // Adjust as needed
}

void loop() {
  unsigned long id = Commanders::loop();

  if (id != UNDEFINED_ID) {
    // Forward the event received from Commanders to the Accessories
    Accessories::RaiseEvent(id, (ACCESSORIES_EVENT_TYPE) Commanders::GetLastEventType(), Commanders::GetLastEventData());
  }

  // Call Accessories::loop() to handle the state of accessories
  Accessories::loop();
}
