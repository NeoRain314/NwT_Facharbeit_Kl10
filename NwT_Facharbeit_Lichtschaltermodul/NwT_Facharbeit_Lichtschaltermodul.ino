#include <Wire.h>

#include <VirtualWire.h>

// <<< library <<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<< library <<< //
#include <Servo.h>
#include <Arduino.h>

// <<< inizaializing <<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<< inizaializing <<< //
#define RX_PIN 11  // Pin für den Empfänger
#define SERVO_PIN 9  // Pin für den Servo

int test = true

Servo S1;

// <<< setup <<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<< setup <<< //
void setup() {
  Serial.begin(9600);

  S1.attach(3); 
  vw_set_rx_pin(RX_PIN);
  vw_setup(2000); // Funkfrequenz (2000 Baud)
  vw_rx_start(); // Start des Empfängers
}

// <<< loop <<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<< loop <<< //
void loop() {
  uint8_t buffer[10];  // Puffer für empfangene Daten
  uint8_t buflen = sizeof(buffer);

 /* if (vw_get_message(buffer, &buflen)) {  //wenn ein Signal empfangen wird
    Serial.println("Signal empfangen! Schalter wird betätigt.");
    activateLight(); 
*/  

    if (test == true){
      test = false;
      activateLight(); 

    }

  }

}
void activateLight() {
  Serial.println("Schalter betätigen!");
  myServo.write(90);  // Servo auf Position bringen
  delay(1000); //!! !! !! !! !! !! !! !! !! !! !! !! !! !! !! !! !! !! !! !! !! !! !! !! !! !! !! !! !! !! !! !! !! !! !! !! !! !! !! !! !! !! !! !! !! !! !! !! !! !! !! !! !! !! !! !! !! !! !! !! !! !! 
  myServo.write(0);    // Zurücksetzen
}
