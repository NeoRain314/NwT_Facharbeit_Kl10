






/***************************************************************************************

g_... ---> globale Var
p --> pointer

Benennung:
  class: CamelCase
  functions: camelCase
  variables: snake_case
  defines: KEINE_AHNUNG_SO_HALT

****************************************************************************************/


// <<< Inizalizing <<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<< Initalizing <<//
#define arr_length(a) (sizeof(a) / sizeof(a[0]))

// ... Pin Defines & vars .................................................................................................... Pin Defines & vars ... //
#define SELECT_BUTTON_PIN 2
volatile bool select_button_interrupt = false;

#define OK_BUTTON_PIN 3
volatile bool ok_button_interrupt = false;

#define PIEZO_PIN 8



// RTC Variables
int rtc_hour = 0;
int rtc_minute = 0;

// ... libraries ...................................................................................................................... libraries ... //
#include <Wire.h>
#include <Arduino.h>

//LCD Display
#include <LCDWIKI_SPI.h>
#include <LCDWIKI_GUI.h>

//Real Time Clock (RTC)
#include <Adafruit_BusIO_Register.h>
#include <Adafruit_GenericDevice.h>
#include <Adafruit_I2CDevice.h>
#include <Adafruit_I2CRegister.h>
#include <Adafruit_SPIDevice.h>

#include <RTClib.h>

//7 Segment Display
#include <TM1637Display.h>

// ... LCD Display .................................................................................................................. LCD Display ... //
// --> LCD_ / lcd_ //

// Pins:              CS  A0/DC  RESET  SDA  SCK  LED    VCC     GND    //
// Arduino Uno:       A5   A3     A4    11   13   A0   5V/3.3V   GND    //
// Arduino Mega2560:  A5   A3     A4    51   52   A0   5V/3.3V   GND    //

#define LCD_MODEL ST7735S128
#define LCD_CS   A5
#define LCD_CD   A3
#define LCD_RST  A4
#define LCD_LED  A0

LCDWIKI_SPI mylcd(LCD_MODEL,LCD_CS,LCD_CD,LCD_RST,LCD_LED); //model,cs,dc,reset,led

//Color Defines
#define BLACK 0x0000
#define WHITE 0xFFFF
#define GREY  0x8410

#define LCD_BG_COLOR BLACK //-> to change BG color for LCD later
#define LCD_TEXT_COLOR WHITE //-> to change Text color for LCD later

// ... Real Time Clock .......................................................................................................... Real Time Clock ... //
RTC_DS3231 rtc;

// ... 7 Segment Display ...................................................................................................... 7 Segment Display ... //
#define CLK 5
#define DIO 6

TM1637Display display(CLK, DIO);

char* intToString(int num, bool leading_zero);

// ... Menu Structure ............................................................................................................ Menu Structure ... //
class AbstractMenu;
class TimerMenu;
class MyAlarm1Menu;
class StudyMenu;
AbstractMenu* g_pPreviousMenu = 0;

// ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~ Abstract Menu ~~~ //

class AbstractMenu {
  public: // public --> im folgenden funktionen, die von außen aufgerufen werden können
  virtual void draw(){  //virtual --> abgeleitete Klassen können funktion überschreiben
    Serial.println("Ich bin ein Abstract Menu!");
  }
  
  virtual void okPressed() {
    Serial.println("ok not implemented");
  }

  virtual void selectPressed() {
    Serial.println("select not implemented");
  }

  void beforeMenuSwitch() {
    g_pPreviousMenu = this;
  }

  void printMenuBar(char* menu_name) { //helper function to draw top of menu
    mylcd.Fill_Screen(BLACK);

    mylcd.Set_Text_Mode(0);
    mylcd.Set_Text_colour(LCD_TEXT_COLOR);
    mylcd.Set_Text_Back_colour(LCD_BG_COLOR);
    mylcd.Set_Text_Size(2);
    mylcd.Print_String(menu_name, 3, 3);

    mylcd.Set_Draw_color(LCD_TEXT_COLOR);
    mylcd.Draw_Line(0, 22, mylcd.Get_Display_Width()-1 , 22); //draw line under the name
  }

