#include <RTClib.h>

#define ledPin 7
int state = 0;


int soundValues[20] = {
  45, 52, 48, 55, 60, 58, 53, 47, 50, 49,
  54, 57, 56, 62, 59, 61, 63, 55, 52, 50
};

DateTime timeStamps[20] = {
  DateTime(2025, 6, 30, 9, 0, 0),
  DateTime(2025, 6, 30, 9, 5, 0),
  DateTime(2025, 6, 30, 9, 10, 0),
  DateTime(2025, 6, 30, 9, 15, 0),
  DateTime(2025, 6, 30, 9, 20, 0),
  DateTime(2025, 6, 30, 9, 25, 0),
  DateTime(2025, 6, 30, 9, 30, 0),
  DateTime(2025, 6, 30, 9, 35, 0),
  DateTime(2025, 6, 30, 9, 40, 0),
  DateTime(2025, 6, 30, 9, 45, 0),
  DateTime(2025, 6, 30, 9, 50, 0),
  DateTime(2025, 6, 30, 9, 55, 0),
  DateTime(2025, 6, 30, 10, 0, 0),
  DateTime(2025, 6, 30, 10, 5, 0),
  DateTime(2025, 6, 30, 10, 10, 0),
  DateTime(2025, 6, 30, 10, 15, 0),
  DateTime(2025, 6, 30, 10, 20, 0),
  DateTime(2025, 6, 30, 10, 25, 0),
  DateTime(2025, 6, 30, 10, 30, 0),
  DateTime(2025, 6, 30, 10, 35, 0)
};

int movementValues[20] = {
  3, 7, 5, 6, 4, 8, 7, 6, 5, 4,
  7, 9, 8, 6, 5, 4, 3, 7, 6, 5
};


void setup() {
  pinMode(ledPin, OUTPUT);
  digitalWrite(ledPin, HIGH);
  Serial.begin(9600); // Default communication rate of the Bluetooth module
}

void loop() {
  /*Serial.print("Testtext :D 12345 !!");
  delay(1000);*/

  for (int i = 0; i < 100; i++) {
    Serial.print(soundValues[i]);
    Serial.print(",");
    Serial.print(movementValues[i]);
    Serial.print(",");
    Serial.println(timeStamps[i].unixtime()); // oder .second()/.minute() usw.
  }
}