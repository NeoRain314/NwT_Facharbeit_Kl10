#include <RCSwitch.h>

RCSwitch mySwitch = RCSwitch();

void setup() {
  mySwitch.enableTransmit(10);  // Der Sender wird an Pin 10 angeschlossen
  Serial.begin(9600);
  Serial.println("Start Sender");
}
void loop() {
  mySwitch.send(1234, 24); // Der 433mhz Sender versendet die Dezimalzahl „1234“
  Serial.println("sended");
  delay(3000);  // Eine Sekunde Pause, danach startet der Sketch von vorne
} 
