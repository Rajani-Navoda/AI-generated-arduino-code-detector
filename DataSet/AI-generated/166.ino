#include <Accessories.h>
#include <Commanders.h>

// Define buttons
ButtonsCommanderPush buttonTurnout1;
ButtonsCommanderPush buttonTurnout2;

// Define accessories
AccessoryTurnout turnout1;
AccessoryTurnout turnout2;

// Define ports
PortTwoPins portTurnout1;
PortTwoPins portTurnout2;

void setup() {
  Commanders::begin();
  Accessories::begin();

  // Initialize ports
  portTurnout1.begin(2, 3, DIGITAL); // Pin 2 and 3 for Turnout 1
  portTurnout2.begin(4, 5, DIGITAL); // Pin 4 and 5 for Turnout 2

  // Initialize accessories
  turnout1.begin(&portTurnout1, 1, 2); // Accessory 1 on ports 2 and 3
  turnout2.begin(&portTurnout2, 3, 4); // Accessory 2 on ports 4 and 5

  // Initialize buttons
  buttonTurnout1.begin(1, 6); // Button 1 for Turnout 1, pin 6
  buttonTurnout2.begin(2, 7); // Button 2 for Turnout 2, pin 7
}

void loop() {
  unsigned long id = Commanders::loop();

  if (id != UNDEFINED_ID) {
    // Pass the event to the accessories
    Accessories::RaiseEvent(id, (ACCESSORIES_EVENT_TYPE) Commanders::GetLastEventType(), Commanders::GetLastEventData());
  }

  Accessories::loop();
}
