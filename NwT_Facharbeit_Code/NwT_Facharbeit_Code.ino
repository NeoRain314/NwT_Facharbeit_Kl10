/*
g_... ---> globale Var
+ --> pointer
*/


unsigned long t1 = 0;
unsigned long t2 = 0;

class AbstractMenu {
  public:
  virtual void draw(){
    Serial.println("Ich bin ein Abstract Menu!");
  }
  
  virtual void ok_pressed(){
    Serial.println("not implemented");
  }
};

AbstractMenu* g_pActiveMenu = 0;
AbstractMenu* g_pTimerMenu = 0;
AbstractMenu* g_pMainMenu = 0;

class TimerMenu : public AbstractMenu {
  public:

  virtual void draw(){
    Serial.println("Timer Menu!");
  }

  virtual void ok_pressed(){
    g_pActiveMenu = g_pMainMenu;
  }
};

class MainMenu : public AbstractMenu {
  public:

  MainMenu(){ //wird aufgerufen wenn new MainMenu() aufgerufen wird
    //...
  }

  virtual void draw(){
    Serial.println("Main Menu!");
  }

  virtual void ok_pressed(){
    g_pActiveMenu = g_pTimerMenu;
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
