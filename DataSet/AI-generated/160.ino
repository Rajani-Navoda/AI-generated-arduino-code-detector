#include <Accessories.h>
#include <Commanders.h>

// Define buttons for the control panel
ButtonsCommanderPush decouplerButton;
ButtonsCommanderSwitch leftSwitchButton;
ButtonsCommanderSwitch rightSwitchButton;

// Define motors for different functions
AccessoryMotorTwoWays leftSwitchMotor;
AccessoryMotorTwoWays rightSwitchMotor;
AccessoryMotorOneWay decouplerMotor;

// Define ports for connecting the motors
PortTwoPins leftSwitchPort;
PortTwoPins rightSwitchPort;
PortOnePin decouplerPort;

void setup() {
  // Initialize Commanders and Accessories libraries
  Commanders::begin(LED_BUILTIN);
  Accessories::begin(0, 500);

  // Initialize DCC Commander with optional LED indicator
  DccCommander.begin(0x00, 0x00, digitalPinToInterrupt(3), true);

  // Configure buttons for the control panel
  leftSwitchButton.begin();
  leftSwitchButton.AddEvent(DCCINT(15, 0), 2); // Event for left switch, position 0
  leftSwitchButton.AddEvent(DCCINT(15, 1), 7); // Event for left switch, position 1

  rightSwitchButton.begin();
  rightSwitchButton.AddEvent(DCCINT(16, 0), 4); // Event for right switch, position 0
  rightSwitchButton.AddEvent(DCCINT(16, 1), 5); // Event for right switch, position 1

  decouplerButton.begin(DCCINT(17, 0), 6); // Single event for the decoupler

  // Initialize ports for motors
  leftSwitchPort.begin(8, 9, DIGITAL);
  rightSwitchPort.begin(10, 11, DIGITAL);
  decouplerPort.begin(12, DIGITAL);

  // Initialize accessories with their respective ports and DCC IDs
  // 255 is the speed, 400 is the activation duration in milliseconds
  leftSwitchMotor.beginTwoWays(&leftSwitchPort, DCCINT(15, 0), DCCINT(15, 1), 255, 400);
  rightSwitchMotor.beginTwoWays(&rightSwitchPort, DCCINT(16, 0), DCCINT(16, 1), 255, 400);
  decouplerMotor.begin(&decouplerPort, DCCINT(17, 0), 255, 400);
}

void loop() {
  // Process events from the Commanders library
  unsigned long eventId = Commanders::loop();

  // If an event ID is valid, raise the corresponding event in the Accessories library
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
