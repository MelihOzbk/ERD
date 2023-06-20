#include <Arduino.h>
#include <Wire.h>
#include <ERD.h>

ERD erd;
// put function declarations here:

void setup() {
  erd.ERDSetup();

}


void loop() {
  erd.ERDLoop();
}