  void printMenuEntries(int index, int menu_length, char* menu_entries[]) { //helper function to draw menu
    mylcd.Set_Text_Mode(0);
    mylcd.Set_Text_colour(LCD_TEXT_COLOR);
    mylcd.Set_Text_Back_colour(LCD_BG_COLOR);
    mylcd.Set_Text_Size(2);

    for (int i=0; i<menu_length; i++){
      String print_message = menu_entries[i];
      if(i == index) print_message = "> " + print_message;
      mylcd.Print_String(print_message, 10, 29 + i*20);
    }
  }

  

};

// ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~ Menu Variables ~~~ //

AbstractMenu* g_pActiveMenu = 0;
//main menus 
AbstractMenu* g_pMainMenu = 0;
AbstractMenu* g_pAlarmMenu = 0;
TimerMenu* g_pTimerMenu = 0;
StudyMenu* g_pStudyMenu = 0;
AbstractMenu* g_pLedMenu = 0;
AbstractMenu* g_pModulMenu = 0;

//setting menus
MyAlarm1Menu* g_pMyAlarm1Menu = 0;
AbstractMenu* g_pSetTimeMenu = 0;




// ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~ MyAlarm 1 Menu ~~~ //
const char* myalarm1_menu_entries[] = {"off",  "00:00", "back"};
int alarm1_time[] = {0, 0};

class MyAlarm1Menu : public AbstractMenu {
  int selected_index = 0;
  
  public:

  bool alarm1_stat = false;

  virtual void draw(){
    char buffer[100];
    sprintf(buffer, "%02d:%02d ", alarm1_time[0], alarm1_time[1]);
    myalarm1_menu_entries[1] = buffer;

    printMenuBar("Alarm 1");
    printMenuEntries(selected_index, 3, myalarm1_menu_entries); // index, menu_length, menu_entries[]y
  }

  virtual void selectPressed() {
    selected_index = (selected_index + 1) % 3; //damit i nie größer 2
  }

  virtual void okPressed(){
    if (selected_index == 0) { //switch between on and off
      if(alarm1_stat){
        alarm1_stat = false;
        myalarm1_menu_entries[0] = "off";
      }else{
        alarm1_stat = true;
        myalarm1_menu_entries[0] = "on";
      }
    }
    if (selected_index == 1) {
      beforeMenuSwitch();
      g_pActiveMenu = g_pSetTimeMenu;
    }
    if (selected_index == 2) {
      beforeMenuSwitch();
      g_pActiveMenu = g_pAlarmMenu;
    }
    
  }
};

// ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~ Alarm Menu ~~~ //
const char* alarm_menu_entries[] = {"Alarm 1", "Alarm 2", "Sound", "back"};

class AlarmMenu : public AbstractMenu {
  int selected_index = 0;
  
  public:

  virtual void draw(){
    printMenuBar("Alarm Menu");
    printMenuEntries(selected_index, 4, alarm_menu_entries); // index, menu_length, menu_entries[]
  }

  virtual void selectPressed() {
    selected_index = (selected_index + 1) % 4; //damit i nie größer 2
  }

  virtual void okPressed(){
    beforeMenuSwitch();
    if (selected_index == 0) g_pActiveMenu = g_pMyAlarm1Menu;
    if (selected_index == 1) g_pActiveMenu = g_pAlarmMenu;
    if (selected_index == 2) g_pActiveMenu = g_pAlarmMenu;
    if (selected_index == 3) g_pActiveMenu = g_pMainMenu;
  }
};

// ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~ Timer Menu ~~~ //
const char* timer_menu_entries[] = {"new Timer", "Sound", "back"};
int timer_time[] = {0, 0};


class TimerMenu : public AbstractMenu {
  int selected_index = 0;

  public:

  bool timer_stat = false;
  unsigned long timer_start_mill = 0;
  unsigned long timer_time_mill = 0;

  virtual void draw(){
    if(timer_stat) timer_menu_entries[0] = "stop Timer"; else timer_menu_entries[0] = "new Timer";
    printMenuBar("Timer Menu");
    printMenuEntries(selected_index, 3, timer_menu_entries); // index, menu_length, menu_entries[]
  }

  virtual void selectPressed() {
    selected_index = (selected_index + 1) % 3; //damit i nie größer 2
  }

