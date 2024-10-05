#include <AccelStepper.h>
#include <AFMotor.h>

// Connect a stepper motor with 200 steps per revolution (1.8 degree)
// to motor port #2 (M3 and M4)
AF_Stepper motor(200, 2);

// you can change these to DOUBLE or INTERLEAVE or MICROSTEP!
void forwardstep() {  
  motor.onestep(FORWARD, SINGLE);
}
void backwardstep() {  
  motor.onestep(BACKWARD, SINGLE);
}

// Now we'll wrap the stepper in an AccelStepper object
AccelStepper stepper(forwardstep, backwardstep);

void setup() {
  stepper.setMaxSpeed(100.0);
  stepper.setSpeed(50);  // Set the speed in steps per second
}

void loop() {  
  stepper.runSpeed();
}
