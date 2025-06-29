#include <Adafruit_NeoPixel.h>

#ifdef __AVR__
#include <avr/power.h>
#endif
#define PIN 9 
#define NUMPIXELS 8
Adafruit_NeoPixel pixels = Adafruit_NeoPixel (NUMPIXELS, PIN, NEO_GBR + NEO_KHZ800);
int pause = 200; 

//const char* led_colors[] = {"red", "orange", "yellow", "green", "lightgreen", "blue", "lightblue", "purple", "pink", "rainbow"};

#define SELECT_BUTTON_PIN 2 
#define OK_BUTTON_PIN 3
int select_button_interrupt = 0;
int ok_button_interrupt = 0;


#define NEO_RED 0, 0, 255
#define NEO_ORANGE 0, 99, 255  
#define NEO_YELLOW 2, 150, 247
#define NEO_GREEN  3, 138, 7 
#define NEO_LIGHTGREEN 3, 252,61
#define NEO_BLUE  255, 0, 0
#define NEO_LIGHTBLUE  252, 219, 3
#define NEO_PURPLE  252, 3, 144 
#define NEO_PINK  255, 0, 255

void setup() {
  pixels.begin(); // Initialisierung der WS2812LEDs
}

void loop() {
  neoClassic(NEO_RED);
  delay(1000);
  neoClassic(NEO_ORANGE);
  delay(1000);
  neoClassic(NEO_YELLOW);
  delay(1000);
  neoClassic(NEO_GREEN);
  delay(1000);
  neoClassic(NEO_LIGHTGREEN);
  delay(1000);
  neoClassic(NEO_BLUE);
  delay(1000);
  neoClassic(NEO_LIGHTBLUE);
  delay(1000);
  neoClassic(NEO_PURPLE);
  delay(1000);
  neoClassic(NEO_PINK);
  delay(1000);

  neoFading(NEO_RED, 2);

  neoRainbow(10);

  neoRainbowAll(10);
}

void neoClassic(int g, int b, int r){ // einzelne farben normal 
 for(int i = 0; i < NUMPIXELS; i++){
  pixels.setPixelColor(i, pixels.Color(g, b, r));
  pixels.show();
 }
}

 void neoFading(int g, int b, int r, int speed){ // ausgewählte Farben (hier rot) pulsiert
  for (int brightness = 20; brightness <= 255; brightness += speed) {
    neoClassic (g * brightness / 255, b * brightness / 255, r * brightness / 255);
    delay(10);
  }
  for (int brightness = 255; brightness >= 20; brightness -= speed) {
    neoClassic (g * brightness / 255, b * brightness / 255, r * brightness / 255);
    delay(10);
  }
 }

void neoRainbow (int wait){ // die LEDs bewegen sich einzeln durch den Regenbogen
   for (int j = 0; j < 256; j++) {  // 256 verschiedene Farbwerte für sanften Übergang
    for (int i = 0; i < NUMPIXELS; i++) {
      int hue = (i * 256 / NUMPIXELS) + j;
      pixels.setPixelColor(i, Wheel(hue & 255)); 
    }
    pixels.show();
    delay(wait);
  }
}


void neoRainbowAll(int wait) { // 8 LEDs zeigen immer die gleiche Farbe die gleichzeitig durch den Regenbogen geht
  for (int j = 0; j < 256; j++) {  // Farbverlauf durch 256 Farbstufen
    uint32_t color = Wheel(j & 255); // Farbe für alle LEDs berechnen
    
    for (int i = 0; i < NUMPIXELS; i++) {
      pixels.setPixelColor(i, color); // Setze alle LEDs auf die gleiche Farbe
    }

    pixels.show();
    delay(wait);
  }
}

uint32_t Wheel(byte WheelPos) { // wheel()-Funktion sorgt für sanften Farbübergang
  WheelPos = 255 - WheelPos;
  if (WheelPos < 85) {
    return pixels.Color(255 - WheelPos * 3, 0, WheelPos * 3);
  }
  if (WheelPos < 170) {
    WheelPos -= 85;
    return pixels.Color(0, WheelPos * 3, 255 - WheelPos * 3);
  }
  WheelPos -= 170;
  return pixels.Color(WheelPos * 3, 255 - WheelPos * 3, 0);
}