  virtual void okPressed(){
    beforeMenuSwitch();
    if (selected_index == 0) {
      if(timer_stat){
        timer_time[0] = 0;
        timer_time[1] = 0;
        timer_stat = false;
      }else {
        beforeMenuSwitch();
        g_pActiveMenu = g_pSetTimeMenu;
      }

      
    }
    if (selected_index == 1) g_pActiveMenu = g_pTimerMenu;
    if (selected_index == 2) g_pActiveMenu = g_pMainMenu;
  }
};

// ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~ Study Menu ~~~ //
const char* study_menu_entries[] = {"25/5 min", "Rept: 1 ", "start", "back"};
const char* study_menu_modes[] = {"25/5 min", "50/10", "90/20 min"};
int studytimer_time[] = {0, 0};

class StudyMenu : public AbstractMenu {
  int selected_index = 0;
  
  public:
  bool study_stat = false;
  int study_mode = 0;
  int study_repetitions = 1;
  unsigned long studytimer_start_mill = 0;
  unsigned long studytimer_time_mill = 0;

  bool study_pause = false; //pause or fucus
  int study_curr_repetition = 0; //current repetition

  virtual void draw(){
    if(study_stat){
      printMenuBar("Focusing");
    }else {
      printMenuBar("Study Menu");
      printMenuEntries(selected_index, 4, study_menu_entries); // index, menu_length, menu_entries[]
    }
    
  }

  virtual void selectPressed() {
    selected_index = (selected_index + 1) % 4; //damit i nie größer 2
  }

  virtual void okPressed(){
    beforeMenuSwitch();
    if(study_stat == true) {
      //interrupt study mode
      study_stat = false;
    }
    
    if (selected_index == 0){
      study_mode = (study_mode + 1) % 3; 
      study_menu_entries[0] = study_menu_modes[study_mode];
    }
    if (selected_index == 1){
      study_repetitions += 1;
      if(study_repetitions>5) study_repetitions = 1;

      sprintf(study_menu_entries[1], "Rept: %d", study_repetitions);
    }
    if (selected_index == 2){
      study_stat = true;
    };
    if (selected_index == 3) g_pActiveMenu = g_pMainMenu;
  }
};

// ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~ LED Menu ~~~ //
const char* led_menu_entries[] = {"on", "red", "back"};
const char* led_colors[] = {"red", "orange", "yellow", "green", "lightgreen", "blue", "lightblue", "purple", "pink", "rainbow"};

class LedMenu : public AbstractMenu {
  int selected_index = 0;
  bool led_stat = true;
  int led_mode = 0;
  
  public:

  virtual void draw(){
    printMenuBar("LED Menu");
    printMenuEntries(selected_index, 3, led_menu_entries); // index, menu_length, menu_entries[]
  }

  virtual void selectPressed() {
    selected_index = (selected_index + 1) % 3; //damit i nie größer 2
  }

  virtual void okPressed(){
    beforeMenuSwitch();
    if (selected_index == 0) { //switch between on and off
      if(led_stat){
        led_stat = false;
        led_menu_entries[0] = "off";
      }else{
        led_stat = true;
        led_menu_entries[0] = "on";
      }
    }
    if (selected_index == 1) {
      led_mode ++;
      if(led_mode > 9) led_mode = 0;
      led_menu_entries[1] = led_colors[led_mode];
      Serial.print(led_mode);
      Serial.print(" - ");
      Serial.println(led_menu_entries[led_mode]);
    }
    if (selected_index == 2) g_pActiveMenu = g_pMainMenu;
  }
};

// ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~ Modul Menu ~~~ //
const char* modul_menu_entries[] = {"Punkt 1", "Punkt 2", "back"};

class ModulMenu : public AbstractMenu {
  int selected_index = 0;
  
  public:

  virtual void draw(){
    printMenuBar("Modul Menu");
    printMenuEntries(selected_index, 3, modul_menu_entries); // index, menu_length, menu_entries[]
  }

  virtual void selectPressed() {
    selected_index = (selected_index + 1) % 3; //damit i nie größer 2
  }

  virtual void okPressed(){
    beforeMenuSwitch();
    if (selected_index == 0) g_pActiveMenu = g_pModulMenu;
    if (selected_index == 1) g_pActiveMenu = g_pModulMenu;
    if (selected_index == 2) g_pActiveMenu = g_pMainMenu;
  }
};


// ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~ set time Menu ~~~ //
int set_time_menu_output[] = {0, 0};

