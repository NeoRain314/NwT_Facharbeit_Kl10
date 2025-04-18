

/* verwendete Pins:
2 select_button_pin 4 CLK
3 ok_button_pin     5 DIO
*/ 

// <<< library <<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<< library <<< //
#include <Wire.h>
// RealTimeClock:
#include <RTClib.h>
#include <Adafruit_BusIO_Register.h>
#include <Adafruit_GenericDevice.h>
#include <Adafruit_I2CDevice.h>
#include <Adafruit_I2CRegister.h>
#include <Adafruit_SPIDevice.h>

// 7SegmentDisplay:
#include <TM1637Display.h>



// <<< Inizalizing <<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<< Initalizing <<//

int ah; // var for hours (->alarmhour) (used to you select on what thime the alarm should go off)
int am; // var for minutes (->alarmminute)

int hour; // var for the hours being showed to know what time it is
int minute; // var for the minutes -"-

// 7SegmentDisplay:
#define SEG_CLK_PIN 4
#define SEG_DIO_PIN 5
TM1637Display display(SEG_CLK_PIN, SEG_DIO_PIN);

// RealTimeClock:
RTC_DS3231 rtc; 

// Buttons:
#define SELECT_BUTTON_PIN 2 
#define OK_BUTTON_PIN 3
int select_button_interrupt = 0;
int ok_button_interrupt = 0;

// Piezo:
#define PIEZO_PIN 8



// <<< setup <<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<< setup <<//
int index = 0;
int alarm_time[] = {15, 0};
bool alarm_stat = true;

void setup() {
  Serial.begin(9600);

  pinMode (SELECT_BUTTON_PIN, INPUT_PULLUP);
  attachInterrupt (digitalPinToInterrupt(SELECT_BUTTON_PIN), selectButtonISR, RISING );
  pinMode (OK_BUTTON_PIN, INPUT_PULLUP);
  attachInterrupt (digitalPinToInterrupt(OK_BUTTON_PIN), okButtonISR, RISING); //Rising 0 -> 1
  
  pinMode (PIEZO_PIN, OUTPUT);

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



// <<< Loop <<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<< loop <<//
void loop() {
  

  showTime();

 if (select_button_interrupt == true){  
  select_button_interrupt = false;
  setAlarm();
 }
 
 if (ok_button_interrupt == true){
  index = 1;
 }
 
 if (alarm_time[0] == hour && alarm_time[1] == minute && alarm_stat){
  tone(PIEZO_PIN, 400);
  delay(2000);
  noTone(PIEZO_PIN);
  alarm_stat = false;
 }
}
// <<< sub functions <<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<< sub functions <<//


void setAlarm() {
  Serial.print("Index: ");
  Serial.println(index);
  if (index == 0) {
    alarm_time[0]++;
    Serial.println(alarm_time[0]);
  } else if (index == 1) {
    alarm_time[1]++;
    Serial.println(alarm_time[1]);
  }
}

void showTime(){
  
  DateTime now = rtc.now();
  hour = now.hour();
  minute = now.minute();

  //Serial.print(now.hour());
    //Serial.print(":");
    //Serial.println(now.minute());
    

  hour = (hour + 1) % 24; // Sommerzeit (+1)
 display.showNumberDecEx(hour * 100 + minute, 0b01000000);


}
// ... Interrupts .................................................................................................................... Interrupts ... //
void okButtonISR() {
  ok_button_interrupt = true;
}

void selectButtonISR() {
  select_button_interrupt = true;
}

 