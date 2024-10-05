#include <Accessories.h>
#include <Commanders.h>

// Define buttons for the control panel
ButtonsCommanderSwitch crossoverButton;

// Define motors for different directions
AccessoryMotorTwoWays topLeftSwitch;
AccessoryMotorTwoWays topRightSwitch;
AccessoryMotorTwoWays bottomLeftSwitch;
AccessoryMotorTwoWays bottomRightSwitch;

// Define a group to manage the motors
AccessoryGroup crossoverGroup;

// Define ports for connecting the motors
PortTwoPins topLeftSwitchPort;
PortTwoPins topRightSwitchPort;
PortTwoPins bottomLeftSwitchPort;
PortTwoPins bottomRightSwitchPort;

void setup() {
  // Initialize Commanders and Accessories libraries
  Commanders::begin(LED_BUILTIN);
  Accessories::begin(0, 500);

  // Initialize DCC Commander with optional LED indicator
  DccCommander.begin(0x00, 0x00, digitalPinToInterrupt(3), true);

  // Configure the crossover button
  crossoverButton.begin();
  crossoverButton.AddEvent(DCCINT(15, 0), 4); // Event for crossover button position 0
  crossoverButton.AddEvent(DCCINT(15, 1), 5); // Event for crossover button position 1

  // Initialize motor ports
  topLeftSwitchPort.begin(7, 8, DIGITAL);
  topRightSwitchPort.begin(9, 10, DIGITAL);
  bottomLeftSwitchPort.begin(11, 12, DIGITAL);
  bottomRightSwitchPort.begin(14, 15, DIGITAL);

  // Initialize motors with their respective ports and DCC IDs
  // Speed is set to maximum (255) and activation duration is 400 milliseconds
  topLeftSwitch.beginTwoWays(&topLeftSwitchPort, 1000, 1001, 255, 400);
  topRightSwitch.beginTwoWays(&topRightSwitchPort, 1002, 1003, 255, 400);
  bottomLeftSwitch.beginTwoWays(&bottomLeftSwitchPort, 1004, 1005, 255, 400);
  bottomRightSwitch.beginTwoWays(&bottomRightSwitchPort, 1006, 1007, 255, 400);

  // Create and configure the group of motors
  crossoverGroup.begin();

  // First state: all motors in default position
  crossoverGroup.AddState(DCCINT(15, 0), false); // Non-simultaneous execution
  crossoverGroup.AddStateItem(DCCINT(15, 0), topLeftSwitch, LEFT);
  crossoverGroup.AddStateItem(DCCINT(15, 0), topRightSwitch, LEFT);
  crossoverGroup.AddStateItem(DCCINT(15, 0), bottomLeftSwitch, LEFT);
  crossoverGroup.AddStateItem(DCCINT(15, 0), bottomRightSwitch, LEFT);

  // Second state: all motors in diverged position
  crossoverGroup.AddState(DCCINT(15, 1), false); // Non-simultaneous execution
  crossoverGroup.AddStateItem(DCCINT(15, 1), topLeftSwitch, RIGHT);
  crossoverGroup.AddStateItem(DCCINT(15, 1), topRightSwitch, RIGHT);
  crossoverGroup.AddStateItem(DCCINT(15, 1), bottomLeftSwitch, RIGHT);
  crossoverGroup.AddStateItem(DCCINT(15, 1), bottomRightSwitch, RIGHT);
}

void loop() {
  // Process events from the Commanders library
  unsigned long eventId = Commanders::loop();

  // If a valid event ID is received, send it to the Accessories library
  if (eventId != UNDEFINED_ID) {
    Accessories::RaiseEvent(
      eventId,
      (ACCESSORIES_EVENT_TYPE) Commanders::GetLastEventType(),
      Commanders::GetLastEventData()
    );
  }

  // Process the Accessories library loop
  Accessories::loop();
}
