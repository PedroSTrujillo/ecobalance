#include <SoftwareSerial.h>

SoftwareSerial HM10(3, 4);  // RX, TX

char myChar;




void setup() {
  // Open serial communications and wait for port to open:
  Serial.begin(9600);
  Serial.println("HM-10 started at 9600");
  HM10.begin(9600);
  HM10.println("HM-10 connected at 9600");
}

void loop() {  // run over and over
  //Leer datos
  while (HM10.available()) {
    myChar = HM10.read();
    Serial.print(myChar);
  }

  //Escribir datos
  if (Serial.available()) {
    myChar = Serial.read();
    HM10.print(myChar);
  }
}