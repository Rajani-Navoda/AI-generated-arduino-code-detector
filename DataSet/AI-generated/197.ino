#include "AceMenu.h"
#include "Terminal.h"

#define kTemperatureDelta 3

#define kEepromSetpoint ((uint16_t *)0)
#define kEepromHysteresis ((uint16_t *)2)

int temperature = 200; // Simulated current temperature
int heater = 0;        // Heater status

// Getter functions
int getTemperature() { return temperature; }
int getHeater() { return heater; }
int getSetPoint() { return (int)eeprom_read_word(kEepromSetpoint); }
int getHysteresis() { return (int)eeprom_read_word(kEepromHysteresis); }

// Setter functions
void setSetPoint(int v) { eeprom_write_word(kEepromSetpoint, (uint16_t)v); }
void setHysteresis(int v) { eeprom_write_word(kEepromHysteresis, (uint16_t)v); }

// Menu items
menuItem menuItems[] = {
    {"TEMP", getTemperature, NULL, Format::deci, 0, 0},
    {"SET", getSetPoint, setSetPoint, Format::deci, 100, 400},
    {"HYST", getHysteresis, setHysteresis, Format::deci, 5, 100},
    {"HEAT", getHeater, NULL, Format::boolean, 0, 1},
};
#define kMenuCount (sizeof(menuItems) / sizeof(menuItem))

Terminal terminal(Serial, 9600);
AceMenu menu = AceMenu(menuItems, kMenuCount, terminal, terminal);

void setup() {
    menu.begin(); // Initialize the menu
}

void loop() {
    menu.update(); // Update the menu

    // Temperature control logic
    if (heater == true) {
        if (temperature > getSetPoint() + getHysteresis())
            heater = false; // Turn off heater
    } else {
        if (temperature < getSetPoint() - getHysteresis())
            heater = true; // Turn on heater
    }

    // Simulate temperature changes every 500 ms
    static int temperatureDelta = kTemperatureDelta;
    static long unsigned int waitUntil = 0;
    if (millis() > waitUntil) {
        waitUntil = millis() + 500L;
        temperature += temperatureDelta; // Change temperature
        if (temperature > 250)
            temperatureDelta = -kTemperatureDelta; // Ramp down
        if (temperature < 150)
            temperatureDelta = kTemperatureDelta; // Ramp up
    }
}
