#ifndef SIGNALAROUND_H
#define SIGNALAROUND_H

#include <Arduino.h>

class SignalArduino {
  public:
    SignalArduino(const int* ledPins, int numLEDs);
    void begin();
    void setPattern(int pattern);
    void update();
    
  private:
    const int* _ledPins;
    int _numLEDs;
    int _currentPattern;
    unsigned long _lastUpdate;
    void _applyPattern(int pattern);
};

#endif
