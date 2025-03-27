
//              CS  A0/DC  RESET  SDA  SCK  LED    VCC     GND    //
// Arduino Uno  A5   A3     A4    11   13   A0   5V/3.3V   GND    //

#include <LCDWIKI_GUI.h> //Core graphics library
#include <LCDWIKI_SPI.h> //Hardware-specific library

#define arr_length(a) (sizeof(a) / sizeof(a[0]))

//paramters define
#define MODEL ST7735S128
#define CS   A5
#define CD   A3
#define RST  A4
#define LED  A0   //if you don't need to control the LED pin,you should set it to -1 and set it to 3.3V

//the definiens of hardware spi mode as follow:
//if the IC model is known or the modules is unreadable,you can use this constructed function
LCDWIKI_SPI mylcd(MODEL,CS,CD,RST,LED); //model,cs,dc,reset,led

#define  BLACK   0x0000
#define BLUE    0x001F
#define RED     0xF800
#define GREEN   0x07E0
#define CYAN    0x07FF
#define MAGENTA 0xF81F
#define YELLOW  0xFFE0
#define WHITE   0xFFFF

void setup() {
  Serial.begin(9600);
  mylcd.Init_LCD();
  mylcd.Fill_Screen(BLACK);

  Draw_Cute_Face();
}

void loop(){
  
}

void Draw_Cute_Face() {
  int centerX = 64;
  int centerY = 64;
  int noseSize = 10;
  int eyeSize = 10;
  
  mylcd.Set_Draw_color(WHITE);
  //mylcd.Draw_Circle(64, 64, 50);

  //face
  mylcd.Draw_Circle(centerX-20, centerY-10, 10);
  mylcd.Draw_Circle(centerX+20, centerY-10, 10);
  mylcd.Set_Draw_color(BLACK);
  mylcd.Fill_Rectangle(0, 53, mylcd.Get_Display_Width(),mylcd.Get_Display_Height());

  //nose
  mylcd.Set_Draw_color(WHITE);
  mylcd.Draw_Line(centerX, centerY, centerX - noseSize / 2, centerY + noseSize);
  mylcd.Draw_Line(centerX, centerY, centerX + noseSize / 2, centerY + noseSize);
  mylcd.Draw_Line(centerX - noseSize / 2, centerY + noseSize, centerX + noseSize / 2, centerY + noseSize);

  //whiskers
  mylcd.Draw_Line(0,0,0,0);
}



