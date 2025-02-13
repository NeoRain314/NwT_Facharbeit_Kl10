#define VIBRATION_PIN 6

void setup() {
  pinMode(VIBRATION_PIN, OUTPUT);
}

void loop() {
  digitalWrite(VIBRATION_PIN, HIGH);
  delay(1000);
  digitalWrite(VIBRATION_PIN, LOW);
  delay(1000);
}
