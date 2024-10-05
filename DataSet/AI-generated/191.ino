#include <AceButton.h>

using namespace ace_button;

// Constants for the button and timer
const int BUTTON_PIN = 2;
AceButton button(BUTTON_PIN);

enum State {
    STOPPED,
    RUNNING
};

State stopwatchState = STOPPED;
unsigned long startTime = 0;
unsigned long elapsedTime = 0;
bool allEventsEnabled = true;

void setup() {
    Serial.begin(9600);
    button.init();
    button.setEventHandler(eventHandler);
    button.enableAllEvents();
}

void loop() {
    // Check the button state
    button.check();
}

void eventHandler(AceButton* button, uint8_t eventType) {
    switch (eventType) {
        case AceButton::kEventPressed:
            if (stopwatchState == STOPPED) {
                startTime = millis(); // Start the stopwatch
                stopwatchState = RUNNING;
                Serial.println("Stopwatch started.");
            } else if (stopwatchState == RUNNING) {
                elapsedTime = millis() - startTime; // Stop the stopwatch
                stopwatchState = STOPPED;
                Serial.print("Stopwatch stopped. Time elapsed: ");
                Serial.print(elapsedTime);
                Serial.println(" ms");
            }
            break;

        case AceButton::kEventLongPressed:
            stopwatchState = STOPPED; // Reset state
            elapsedTime = 0;
            Serial.println("Stopwatch reset.");
            allEventsEnabled = !allEventsEnabled;
            if (allEventsEnabled) {
                button->enableAllEvents();
                Serial.println("All events enabled.");
            } else {
                button->disableAllEvents();
                Serial.println("All events disabled. Only Pressed and Released events are active.");
            }
            break;
    }
}
