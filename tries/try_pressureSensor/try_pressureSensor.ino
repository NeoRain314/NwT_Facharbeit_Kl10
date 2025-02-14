#define PRESSURESENSOR_PIN A0

void setup() {
  Serial.begin(9600);
  pinMode(PRESSURESENSOR_PIN, INPUT);
}

void loop() {
  Serial.println(analogRead(PRESSURESENSOR_PIN));
  delay(200);
}