class SetTimeMenu : public AbstractMenu {
  int index = 0;
  int mode = 0; //0->alarm ; 1->timer
  
  public:

  virtual void draw(){
    mylcd.Fill_Screen(BLACK);

    mylcd.Set_Text_Mode(0);
    mylcd.Set_Text_Back_colour(LCD_BG_COLOR);
    mylcd.Set_Text_Size(3);

    mylcd.Set_Text_colour(GREY); //print the selected position white, the other /the rest grey
    mylcd.Print_String(":", mylcd.Get_Display_Width()/2 - 5, mylcd.Get_Display_Height()/2 - 10);
    for(int i = 0; i < 2; i++) {
      mylcd.Set_Text_colour(GREY);
      if(index == i) mylcd.Set_Text_colour(LCD_TEXT_COLOR);
      mylcd.Print_String(intToString(set_time_menu_output[i], true), mylcd.Get_Display_Width()/2 - 40 + i*50, mylcd.Get_Display_Height()/2 - 10);
    }
  }


  virtual void selectPressed() {
    if (g_pPreviousMenu == g_pMyAlarm1Menu){ //alarm mode
      set_time_menu_output[index] += 1;
      if (index == 0 && set_time_menu_output[index] > 23) set_time_menu_output[index] = 0;
      if (index == 1 && set_time_menu_output[index] > 59) set_time_menu_output[index] = 0;
    }

    if (g_pPreviousMenu == g_pTimerMenu){ //timer mode
      set_time_menu_output[index] += 1;
      if (index == 0 && set_time_menu_output[index] > 59) set_time_menu_output[index] = 0;
      if (index == 1 && set_time_menu_output[index] > 59) set_time_menu_output[index] = 0;
    }
  }

  virtual void okPressed(){
    if(index < 1){
      index++;
    }else {
      if (g_pPreviousMenu == g_pMyAlarm1Menu){
        alarm1_time[0] = set_time_menu_output[0];
        alarm1_time[1] = set_time_menu_output[1];
      }

      if (g_pPreviousMenu == g_pTimerMenu) {
        timer_time[0] = set_time_menu_output[0];
        timer_time[1] = set_time_menu_output[1];

        Serial.print(set_time_menu_output[0]);
        Serial.print(":");
        Serial.println(set_time_menu_output[1]);
        
        if(timer_time[0] != 0 || timer_time[1] != 0) { //Timer startet
          g_pTimerMenu->timer_stat = true;
          g_pTimerMenu->timer_time_mill = timer_time[0]*60000 + timer_time[1]*1000;
          g_pTimerMenu->timer_start_mill = millis();
        }

        //Serial.println(g_pTimerMenu->timer_stat);
      }

      //reset (vieleicht iw noch besser, so dass timer timer bleibt, wecker wecker bleibt und es sich nicht jedes mal 0);
      index = 0;
      set_time_menu_output[0] = 0;
      set_time_menu_output[1] = 0;

      g_pActiveMenu = g_pPreviousMenu;
      beforeMenuSwitch();
    }
  }
};



// ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~ Main Menu ~~~ //
const char* main_menu_entries[] = {"Alarm", "Timer", "Study", "LED", "Modul"};

class MainMenu : public AbstractMenu {
  int selected_index = 0;

  public:

  MainMenu(){ //wird aufgerufen wenn new MainMenu() aufgerufen wird
    //...
  }

  virtual void draw(){
    /*for (int i=0; i<3; i++){
      if (i == selected_index) Serial.print("* ");
      Serial.println(main_menu_entries[i]);
    }
    Serial.println("");*/
    printMenuBar("Main Menu");
    printMenuEntries(selected_index, 5, main_menu_entries); // index, menu_length, menu_entries[]
  }

  virtual void selectPressed() {
    selected_index = (selected_index + 1) % 5; //damit i nie größer 2
  }

  virtual void okPressed(){
    beforeMenuSwitch();
    if (selected_index == 0) g_pActiveMenu = g_pAlarmMenu;
    if (selected_index == 1) g_pActiveMenu = g_pTimerMenu;
    if (selected_index == 2) g_pActiveMenu = g_pStudyMenu;
    if (selected_index == 3) g_pActiveMenu = g_pLedMenu;
    if (selected_index == 4) g_pActiveMenu = g_pModulMenu;
  }
};

