

/***************************************************************************************

g_... ---> globale Var
p --> pointer

Benennung:
  class: camelCase
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

// ... libraries ...................................................................................................................... libraries ... //
#include <LCDWIKI_SPI.h>
#include <LCDWIKI_GUI.h>

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

#define BLACK 0x0000
#define WHITE 0xFFFF


// ... Menu Structure ............................................................................................................ Menu Structure ... //

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

  void printMenuBar(char* menu_name) { //helper function to draw top of menu
    mylcd.Fill_Screen(0x0000);

    mylcd.Set_Text_Mode(0);
    mylcd.Set_Text_colour(WHITE);
    mylcd.Set_Text_Back_colour(BLACK);
    mylcd.Set_Text_Size(2);
    mylcd.Print_String(menu_name, 3, 3);

    mylcd.Set_Draw_color(WHITE);
    mylcd.Draw_Line(0, 22, mylcd.Get_Display_Width()-1 , 22); //draw line under the name
  }

  void printMenuEntries(int index, int menu_length, char* menu_entries[]) { //helper function to draw menu
    mylcd.Set_Text_Mode(0);
    mylcd.Set_Text_colour(WHITE);
    mylcd.Set_Text_Back_colour(BLACK);
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
AbstractMenu* g_pTimerMenu = 0;
AbstractMenu* g_pMainMenu = 0;


// ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~ Main Menu ~~~ //
const char* main_menu_entries[] = {"Punkt 1", "Punkt 2", "Punkt 3"};

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
    printMenuEntries(selected_index, 3, main_menu_entries); // index, menu_length, menu_entries[]
  }

  virtual void selectPressed() {
    selected_index = (selected_index + 1) % 3; //damit i nie größer 2
  }

  virtual void okPressed(){
    if (selected_index == 0) g_pActiveMenu = g_pMainMenu;
    if (selected_index == 1) g_pActiveMenu = g_pMainMenu;
    if (selected_index == 2) g_pActiveMenu = g_pMainMenu;
  }
};

// ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~ Timer Menu ~~~ //
class TimerMenu : public AbstractMenu {
  int selected_index = 0;
  public:

  virtual void draw(){
    Serial.println("Timer Menu!");
  }

  virtual void okPressed(){
    if (selected_index == 0) g_pActiveMenu = g_pMainMenu;
    if (selected_index == 1) g_pActiveMenu = g_pMainMenu;
    if (selected_index == 2) g_pActiveMenu = g_pMainMenu;
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

  // ... Menu Structure ............................................................................................................ Menu Structure ... //
  g_pMainMenu = new MainMenu();
  g_pTimerMenu = new TimerMenu();
  g_pActiveMenu = g_pMainMenu; //--> g_pActiveMenu legt hier start Menü fest

  // ... LCD Display .................................................................................................................. LCD Display ... //
  mylcd.Init_LCD();
  mylcd.Fill_Screen(BLACK);
  updateLcdDisplay();
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
}

// <<< sub functions <<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<< sub functions <<//
void updateLcdDisplay() {
  g_pActiveMenu->draw();
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
  Serial.println("ok");
}

void selectButton() {
  Serial.println("select");
  g_pActiveMenu->selectPressed();
}

// ... Wecker ............................................................................................................................ Wecker ... //


// ... Timer .............................................................................................................................. Timer ... //

