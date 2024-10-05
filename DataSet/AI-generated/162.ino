#include <Accessories.h>
#include <Commanders.h>

#define TEMPO 20000 // Time to wait before resetting the system

// Define the button for ILS (Inductive Loop Sensor)
ButtonsCommanderPush ilsButton;

// Define the servo motor
AccessoryServo servoMotor;

// Define the LEDs
AccessoryLightMulti leds;

// Define the ports for connecting the servo and LEDs
PortServo servoPort;
PortOnePin ledPort1;
PortOnePin ledPort2;

void setup() {
  // Initialize Commanders and Accessories libraries
  Commanders::begin(LED_BUILTIN);
  Accessories::begin(0, 500); // Initialize Accessories with EEPROM settings

  // Set up the ILS button with a unique event ID
  ilsButton.begin(1234, 6);

  // Initialize ports for the servo and LEDs
  servoPort.begin(14);
  ledPort1.begin(7, DIGITAL_INVERTED);
  ledPort2.begin(8, DIGITAL_INVERTED);

  // Initialize the LEDs accessory with blinking settings
  leds.begin(0, 2, 500); // Two LEDs, blinking interval of 500ms
  leds.beginLight(0, &ledPort1); // Setup first LED
  leds.beginLight(1, &ledPort2); // Setup second LED

  // Start blinking LEDs
  leds.SetBlinking(0, 500); // Blink every 500ms
  leds.SetBlinking(1, 500); // Blink every 500ms

  // Configure the servo motor with movement range and positions
  servoMotor.begin(&servoPort, 50, 95, 135, 1); // Servo with 50ms movement duration and range 95-135 degrees
  servoMotor.AddMinMaxMovingPositions(456, 789); // Define min and max positions
}

unsigned long closureTime = 0;

void loop() {
  // Handle Accessories library events
  Accessories::loop();

  // Handle Commanders library events
  unsigned long eventId = Commanders::loop();

  // Check if the ILS button was pressed
  if (eventId == 1234) {
    if (closureTime == 0) {
      closureTime = millis(); // Record the current time

      // Start LED blinking and move the servo to the minimum position
      leds.Blink();
      servoMotor.MoveMinimum();

      // Exit loop to wait for next action
      return;
    } else {
      closureTime = millis(); // Reset the closure time if the button is pressed again
    }
  }

  // If the closure time is set, check if the TEMPO has elapsed
  if (closureTime > 0) {
    if (millis() - closureTime > TEMPO) {
      // Stop the animation: move servo to maximum position and turn off LEDs
      closureTime = 0;
      servoMotor.MoveMaximum();
      leds.LightOff();
    }
  }
}
