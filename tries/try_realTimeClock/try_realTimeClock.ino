#include <Adafruit_BusIO_Register.h>
#include <Adafruit_GenericDevice.h>
#include <Adafruit_I2CDevice.h>
#include <Adafruit_I2CRegister.h>
#include <Adafruit_SPIDevice.h>

#include <RTClib.h>
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
}

void loop() {
    DateTime now = rtc.now();

    Serial.print(now.year(), DEC);
    Serial.print('/');
    Serial.print(now.month(), DEC);
    Serial.print('/');
    Serial.print(now.day(), DEC);
    Serial.print(" ");
    Serial.print(now.hour(), DEC);
    Serial.print(':');
    Serial.print(now.minute(), DEC);
    Serial.print(':');
    Serial.println(now.second(), DEC);

    delay(1000);
}

