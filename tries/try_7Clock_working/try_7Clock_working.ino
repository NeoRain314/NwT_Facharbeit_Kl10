#include <Wire.h>

#include <Adafruit_BusIO_Register.h>
#include <Adafruit_GenericDevice.h>
#include <Adafruit_I2CDevice.h>
#include <Adafruit_I2CRegister.h>
#include <Adafruit_SPIDevice.h>

#include <RTClib.h>

/* C++ Code
 *  there is going to be written "11 30" on the 7SegmentDisplay 
 */

#include <TM1637Display.h>
#include <Arduino.h>

// Module connection pins (Digital Pins)
#define CLK 5
#define DIO 6

TM1637Display display(CLK, DIO);

#define TEST_DELAY   2000


RTC_DS3231 rtc; 

void setup()
{
    Serial.begin(9600);
    display.setBrightness(0x0f); // Helligkeit auf 15??? 


    if (!rtc.begin()) {
    Serial.println("RTC nicht gefunden!");
    while (1);
  }

 // Falls die RTC nicht eingestellt ist, die aktuelle Zeit setzen:
  if (rtc.lostPower()) {
    Serial.println("RTC hat Strom verloren, Setze Zeit auf Kompilierzeit!");
    rtc.adjust(DateTime(F(__DATE__), F(__TIME__)));
  }
}

void loop() {
  DateTime now = rtc.now();
  
  Serial.print(now.hour());
    Serial.print(":");
    Serial.println(now.minute());



  int hour = now.hour();
  int minute = now.minute();
 
  uint8_t data[] = { 255, 255, 255, 255 }; // array wert zw 0 und 255 (--> unit8_data) jeder einzelne wert auf 255 (0xff)
  uint8_t blank[] = { 0x00, 0x00, 0x00, 0x00 }; // -"- Wert auf 0 (0x00)

  //display.setSegments(data);
  //delay(TEST_DELAY);
    display.showNumberDecEx(hour * 100 + minute, 0b01000000);  // hour*100+minute (--> vierstellige Zahl (11*100*30 =1130)) ;0b01000000 Binärzahl (--> aktiviert den Doppelpunkt) 
  //while (1);
  delay(1000);
}
