#include <SoftwareSerial.h>

#define ledPin 7
int state = 0;

void setup() {
  pinMode(ledPin, OUTPUT);
  digitalWrite(ledPin, LOW);
  Serial.begin(9600); // Default communication rate of the Bluetooth module

  

  /*digitalWrite(ledPin, HIGH);
  delay(1000);
  digitalWrite(ledPin, LOW);*/
}

void loop() {
  
  Serial.println("Hallo");
  delay(1000);

  /*Serial.println(Serial.available());
  if(Serial.available() > 0){ // Checks whether data is comming from the serial port
    state = Serial.read(); // Reads the data from the serial port
 }

 if (state == '0') {
  digitalWrite(ledPin, LOW); // Turn LED OFF
  Serial.println("LED: OFF"); // Send back, to the phone, the String "LED: ON"
  state = 0;
 }/
 else if (state == '1') {
  digitalWrite(ledPin, HIGH);
  Serial.println("LED: ON");;
  state = 0;
 } */
}
