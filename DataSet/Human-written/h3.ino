/*
  ATmega32U4 AirQuality Example v0.0.1
* By: https://github.com/JCardoen
*/
#include"AirQuality.h"
#include"Arduino.h"
AirQuality airqualitysensor;
int current_quality =-1;
void setup()
{
    Serial.begin(9600);
    airqualitysensor.init(A0);
}
void loop()
{
    current_quality=airqualitysensor.slope();
    if (current_quality >= 0)
    {
        if (current_quality==0)
            Serial.println("High pollution! Force signal active");
        else if (current_quality==1)
            Serial.println("High pollution!");
        else if (current_quality==2)
            Serial.println("Low pollution!");
        else if (current_quality ==3)
            Serial.println("Fresh air");
    }
}

ISR(TIMER1_OVF_vect)
{
  TCNT1 = 34286;
  airqualitysensor.last_vol = airqualitysensor.first_vol;
  airqualitysensor.first_vol = analogRead(A0);
  airqualitysensor.counter = 0;
  airqualitysensor.timer_index = 1;
  PORTB = PORTB ^ 0x20;
}