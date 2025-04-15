/*
g_... ---> globale Var
p --> pointer
*/

unsigned long t1 = 0;
unsigned long t2 = 0;

class AbstractMenu {
  public: // public --> im folgenden funktionen, die von außen aufgerufen werden können
  virtual void draw(){  //virtual --> abgeleitete Klassen können funktion überschreiben
    Serial.println("Ich bin ein Abstract Menu!");
  }
  
  virtual void ok_pressed() {
    Serial.println("ok not implemented");
  }

  virtual void select_pressed() {
    Serial.println("select not implemented");
  }
};

AbstractMenu* g_pActiveMenu = 0;  // g --> globale Variable; p --> pointer

AbstractMenu* g_pTimerMenu = 0;
AbstractMenu* g_pMainMenu = 0;



const char* main_menu_entries[] = {"Timer Menu", "Punkt 2", "Punkt 3"};

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

  virtual void select_pressed() {
    selected_index = (selected_index + 1) % 3; //damit i nie größer 2
  }

  virtual void ok_pressed(){
    g_pActiveMenu = g_pTimerMenu;x
  }
};

class TimerMenu : public AbstractMenu {
  public:

  virtual void draw(){
    Serial.println("Timer Menu!");
  }

  virtual void ok_pressed(){
    if (selected_index == 0) g_pActiveMenu = g_pMainMenu;
    if (selected_index == 1) g_pActiveMenu = g_pMainMenu;
    if (selected_index == 2) g_pActiveMenu = g_pMainMenu;
  }
};


// <<< Inizalizing <<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<< Initalizing <<//


// <<< setup <<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<< setup <<//


void setup() {
  Serial.begin(9600); //Serial Monitor
  g_pMainMenu = new MainMenu();
  g_pTimerMenu = new TimerMenu();
  g_pActiveMenu = g_pMainMenu; //--> g_pActiveMenu legt hier start Menü fest
}

// <<< Loop <<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<< Loop <<//
void loop() {
  g_pActiveMenu->draw();
  delay(1000);
  g_pActiveMenu->ok_pressed();
}

// <<< sub functions <<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<< sub functions <<//
void updateClock(){
  Serial.println(millis());
}


// Wecker .................................................................................................. Wecker //

// Timer  .................................................................................................. Timer //


/*if(millis() > t1+1000){
    t1 = millis();
    updateClock(); //update clock
  }
  
  //update current active module (like display clock, display menue, timer)*/
