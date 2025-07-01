#include <RCSwitch.h>

RCSwitch mySwitch = RCSwitch();

void setup() {
  Serial.begin(9600);
  pinMode(3, INPUT_PULLUP)
}

void loop() {
  if(digitalRead(3) == 0){
    mySwitch.send(9123, 24); //Code for okPressed
    delay(500);
  }
}


