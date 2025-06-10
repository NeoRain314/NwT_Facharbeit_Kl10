// <<< Inizalizing <<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<< Initalizing <<<//
int analog_input = A0; // Analoger Ausgang des Sensors --> direkter Messwert 
int digital_input = 3; // Digitaler Ausgang des Sensors --> hier Signal wenn Messwert über eingestelltem Schwellwert
  
// <<< setup <<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<< setup <<<//
void setup () {
  pinMode(analog_input, INPUT);
  pinMode(digital_input, INPUT);
  Serial.begin(9600); 
  Serial.println("KY-037 Geräuscherkennung");
}
  
// Das Programm liest die aktuellen Werte der Eingang-Pins
// und gibt diese auf der seriellen Ausgabe aus

// <<< loop <<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<< loop <<<//
void loop () {
  float analog_value;
  int digital_value;
    
  //Aktuelle Werte werden ausgelesen, auf den Spannungswert konvertiert (=kalibriert?)...
  analog_value = analogRead(analog_input) * (5.0 / 1023.0); 
  digital_value = digitalRead(digital_input);
    
  //... und an dieser Stelle ausgegeben
  //Serial.print("Analoger Spannungswert: "); 
  Serial.print("C:");
  Serial.println(analog_value, 4);
 // Serial.print(" V, \t Grenzwert: ");


  Serial.print("A:");
  Serial.println(2.5);

  Serial.print("B:");
  Serial.println(2.6);
  
  if (digital_value == 1) {
      //Serial.println("erreicht");
  }
  else {
     // Serial.println("noch nicht erreicht");
  }
  //Serial.println("----------------------------------------------------------------");
  delay(100);
}
