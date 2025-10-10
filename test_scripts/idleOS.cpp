#include <Arduino.h>

#include <SoftwareSerial.h>
SoftwareSerial LOGSerial(0, 1); // RX, TX1
SoftwareSerial DFSerial(3, 4);
#include "df.hpp"

void setup() {
  LOGSerial.begin(2400);
  DFSerial.begin(9600);
  LOGSerial.listen();

  // button input
  pinMode(2, INPUT);

  // transistor controlpin / power dfplayer
  pinMode(0, OUTPUT);
  digitalWrite(0, LOW);

  // led indicator
  pinMode(3, OUTPUT);
  digitalWrite(3, LOW);

  LOGSerial.print(F("Setup complete"));
}

void loop() {
  static unsigned long timer = millis();

  if (LOGSerial.available() && !digitalRead(2)) {
    String s1 = LOGSerial.readStringUntil(' ');
    String s2 = LOGSerial.readStringUntil(' ');
    String s3 = LOGSerial.readStringUntil('\n');
    
    if (!(s1.length() == 0 || s2.length() == 0 || s3.length() == 0)) {
      LOGSerial.println("cmd: < " + s1 + " " + s2 + " " + s3 + " >");

      uint8_t byte1 = (uint8_t) strtol(s1.c_str(), NULL, 16);
      uint8_t byte2 = (uint8_t) strtol(s2.c_str(), NULL, 16);
      uint8_t byte3 = (uint8_t) strtol(s3.c_str(), NULL, 16);
      
      DFSerial.listen();
      DFSerial.flush();

      DFSerial.write(createCommand(byte1, byte2, byte3), 10);

      LOGSerial.print("reply: < ");
      while (millis() - timer < 2000) {
        if (DFSerial.available()) {
          LOGSerial.print(DFSerial.read(), HEX);
          LOGSerial.write(" ");
        }
      }
      LOGSerial.println(">");

      LOGSerial.listen();
      LOGSerial.flush();
    }
  }



  if (millis() - timer > 1500) {
    timer = millis();
    LOGSerial.print(".");
    LOGSerial.print(digitalRead(2));
  }



  if (digitalRead(2) == HIGH) {
    digitalWrite(0, HIGH);
    delay(100);
    digitalWrite(0, LOW);
  }
}