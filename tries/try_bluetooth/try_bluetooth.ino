#include <SoftwareSerial.h>

#define ledPin 7
int state = 0;

void setup() {
  pinMode(ledPin, OUTPUT);
  digitalWrite(ledPin, LOW);
  Serial.begin(9600); // Default communication rate of the Bluetooth module
}

void loop() {
  Serial.println(Serial.available());
  if(Serial.available() > 0){ // Checks whether data is comming from the serial port
    state = Serial.read(); // Reads the data from the serial port
 }

 if (state == '0') {
  digitalWrite(ledPin, LOW); // Turn LED OFF
  Serial.println("LED: OFF"); // Send back, to the phone, the String "LED: ON"
  state = 0;
 }
 else if (state == '1') {
  digitalWrite(ledPin, HIGH);
  Serial.println("LED: ON");;
  state = 0;
 } 
}

/*
// RX, TX
SoftwareSerial btSerial(10, 11); 

void setup() {
  Serial.begin(9600);       // Für Debug über USB
  btSerial.begin(9600);     // HC-05 Standard Baudrate
  Serial.println("Bluetooth ready");
}

void loop() {
  // Vom Bluetooth lesen und über USB ausgeben
  if (btSerial.available()) {
    char data = btSerial.read();
    Serial.print("Von Handy: ");
    Serial.println(data);
  }

  // Vom PC lesen und an Handy senden
  if (Serial.available()) {
    char data = Serial.read();
    btSerial.write(data);
  }
}*/
