/* --------------------------------------------------------------
	Example sketch of sawtooth generator. 

	Author: Christoph Jurczyk
  -------------------------------------------------------------- */

#include <AD7390.h>

// Pins
#define DAC_CS 8

// DAC init
AD7390 dac(DAC_CS);

// Variables
uint16_t output_signal = 0;
boolean signal_direction = false;


void setup() {
}


void loop() {
  // signal generation
  if (signal_direction) {
    // down
    output_signal--;
    if (output_signal == 0) signal_direction = false;
  } else {
    // up
    output_signal++;
    if (output_signal >= 4095) signal_direction = true;
  }

  // output to DAC
  dac.writeValue(output_signal);
}