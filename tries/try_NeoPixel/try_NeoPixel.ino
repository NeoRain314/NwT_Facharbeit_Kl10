#include <Adafruit_NeoPixel.h>
#ifdef __AVR__
#include <avr/power.h>
#endif
#define PIN 9 
#define NUMPIXELS 8
Adafruit_NeoPixel pixels = Adafruit_NeoPixel (NUMPIXELS, PIN, NEO_GBR + NEO_KHZ800);
int pause = 200; 

void setup() {
  pixels.begin(); // Initialisierung der WS2812LEDs
}

void loop() {
  activateAllLEDsInDifferentColors();
}

void activateAllLEDsInDifferentColors(){
  pixels.setPixelColor (0, pixels.Color (20, 100, 20));
  pixels.show(); // Durchführung LED Ansteuerung
  delay (pause);
  pixels.setPixelColor (1, pixels.Color (255, 0, 0));
  pixels.show(); // Durchführung LED Ansteuerung
  delay (pause);
  pixels.setPixelColor (2, pixels.Color (0, 255, 0));
  pixels.show(); // Durchführung LED Ansteuerung
  delay (pause);
  pixels.setPixelColor (3, pixels.Color (0, 0, 255));
  pixels.show(); // Durchführung LED Ansteuerung
  delay (pause);
  pixels.setPixelColor (4, pixels.Color (0, 255, 255));
  pixels.show(); // Durchführung LED Ansteuerung
  delay (pause);
  pixels.setPixelColor (5, pixels.Color (255, 255, 0));
  pixels.show(); // Durchführung LED Ansteuerung
  delay (pause);
  pixels.setPixelColor (6, pixels.Color (255, 255, 255));
  pixels.show(); // Durchführung LED Ansteuerung
  delay (pause);
  pixels.setPixelColor (7, pixels.Color (100, 20, 20));
  pixels.show(); // Durchführung LED Ansteuerung
  delay (4000); // etas längere Pause es läuchten alle acht LEDs
  pixels.clear();
  pixels.show();
  delay (pause);
}
