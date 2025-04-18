int timer_time[] = {0, 10};
unsigned long timer_start_mill = 0;
unsigned long timer_time_mill = 0;

bool timer_stat = true;

void setup() {
  Serial.begin(9600);
  Serial.println("");

  timer_time_mill = timer_time[0]*60000 + timer_time[1]*1000;
  timer_start_mill = millis();
  Serial.println(timer_time_mill);
}

void loop() {
  if(timer_stat) timer();
}

void timer() {
  if(millis() > timer_start_mill + timer_time_mill) {
    timer_stat = false;
    Serial.println("");
    Serial.println("-----------------------");
    Serial.println("Timer ended!");
    return;
  }

  unsigned long rest_mill = timer_start_mill + timer_time_mill - millis();
  int minutes = rest_mill/60000;
  int seconds = (rest_mill%60000) /1000;

  //Print Timer on Serial Monitor
  Serial.print("Timer: ");
  Serial.print(intToString(minutes, true));
  Serial.print(":");
  Serial.println(intToString(seconds, true));
}

char* intToString(int num, bool leading_zero) {
  static char buffer[16]; // 2 Stellen + Nullterminierung

  if (leading_zero) sprintf(buffer, "%02d", num); 
  else sprintf(buffer, "%d", num);
  return buffer;
}