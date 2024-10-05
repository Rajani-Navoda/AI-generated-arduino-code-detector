#include <Accessories.h>
#include <Commanders.h>
#include <AccelStepper.h>  // Include the AccelStepper library for stepper motor control

// Define DCC address for the stepper motor
#define DCC_STEPPER_ID 2001

// Define stepper motor control pins
#define STEP_PIN 8
#define DIR_PIN 9

// Create the stepper motor object
AccelStepper stepper(AccelStepper::DRIVER, STEP_PIN, DIR_PIN);

// Define the stepper motor accessory
AccessoryStepper stepperMotor;
PortTwoPins port;

void setup() {
  // Initialize the Commanders and Accessories libraries
  Commanders::begin(LED_BUILTIN);  // Using the onboard LED for diagnostics
  Accessories::begin();

  // Initialize the ports for the stepper motor
  port.begin(STEP_PIN, DIR_PIN, DIGITAL);

  // Initialize the stepper motor accessory
  stepperMotor.begin(&port, DCC_STEPPER_ID);

  // Set up the stepper motor parameters (adjust as needed)
  stepper.setMaxSpeed(1000);  // Max speed in steps per second
  stepper.setAcceleration(500);  // Acceleration in steps per second squared

  // Initialize the DCC Commander for controlling the stepper motor
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

  // Update the stepper motor
  stepper.run();
}
