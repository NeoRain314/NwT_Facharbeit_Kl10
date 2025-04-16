int timer_time = 10;

void setup() {
  Serial.Begin(9600);

}

void loop() {
  // put your main code here, to run repeatedly:

}


void printTimerTime() {
  int minutes = totalSeconds / 60;
  int seconds = totalSeconds % 60;

  // Anzeige im Format MM:SS mit führender Null
  char buffer[6];
  sprintf(buffer, "%02d:%02d", minutes, seconds);
  Serial.println(buffer);
}
