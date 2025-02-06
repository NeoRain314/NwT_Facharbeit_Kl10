#include <SPI.h>
#include <SD.h>
#include <x.h>
#include <Wire.h>

bool century = false;
bool h12Flag;
bool pmFlag;

DS3231 clock;

void setup() {
  for (int i = 0; i < 1000; i++) {
      delay(1000);
      Textdatei.print(i);
      Textdatei.print(" : ");
      Textdatei.print(clock.getYear());
      Textdatei.print("-");
      Textdatei.print(clock.getMonth(century));
      Textdatei.print("-");
      Textdatei.print(clock.getDate());
      Textdatei.print(":");
      Textdatei.print(clock.getHour(h12Flag, pmFlag));
      Textdatei.print("-");
      Textdatei.print(clock.getMinute());
      Textdatei.print("-");
      Textdatei.print(clock.getSecond(), DEC);
      Textdatei.print(";");
      Textdatei.println(clock.getTemperature(), 2);
      Textdatei.close();  // Anschliessend wird die Textdatei wieder geschlossen...
    }
}

void loop()
{

}
