#include <Servo.h>

#include <RCSwitch.h>

RCSwitch mySwitch = RCSwitch();

Servo S1;

void setup() {
  Serial.begin(9600);
  mySwitch.enableReceive(0);  // Pin für Empfänger
  S1.attach(9);
}

void loop() {
  if (mySwitch.available()) {
    int receivedValue = mySwitch.getReceivedValue();
    Serial.println(receivedValue);
    if (receivedValue == 1234) { 
      tunServo();
    }
    mySwitch.resetAvailable();
  }
}


void tunServo(){
  S1.write(90);  // Servo auf Position setzen
  delay(1000);
  S1.write(0);
  }
