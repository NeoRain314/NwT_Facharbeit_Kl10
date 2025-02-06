// <<< inizaializing <<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<< inizaializing <<< //

int piezo = 5;
int bewegung = 7; 
int bewegungsstatus = 0; // darin wird später gespeichert ob eine Bewegung erkannt wurde oder nicht 

// <<< setup <<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<< setup <<< //

void setup() {
  pinMode (piezo, OUTPUT);
  pinMode (bewegung, INPUT);
}

// <<< loop <<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<< loop <<< //

void loop() {
  bewegungsstatus = digitalRead (bewegung); // wenn 5 Volt (also Bewegung wahrgenommen) dann HIGH; wenn 0 Volt (also keine Bewegung) dann LOW --> wird in Variable bewegungsstatus gespeichert
  if (bewegungsstatus == HIGH) { // wenn eine Bewegung wahrgenommen wurde...
    digitalWrite (piezo, HIGH); //...dann ton von piezo
    delay (5000); // 5 sekunden lang
    digitalWrite (piezo, LOW); // und dann wieder leise
  }
  else { // wenn keine Bewegung wahrgenommen wurde ...
    digitalWrite (piezo, LOW); // ... dann soll der piezo lese bleiben
  }
}
