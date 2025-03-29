#include <LCDWIKI_SPI.h> //Hardware-specific library
#include <LCDWIKI_GUI.h> //Core graphics library


//              CS  A0/DC  RESET  SDA  SCK  LED    VCC     GND    //
// Arduino Uno  A5   A3     A4    11   13   A0   5V/3.3V   GND    //

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

bool catBlink = true;

void setup() {
  Serial.begin(9600);
  mylcd.Init_LCD();
  mylcd.Fill_Screen(BLACK);

 
}

void loop(){
  catBlink = false;
  Draw_Cute_Face();
  delay(2000);
  catBlink = true;
  Draw_Cute_Face();
  delay(150);
}

void Draw_Cute_Face() {
  int centerX = 64;
  int centerY = 64;
  int noseSize = 7;
  int eyeSize = 10;
  int whiskerLength = 20;
  int earSize = 15;

  //face
  if(catBlink){
    mylcd.Set_Draw_color(BLACK);
    //mylcd.Fill_Rectangle(0, centerY - noseSize+5, mylcd.Get_Display_Width(), centerY - noseSize+5);
    mylcd.Fill_Rectangle(0, centerY - eyeSize, mylcd.Get_Display_Width(), centerY - eyeSize - 10);
    
    mylcd.Set_Draw_color(WHITE);
    mylcd.Draw_Line(centerX-30, centerY-12, centerX-10, centerY-12);
    mylcd.Draw_Line(centerX+30, centerY-12, centerX+10, centerY-12);
  }else{
    mylcd.Fill_Screen(BLACK);
    mylcd.Set_Draw_color(WHITE);
    
    mylcd.Draw_Circle(centerX-20, centerY-10, 10);
    mylcd.Draw_Circle(centerX+20, centerY-10, 10);

    mylcd.Draw_Circle(centerX-3, centerY + noseSize +5, 3);
    mylcd.Draw_Circle(centerX+3, centerY + noseSize +5, 3);
    
    mylcd.Set_Draw_color(BLACK);
    mylcd.Fill_Rectangle(0, centerY-10, mylcd.Get_Display_Width(),centerY + noseSize+5);
  
    //nose
    mylcd.Set_Draw_color(WHITE);
    //mylcd.Draw_Line(centerX, centerY, centerX - noseSize / 2, centerY + noseSize);
    //mylcd.Draw_Line(centerX, centerY, centerX + noseSize / 2, centerY + noseSize);
    //mylcd.Draw_Line(centerX - noseSize / 2, centerY + noseSize, centerX + noseSize / 2, centerY + noseSize);
    
    //mylcd.Draw_Line(centerX, centerY + noseSize, centerX - noseSize / 2, centerY);
    //mylcd.Draw_Line(centerX, centerY + noseSize, centerX + noseSize / 2, centerY);
    //mylcd.Draw_Line(centerX - noseSize / 2, centerY, centerX + noseSize / 2, centerY);
    //mylcd.Draw_Line(centerX, centerY + noseSize, centerX, centerY + noseSize + 5);
  
    mylcd.Draw_Line(centerX, centerY + noseSize, centerX - noseSize / 2, centerY);
    mylcd.Draw_Line(centerX, centerY + noseSize, centerX + noseSize / 2, centerY);
    mylcd.Draw_Line(centerX - noseSize / 2, centerY, centerX + noseSize / 2, centerY);
    mylcd.Draw_Line(centerX, centerY + noseSize, centerX, centerY + noseSize + 5);
    
  
    //whiskers
    mylcd.Draw_Line(centerX - 30, centerY + 3, centerX - 30 - whiskerLength, centerY);
    mylcd.Draw_Line(centerX - 30, centerY + 5, centerX - 30 - whiskerLength, centerY + 5);
    mylcd.Draw_Line(centerX - 30, centerY + 8, centerX - 30 - whiskerLength, centerY + 10);
    
    mylcd.Draw_Line(centerX + 30, centerY +3, centerX + 30 + whiskerLength, centerY);
    mylcd.Draw_Line(centerX + 30, centerY + 5, centerX + 30 + whiskerLength, centerY + 5);
    mylcd.Draw_Line(centerX + 30, centerY + 8, centerX + 30 + whiskerLength, centerY + 10);
  
    //ears
    mylcd.Draw_Line(centerX - 40, centerY - 30 - earSize, centerX - 15, centerY - 30);
    mylcd.Draw_Line(centerX - 40, centerY - 30 - earSize, centerX - 40, centerY - 30);
  
    mylcd.Draw_Line(centerX + 40, centerY - 30 - earSize, centerX + 15, centerY - 30);
    mylcd.Draw_Line(centerX + 40, centerY - 30 - earSize, centerX + 40, centerY - 30);
  }
}



