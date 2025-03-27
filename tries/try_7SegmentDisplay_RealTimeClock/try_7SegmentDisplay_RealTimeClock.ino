#include <TM1637Display.h>
#include <Aduino.h>

#define CLK 2
#define DIO 3

TM1637Display display(CLK, DIO);

#include //Bibliotheken einbinden!!!!!!!
#include <Wire.h>

RTC_DS3231 rtc; 

void setup() {
  Serial.begin(9600);

  if (!rtc.begin()) {
    Serial.println("RTC nicht gefunden!");
    while (1);
 }

 // Falls die RTC nicht eingestellt ist, die aktuelle Zeit setzen:
  if (rtc.lostPower()) {
    Serial.println("RTC hat Strom verloren, Setze Zeit auf Kompilierzeit!");
    rtc.adjust(DateTime(F(__DATE__), F(__TIME__)));
  }

  display.setBrightness(0x0f); // Helligkeit vom Display einstellen (15)
}

void loop() {
  DateTime now = rtc.now();
  
  int hour = now.hour(), DEC;
  int minute = now.minute(), DEC;
  
  display.showNumberDecEx(hour * 100 + minute, 0b01000000);


}
