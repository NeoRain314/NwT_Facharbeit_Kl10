#include <Wire.h>
#include <RTClib.h>  // RTC-Bibliothek
RTC_DS3231 rtc;

int analog_input = A0;   // Mikrofon-Signal
int digital_input = 3;   // Schwellwert-Signal
int buttonPinAn = 4;     // Startknopf
int buttonPinAus = 5;    // Ausknopf
bool recording = false;  // Startzustand: keine Aufnahme

int abc[100];             // Speicher für Messwerte
String timeStamps[100];  // Speicher für Zeitstempel
int index = 0;           // Aktuelle Position im Array

void setup() {
  pinMode(analog_input, INPUT);
  pinMode(digital_input, INPUT);
  pinMode(buttonPinAn, INPUT_PULLUP);
  pinMode(buttonPinAus, INPUT_PULLUP);
  Serial.begin(9600);

  if (!rtc.begin()) {
    Serial.println("RTC nicht gefunden!");
    while (1);
  }
  Serial.println("Schlafüberwachung gestartet!");
}


void loop() {
  if (digitalRead(buttonPinAn) == LOW) {
    recording = !recording;  // Umschalten bei Tastendruck
    delay(500);              // Entprellung
    Serial.println(recording ? "Aufnahme gestartet" : "Aufnahme gestoppt");
  }

  if (digitalRead(buttonPinAus) == LOW) {
    Serial.println(index);
    // Wenn die Aufnahme gestoppt wurde, Daten ausgeben
    if (index > 0) {
      Serial.println("Messung beendet. Gespeicherte Daten:");
      float a = 0;
      for (int i = 0; i < index; i++) {
        Serial.print("Zeit: ");
        Serial.print(timeStamps[i]);
        Serial.print(", Spannung: ");
        a = abc[i];
        //a = 3.5;
        Serial.print(a/1000);
        Serial.println(" V");
      }
      index = 0;  // Daten zurücksetzen für nächste Aufnahme
    } else {
      Serial.println("Keine gespeicherten Daten!");
    }
  }
  if (recording) {
    float analog_value = analogRead(analog_input) * (5.0 / 1023.0) * 1000;
    int digital_value = digitalRead(digital_input);

    if (digital_value == 1) {  // Schwellwert überschritten
      if (index < 100) {       // Array nicht überfüllen
        abc[index] = (int)analog_value;
        DateTime now = rtc.now();
        timeStamps[index] = String(now.hour()) + ":" + String(now.minute()) + ":" + String(now.second());
        index++;
      }
    }

    Serial.print("Spannung: ");
    Serial.print(analog_value);
    Serial.print(" V, \t Status: ");
    Serial.println(digital_value == 1 ? "Geräusch erkannt!" : "Ruhe...");

    delay(100);  // Zeit zwischen Messungen
  }
  /*else if (!recording) {
      // Wenn die Aufnahme gestoppt wurde, Daten ausgeben
      Serial.println("Messung beendet. Gespeicherte Daten:");
      for (int i = 0; i < index; i++) {
        Serial.print("Zeit: ");
        Serial.print(timeStamps[i]);
        Serial.print(", Spannung: ");
        Serial.print(abc[i]);
        Serial.println(" V");
      }
      index = 0; // Daten zurücksetzen für nächste Aufnahme
    }*/
}