// <<< setup <<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<< setup <<//
void setup() {
  Serial.begin(9600); //Serial Monitor
  // ... Pin Modes ...................................................................................................................... Pin Modes ... //
  pinMode(SELECT_BUTTON_PIN, INPUT_PULLUP);
  attachInterrupt(digitalPinToInterrupt(SELECT_BUTTON_PIN), selectButtonISR, RISING); //Rising 0 -> 1
  pinMode(OK_BUTTON_PIN, INPUT_PULLUP);
  attachInterrupt(digitalPinToInterrupt(OK_BUTTON_PIN), okButtonISR, RISING); //Rising 0 -> 1
  pinMode(PIEZO_PIN, OUTPUT);

  //short test for Piezo
  tone(PIEZO_PIN, 440);
  delay(1000);
  noTone(PIEZO_PIN);


  // ... Menu Structure ............................................................................................................ Menu Structure ... //
  g_pMainMenu = new MainMenu();
  g_pAlarmMenu = new AlarmMenu();;
  g_pTimerMenu = new TimerMenu();
  g_pStudyMenu = new StudyMenu();
  g_pLedMenu = new LedMenu();
  g_pModulMenu = new ModulMenu();

  g_pMyAlarm1Menu = new MyAlarm1Menu();
  g_pSetTimeMenu = new SetTimeMenu();

  g_pActiveMenu = g_pMainMenu; /*g_pSetTimeMenu;*/ //--> g_pActiveMenu legt hier start Menü fest

  // ... LCD Display .................................................................................................................. LCD Display ... //
  mylcd.Init_LCD();
  mylcd.Fill_Screen(LCD_BG_COLOR);
  updateLcdDisplay();

  // ... Real Time Clock .......................................................................................................... Real Time Clock ... //
  if (!rtc.begin()) {
    Serial.println("RTC nicht gefunden!");
    while (1);
  }

  // Falls die RTC nicht eingestellt ist, die aktuelle Zeit setzen:
  if (rtc.lostPower()) {
    Serial.println("RTC hat Strom verloren, Setze Zeit auf Kompilierzeit!");
    rtc.adjust(DateTime(F(__DATE__), F(__TIME__)));
  }

  // ... 7 Segment Display ........................................................................................................ Real Time Clock ... //
  display.setBrightness(0x0f);
  uint8_t data[] = { 255, 255, 255, 255 };
  display.setSegments(data);
}

// <<< Loop <<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<< loop <<//
void loop() {
  if(select_button_interrupt){
    selectButton();
    updateLcdDisplay();
    select_button_interrupt = false;
  }

  if(ok_button_interrupt){
    okButton();
    updateLcdDisplay();
    ok_button_interrupt = false;
  }

  clock();
  
  if(g_pTimerMenu->timer_stat){
    timer();
  } else if(g_pStudyMenu->study_stat) {
    studyMode();
  } else {
    update7Segment(rtc_hour, rtc_minute);
  }

  if(g_pMyAlarm1Menu->alarm1_stat) alarm1();
}

// <<< sub functions <<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<< sub functions <<//

// ... update Displays .......................................................................................................... update Displays ... //
void updateLcdDisplay() {
  g_pActiveMenu->draw();
}

void update7Segment(int first_number, int second_number) {
  display.showNumberDecEx(first_number * 100 + second_number, 0b01000000);  // hour*100+minute (--> vierstellige Zahl (11*100*30 =1130)) ;0b01000000 Binärzahl (--> aktiviert den Doppelpunkt) 
}

// ... clock  ............................................................................................................................. clock ... //
void clock() {
  DateTime now = rtc.now();

  rtc_hour = now.hour();
  rtc_minute = now.minute();
  /*Serial.print(intToString(rtc_hour, true));
  Serial.print(":");
  Serial.println(intToString(rtc_minute, true));*/
}

// ... Timer .......................................................................................................... Timer ... //
void timer() {
  if(millis() > g_pTimerMenu->timer_start_mill + g_pTimerMenu->timer_time_mill) {
    g_pTimerMenu->timer_stat = false;
    Serial.println("");
    Serial.println("-----------------------");
    Serial.println("Timer ended!");
    return;
  }

  unsigned long rest_mill = g_pTimerMenu->timer_start_mill + g_pTimerMenu->timer_time_mill - millis();
  int minutes = rest_mill/60000;
  int seconds = (rest_mill%60000) /1000;

  Serial.print("Timer: ");
  Serial.print(intToString(minutes, true));
  Serial.print(":");
  Serial.println(intToString(seconds, true));

  update7Segment(minutes, seconds);
}


