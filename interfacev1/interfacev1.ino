//Dispatch Console Interface

#include "config.h"
#include "pinout.h"
#include "functions.h"

boolean emergencysent = 0;
boolean auxiliarysent = 0;

void setup() {
  Serial.begin(baudrate);
  initializepins();
}
void loop() {
  checkforevents();
  holdinterrupt();
  holdtonecheck();
  heartbeatcycle();
  if (emergencyactive()) {
    if (emergencysent == 0) {
      Serial.println(emergencystring);
      emergencysent = 1;
    }
  }
  else{
    emergencysent = 0;
  }
  if (auxactive()) {
    if (auxiliarysent == 0) {
      Serial.println(auxalarmstring);
      auxiliarysent = 1;
    }
  }
  else{
    auxiliarysent = 0;
  }
}
