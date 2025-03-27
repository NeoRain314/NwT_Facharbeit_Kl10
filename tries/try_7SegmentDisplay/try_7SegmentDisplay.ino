/* C++ Code
 *  there is going to be written "11 30" on the 7SegmentDisplay 
 */

#include <TM1637Display.h>
#include <Arduino.h>

// Module connection pins (Digital Pins)
#define CLK 2
#define DIO 3

TM1637Display display(CLK, DIO);

#define TEST_DELAY   2000

void setup()
{
    display.setBrightness(0x0f); // Helligkeit auf 15??? 
}

void loop() {
  int hour = 9; // da kann man dan später die passende Variable einfügen 
  int minute = 7; 
 
  uint8_t data[] = { 255, 255, 255, 255 }; // array wert zw 0 und 255 (--> unit8_data) jeder einzelne wert auf 255 (0xff)
  uint8_t blank[] = { 0x00, 0x00, 0x00, 0x00 }; // -"- Wert auf 0 (0x00)

  display.setSegments(data);
  delay(TEST_DELAY);
    display.showNumberDecEx(hour * 100 + minute, 0b01000000);  // hour*100+minute (--> vierstellige Zahl (11*100*30 =1130)) ;0b01000000 Binärzahl (--> aktiviert den Doppelpunkt) 
  while (1);

}
