#include <RTClib.h>
#include <Wire.h>


RTC_DS3231 rtc; // Oder RTC_DS1307 rtc; wenn du ein DS1307-Modul nutzt

void setup () {
  Serial.begin(9600);

  if (!rtc.begin()) {
    Serial.println("RTC nicht gefunden!");
    while (1);
  }

  // ✅ HIER DEINE ZEIT EINTRAGEN (Jahr, Monat, Tag, Stunde, Minute, Sekunde)
  rtc.adjust(DateTime(2025, 6, 29, 12, 25, 0));  // Beispiel: 29. Juni 2025, 14:30:00

  Serial.println("Zeit gesetzt!");
}

void loop () {
  DateTime now = rtc.now();
  
  Serial.print("Zeit: ");
  Serial.print(now.hour());
  Serial.print(":");
  Serial.print(now.minute());
  Serial.print(":");
  Serial.println(now.second());

  delay(1000);
}