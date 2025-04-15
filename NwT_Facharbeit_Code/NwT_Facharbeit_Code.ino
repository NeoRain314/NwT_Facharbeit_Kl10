/***************************************************************************************

g_... ---> globale Var
p --> pointer

Benennung:
  class: camelCase
  functions: camelCase
  variables: snake_case

****************************************************************************************/


// <<< Inizalizing <<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<< Initalizing <<//
unsigned long t1 = 0;
unsigned long t2 = 0;

// ... libraries ...................................................................................................................... libraries ... //

// ... Display .......................................................................................................................... Display ... //

// ... Menu Structure ............................................................................................................ Menu Structure ... //
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
};

AbstractMenu* g_pActiveMenu = 0;
AbstractMenu* g_pTimerMenu = 0;
AbstractMenu* g_pMainMenu = 0;



const char* main_menu_entries[] = {"Punkt 1", "Punkt 2", "Punkt 3"};

class MainMenu : public AbstractMenu {
  int selected_index = 0;

  public:

  MainMenu(){ //wird aufgerufen wenn new MainMenu() aufgerufen wird
    //...
  }

  virtual void draw(){
    for (int i=0; i<3; i++){
      if (i == selected_index) Serial.print("* ");
      Serial.println(main_menu_entries[i]);
    }
    Serial.println("");
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
  g_pMainMenu = new MainMenu();
  g_pTimerMenu = new TimerMenu();
  g_pActiveMenu = g_pMainMenu; //--> g_pActiveMenu legt hier start Menü fest
}

// <<< Loop <<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<< loop <<//
void loop() {
  g_pActiveMenu->draw();
  delay(1000);
  g_pActiveMenu->selectPressed();
}

// <<< sub functions <<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<< sub functions <<//
void updateClock(){
  Serial.println(millis());
}


// ... Wecker ............................................................................................................................ Wecker ... //


// ... Timer .............................................................................................................................. Timer ... //

/*if(millis() > t1+1000){
    t1 = millis();
    updateClock(); //update clock
  }
  
  //update current active module (like display clock, display menue, timer)*/
