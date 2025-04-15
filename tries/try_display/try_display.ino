// my notes // --------------------------------------------------------------------------------------------
// Taster: Pin 3
// --> taster wechselt eingestellte Menü durch und updatet dann display


// notes from the original code // ------------------------------------------------------------------------
// IMPORTANT: LCDWIKI_SPI LIBRARY MUST BE SPECIFICALLY
// CONFIGURED FOR EITHER THE TFT SHIELD OR THE BREAKOUT BOARD.

//This program is a demo of displaying string

//when using the BREAKOUT BOARD only and using these hardware spi lines to the LCD,
//the SDA pin and SCK pin is defined by the system and can't be modified.
//if you don't need to control the LED pin,you can set it to 3.3V and set the pin definition to -1.
//other pins can be defined by youself,for example
//pin usage as follow:
//             CS  A0/DC  RESET  SDA  SCK  LED    VCC     GND    
//Arduino Uno  A5   A3     A4    11   13   A0   5V/3.3V   GND

//Remember to set the pins to suit your display module!
/********************************************************************************
* @attention
*
* THE PRESENT FIRMWARE WHICH IS FOR GUIDANCE ONLY AIMS AT PROVIDING CUSTOMERS
* WITH CODING INFORMATION REGARDING THEIR PRODUCTS IN ORDER FOR THEM TO SAVE
* TIME. AS A RESULT, QD electronic SHALL NOT BE HELD LIABLE FOR ANY
* DIRECT, INDIRECT OR CONSEQUENTIAL DAMAGES WITH RESPECT TO ANY CLAIMS ARISING
* FROM THE CONTENT OF SUCH FIRMWARE AND/OR THE USE MADE BY CUSTOMERS OF THE 
* CODING INFORMATION CONTAINED HEREIN IN CONNECTION WITH THEIR PRODUCTS.
**********************************************************************************/
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

#define BLACK   0x0000
#define BLUE    0x001F
#define RED     0xF800
#define GREEN   0x07E0
#define CYAN    0x07FF
#define MAGENTA 0xF81F
#define YELLOW  0xFFE0
#define WHITE   0xFFFF

char* menues[] = {"Alarm", "Timer", "Study", "LEDs", "Settings"};
int selectet_menue = 0;

#define BUTTON_PIN 3
int button_stat = 0;

void setup() {
  Serial.begin(9600);
  
  mylcd.Init_LCD();
  mylcd.Fill_Screen(BLACK);

  pinMode(BUTTON_PIN, INPUT_PULLUP);
  attachInterrupt(digitalPinToInterrupt(BUTTON_PIN), interrupt, FALLING);

  updateDisplay();
}

void loop(){
  //mylcd.Print_String("String"], /x-Koordinate/, /y-Koordinate/);
  //mylcd.Print_Number_Float(/Zahl/, /anz Nachkommastellen/, /Koordinate/, /Koordinate/, /Symbol vor Nachkommastelle/, /?/, /?/);
  //mylcd.Print_Number_Float(3.1415926535, 5, 10, 10, '.', 0, ' ');

  
  
  /*
  mylcd.Fill_Screen(0x0000);
  mylcd.Set_Text_colour(MAGENTA);
  mylcd.Set_Text_Back_colour(BLACK);
  mylcd.Set_Text_Size(1);
  mylcd.Print_String("Hello World!", 0, 0);
  mylcd.Print_Number_Float(3.1415926535, 2, 0, 8, '.', 0, ' ');
  mylcd.Print_Number_Int(0xDEADBEF, 0, 16, 0, ' ',16);

  mylcd.Set_Text_colour(GREEN);
  mylcd.Set_Text_Size(2);
  mylcd.Print_String("Hello", 0, 28);
  mylcd.Print_Number_Float(01234.56789, 2, 0, 44, '.', 0, ' ');  
  mylcd.Print_Number_Int(0xDEADBEF, 0, 60, 0, ' ',16);

  mylcd.Set_Text_colour(BLUE);
  mylcd.Set_Text_Size(3);
  mylcd.Print_String("Hello", 0, 80);
  mylcd.Print_Number_Float(01234.56789, 2, 0, 104, '.', 0, ' ');  
  mylcd.Print_Number_Int(0xDEADBEF, 0, 128, 0, ' ',16);
  */
}

void interrupt(){
  changeSelectetMenu();
}

void changeSelectetMenu() {
  Serial.println(selectet_menue);
  if(digitalRead(BUTTON_PIN) == 0 && button_stat == 0){
    button_stat = 1;
  }
  if(digitalRead(BUTTON_PIN) == 1 && button_stat == 1){
    button_stat = 0;
    selectet_menue ++;
    if(selectet_menue > arr_length(menues)-1) selectet_menue = 0;
  }
  delay(10);
  updateDisplay();

}

void updateDisplay(){
  mylcd.Set_Text_Mode(0);

  mylcd.Fill_Screen(0x0000);
  mylcd.Set_Text_colour(WHITE);
  mylcd.Set_Text_Back_colour(BLACK);
  mylcd.Set_Text_Size(2);

  mylcd.Print_String("   Menu", 3, 3);
  //mylcd.Draw_Line(0, 0, mylcd.Get_Display_Width()-1 ,0);

  mylcd.Set_Draw_color(WHITE);
  mylcd.Draw_Line(0, 22, mylcd.Get_Display_Width()-1 , 22);
  
  for(int i=0; i<arr_length(menues); i++){
    String print_message = menues[i];
    if(selectet_menue == i) print_message = "> " + print_message;
    mylcd.Print_String(print_message, 10, 29 + i*20);
  }
}


