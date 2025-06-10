#include <Wire.h>
#include <RTClib.h>  // RTC-Bibliothek
RTC_DS3231 rtc;

int analog_input = A0;  // Mikrofon-Signal
int digital_input = 3;  // Schwellwert-Signal
int buttonPin = 4;      // Startknopf
bool recording = false; // Startzustand: keine Aufnahme

float soundValues[100]; // Speicher für Messwerte
String timeStamps[100]; // Speicher für Zeitstempel
int index = 0;          // Aktuelle Position im Array

void setup() {
    pinMode(analog_input, INPUT);
    pinMode(digital_input, INPUT);
    pinMode(buttonPin, INPUT_PULLUP); // Taster mit internem Pull-Up
    Serial.begin(9600);
    
    if (!rtc.begin()) {
        Serial.println("RTC nicht gefunden!");
        while (1);
    }
    Serial.println("Schlafüberwachung gestartet!");
}

void loop() {
  if (digitalRead(buttonPin) == LOW) { 
    while (digitalRead(buttonPin) == LOW); // Warten, bis der Button losgelassen wird
    recording = !recording; // Umschalten nach Loslassen des Buttons

    if (!recording && index > 0) {
        printResults();
        index = 0; // Arrays zurücksetzen
    }
}
    
  if (recording) {
    float analog_value = analogRead(analog_input) * (5.0 / 1023.0);
    int digital_value = digitalRead(digital_input);
        
    if (digital_value == 1) {  // Schwellwert überschritten
      if (index < 100) {  // Array nicht überfüllen
        soundValues[index] = analog_value;
        DateTime now = rtc.now();
        timeStamps[index] = String(now.hour()) + ":" + String(now.minute()) + ":" + String(now.second());
        index++;
      }
    }

    Serial.print("Spannung: ");
    Serial.print(analog_value);
    Serial.print(" V, \t Status: ");
    Serial.println(digital_value == 1 ? "Geräusch erkannt!" : "Ruhe...");
        
    delay(100); // Zeit zwischen Messungen
  }


}

void printResults() {
    Serial.println("\n=== Übersicht der erkannten Geräusche ===");
    for (int i = 0; i < index; i++) {
        Serial.print("Zeit: ");
        Serial.print(timeStamps[i]);
        Serial.print(" -> Geräuschpegel: ");
        Serial.print(soundValues[i], 4);
        Serial.println(" V");
    }
    Serial.println("=======================================");
}
