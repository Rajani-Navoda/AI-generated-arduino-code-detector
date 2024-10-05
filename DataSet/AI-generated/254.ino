const int outputPin = 9;  // Output pin for PWM signal
const int maxValue = 255;  // Maximum value for the PWM signal
const int delayTime = 10;  // Delay between increments (in milliseconds)

void setup() {
  pinMode(outputPin, OUTPUT); // Set the output pin as an output
  Serial.begin(9600);         // Initialize serial communication
}

void loop() {
  // Generate a sawtooth waveform
  for (int value = 0; value <= maxValue; value++) {
    analogWrite(outputPin, value); // Output the PWM value
    delay(delayTime);               // Wait for a short duration
  }

  // Optionally, reset and create a descending ramp
  for (int value = maxValue; value >= 0; value--) {
    analogWrite(outputPin, value); // Output the PWM value
    delay(delayTime);               // Wait for a short duration
  }
}
