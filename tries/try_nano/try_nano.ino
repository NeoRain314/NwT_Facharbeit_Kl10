void setup() {
  // Pin 13 als Ausgang definieren (dort ist die Onboard-LED angeschlossen)
  pinMode(13, OUTPUT);
}

void loop() {
  digitalWrite(13, HIGH); // LED an
  delay(1000);            // 1 Sekunde warten
  digitalWrite(13, LOW);  // LED aus
  delay(1000);            // 1 Sekunde warten
}
