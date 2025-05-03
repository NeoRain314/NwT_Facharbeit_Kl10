// <<< inizaializing <<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<< inizaializing <<< //
#define MOTIONSENSOR_PIN 7

int motion_stat = 0; // darin wird später gespeichert ob eine Bewegung erkannt wurde oder nicht 

// <<< setup <<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<< setup <<< //

void setup() {
  Serial.begin(9600);
  pinMode(MOTIONSENSOR_PIN, INPUT);
}

// <<< loop <<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<< loop <<< //

void loop() {
  motion_stat = digitalRead(MOTIONSENSOR_PIN); // wenn 5 Volt (also Bewegung wahrgenommen) dann HIGH; wenn 0 Volt (also keine Bewegung) dann LOW --> wird in Variable bewegungsstatus gespeichert
  
  if (motion_stat == HIGH) { 
    Serial.println(1);
  }
  else { 
    Serial.println(0);
  }
  delay(500);
}