#include <Accessories.h>
#include <Commanders.h>

// Define the button ID for DCC control
#define DCC_LIGHT_ID 1234

// Define the LED
AccessoryLight light;
PortOnePin port;

void setup() {
  // Initialize the Commanders and Accessories libraries
  Commanders::begin(LED_BUILTIN);  // Using the onboard LED for diagnostics
  Accessories::begin();

  // Initialize the port for the LED (Pin 7)
  port.begin(7, DIGITAL);

  // Initialize the LED accessory
  light.begin(&port, DCC_LIGHT_ID);

  // Initialize the DCC Commander for controlling the light
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
