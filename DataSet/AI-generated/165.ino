// Define pin connections
const int dataPin = 8;   // DS (Data Serial)
const int latchPin = 10; // ST_CP (Store Clock)
const int clockPin = 9;  // SH_CP (Shift Clock)

// Define the number of LEDs
const int numLeds = 8;

void setup() {
  // Set the pin modes
  pinMode(dataPin, OUTPUT);
  pinMode(latchPin, OUTPUT);
  pinMode(clockPin, OUTPUT);

  // Initialize the LEDs to be off
  shiftOut(0x00); // Send zero to turn off all LEDs
}

void loop() {
  // Light up LEDs one by one
  for (int i = 0; i < numLeds; i++) {
    shiftOut(1 << i); // Shift out a byte to light up the ith LED
    delay(500);       // Wait for 0.5 seconds
  }

  // Turn off all LEDs
  shiftOut(0x00);
  delay(500); // Wait for 0.5 seconds
}

// Function to shift out a byte to the 74HC595
void shiftOut(byte data) {
  digitalWrite(latchPin, LOW);  // Prepare to shift data
  shiftOut(dataPin, clockPin, MSBFIRST, data); // Shift data out
  digitalWrite(latchPin, HIGH); // Latch data to output pins
}

// Function to shift out data (from the ShiftOut library)
void shiftOut(int dataPin, int clockPin, int bitOrder, byte val) {
  int i;
  byte pinState;

  for (i = 0; i < 8; i++) {
    if (bitOrder == MSBFIRST)
      pinState = (val & (1 << (7 - i))) ? HIGH : LOW;
    else
      pinState = (val & (1 << i)) ? HIGH : LOW;

    digitalWrite(clockPin, LOW);
    digitalWrite(dataPin, pinState);
    digitalWrite(clockPin, HIGH);
  }
}
