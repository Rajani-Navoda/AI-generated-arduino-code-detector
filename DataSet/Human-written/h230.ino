#include <ACI_10K_an.h>

void setup() {
 Serial.begin(9600);
}

void loop() {
  Aci_10K an10k; //start an instance of the library
  //Aci_10K an10k(3.3,12);support for 3.3 volt board and/or 12bit analog read resolution
  Serial.print("temp: ");
  Serial.println(an10k.getTemp(analogRead(0)));
  delay(1000);

}