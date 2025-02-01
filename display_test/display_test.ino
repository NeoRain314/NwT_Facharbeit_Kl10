#include <TouchScreen.h>

#include <Adafruit_TFTLCD.h>

#include <Adafruit_GFX.h>

#define BLACK   0x0000
#define BLUE    0x001F
#define RED     0xF800
#define GREEN   0x07E0
#define CYAN    0x07FF
#define MAGENTA 0xF81F
#define YELLOW  0xFFE0
#define WHITE   0xFFFF

// Pinbelegung für den Arduino Mega
#define LCD_CS   10
#define LCD_CD   9
#define LCD_WR   8
#define LCD_RD   7
#define LCD_RESET 6

// Touchscreen-Pins
#define YP A1
#define XM A2
#define YM 7
#define XP 6

// Touchscreen-Kalibrierung
#define TS_MINX 150
#define TS_MINY 120
#define TS_MAXX 920
#define TS_MAXY 940

#define MINPRESSURE 10
#define MAXPRESSURE 1000

Adafruit_TFTLCD tft(LCD_CS, LCD_CD, LCD_WR, LCD_RD, LCD_RESET);
TouchScreen ts = TouchScreen(XP, YP, XM, YM, 300);

void setup() {
  Serial.begin(9600);
  Serial.println("TFT Display Test auf Arduino Mega!");

  tft.reset();
  uint16_t identifier = tft.readID();
  
  if (identifier == 0x9325 || identifier == 0x9341) {
    tft.begin(identifier);
  } else {
    Serial.println("Unbekannter LCD-Treiberchip!");
    while (1);
  }

  tft.setRotation(1);  // Display-Rotation einstellen
  tft.fillScreen(BLACK);
  tft.setTextColor(WHITE);
  tft.setTextSize(2);
  tft.setCursor(30, 50);
  tft.print("TFT TEST OK!");
  tft.setCursor(20, 100);
  tft.setTextColor(YELLOW);
  tft.print("Touchscreen testen...");
}

void loop() {
  TSPoint p = ts.getPoint();
  
  if (p.z > MINPRESSURE && p.z < MAXPRESSURE) {
    p.x = map(p.x, TS_MINX, TS_MAXX, 0, tft.width());
    p.y = map(p.y, TS_MINY, TS_MAXY, 0, tft.height());

    Serial.print("Touch X: "); Serial.print(p.x);
    Serial.print("  Touch Y: "); Serial.println(p.y);

    tft.fillCircle(p.x, p.y, 2, WHITE);
  }
}



