

// <<< library <<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<< library <<< //
// 7SegmentDisplay:
#include <TM1637Display.h>
#include <Arduino.h>

// RealTimeClock:
#include <Adafruit_BusIO_Register.h>
#include <Adafruit_GenericDevice.h>
#include <Adafruit_I2CDevice.h>
#include <Adafruit_I2CRegister.h>
#include <Adafruit_SPIDevice.h>
#include <RTClib.h>
#include <Wire.h>

// <<< inizaializing <<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<< inizaializing <<< //
// 7SegmentDisplay:
#define CLK 5
#define DIO 7

TM1637Display display(CLK, DIO);

// RealTimeClock:
RTC_DS3231 rtc; 

// <<< setup <<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<< setup <<< //
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

// <<< loop <<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<< loop <<< //
void loop() {
  DateTime now = rtc.now();

  Serial.print(now.hour());
    Serial.print(":");
    Serial.println(now.minute());
  int hour = now.hour();
  int minute = now.minute();

  //hour = (hour + 1) % 24; // Sommerzeit (+1)
 display.showNumberDecEx(hour * 100 + minute, 0b01000000);

  delay(1000);
}

