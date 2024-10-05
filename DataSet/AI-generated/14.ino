#include <AStar32U4Buzzer.h>  // Include the AStar32U4Buzzer library

// Create an instance of the AStar32U4Buzzer class
AStar32U4Buzzer buzzer;

// Notes and durations
const int melody[] = {
  NOTE_C4, NOTE_D4, NOTE_E4, NOTE_F4, NOTE_G4, NOTE_A4, NOTE_B4, NOTE_C5
};
const int noteDurations[] = {
  4, 4, 4, 4, 4, 4, 4, 4
};

void setup() {
  // Initialize the buzzer
  buzzer.begin();

  // Play a frequency
  buzzer.playFrequency(440, 500); // Play 440 Hz (A4) for 500 ms
  delay(500);

  // Play notes from an array
  for (int i = 0; i < 8; i++) {
    buzzer.playNote(melody[i], 1000 / noteDurations[i]);
    delay(1000 / noteDurations[i] + 10); // Add a short pause between notes
  }

  // Play notes from program space (flash memory)
  buzzer.playFromProgramSpace(melody, 8, noteDurations);
  delay(1000 * 8); // Wait for all notes to finish
}

void loop() {
  // Example of stopping the buzzer
  if (buzzer.isPlaying()) {
    buzzer.stopPlaying();
  }

  // You can perform other tasks here while the buzzer is playing
  // or check periodically if it's still playing
}