// ... Alarms ............................................................................................................................ Alarms ... //
void alarm1() {
  if (alarm1_time[0] == rtc_hour && alarm1_time[1] == rtc_minute){
    tone(PIEZO_PIN, 400);
    delay(2000); // !! !! !! !! !! !! !! !! !! !! !! !! !! !! !! !! !! !! !! !! !! !! !! !! !! !! !! !! !! !! !! !! !! !! !! !! !! !! !! !! !! !! !! !! !! !! !! !! !! !! !! !! !! !!  Ersatz für Delay
    noTone(PIEZO_PIN);
    //sende funk signal zu Lichtanschaltknopf (wenn in Menü eingeschaltet) / ~ / ~ / ~ / ~ / ~ / ~ / ~ / ~ / ~ / ~ / ~ / ~ / ~ / ~ / ~ / ~ / ~ / ~ / ~ / ~ / ~ / ~ / ~ / ~ / ~ / ~ 
    g_pMyAlarm1Menu->alarm1_stat = false;
    updateLcdDisplay();
  }
}

// ... Study Mode .................................................................................................................... Study Mode ... //
void studyMode(){
  //Serial.println("Study Mode");
  const int focus_times[] = {25, 50, 90};
  const int pause_times[] = {5, 10, 20};

  //Serial.println( g_pStudyMenu->study_curr_repetition);

  if(millis() > g_pStudyMenu->studytimer_start_mill + g_pStudyMenu->studytimer_time_mill || g_pStudyMenu->study_curr_repetition == 0) {
    if(g_pStudyMenu->study_curr_repetition == g_pStudyMenu->study_repetitions){
      g_pStudyMenu->study_curr_repetition = 0;
      g_pStudyMenu->study_stat = false;
      return;
    }
    if(g_pStudyMenu->study_pause == false){
      //next pause
      g_pStudyMenu->study_pause = true;
      studytimer_time[0] = 0;
      studytimer_time[1] = pause_times[g_pStudyMenu->study_mode];

      g_pStudyMenu->studytimer_time_mill = studytimer_time[0]*60000 + studytimer_time[1]*1000;
      g_pStudyMenu->studytimer_start_mill = millis();

      g_pStudyMenu->study_curr_repetition++;
      // irgendwie geht er direkt am anfang in die pause !?!?!?!?!?!?!

    } else {
      //next focus
      g_pStudyMenu->study_pause = false;
      studytimer_time[0] = 0;
      studytimer_time[1] = focus_times[g_pStudyMenu->study_mode];

      g_pStudyMenu->studytimer_time_mill = studytimer_time[0]*60000 + studytimer_time[1]*1000;
      g_pStudyMenu->studytimer_start_mill = millis();

    }
  }

  unsigned long rest_mill = g_pStudyMenu->studytimer_start_mill + g_pStudyMenu->studytimer_time_mill - millis();
  int minutes = rest_mill/60000;
  int seconds = (rest_mill%60000) /1000;

  Serial.print("Study Timer: ");
  Serial.print(intToString(minutes, true));
  Serial.print(":");
  Serial.println(intToString(seconds, true));

  update7Segment(minutes, seconds);
}

// ... other .............................................................................................................................. other ... //
char* intToString(int num, bool leading_zero) {
  static char buffer[16]; // 2 Stellen + Nullterminierung

  if (leading_zero) sprintf(buffer, "%02d", num); 
  else sprintf(buffer, "%d", num);
  return buffer;
}

// ... Interrupts .................................................................................................................... Interrupts ... //
void okButtonISR() {
  ok_button_interrupt = true;
}

void selectButtonISR() {
  select_button_interrupt = true;
}

// ... Button Actions ............................................................................................................ Button Actions ... //
void okButton() {
  //Serial.println("ok");
  g_pActiveMenu->okPressed();
}

void selectButton() {
  //Serial.println("select");
  g_pActiveMenu->selectPressed();
}

// ... Wecker ............................................................................................................................ Wecker ... //


// ... Timer .............................................................................................................................. Timer ... //

