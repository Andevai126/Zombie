#include <Arduino.h>
#include <SoftwareSerial.h>

SoftwareSerial ATSerial(10, 11); // RX, TX

void setup() {
  Serial.begin(2400);
  ATSerial.begin(2400);
  Serial.println("Serial forwarder started");
}

void loop() {
  if (ATSerial.available()) {
  Serial.write(ATSerial.read());
  }
  if (Serial.available()) {
    ATSerial.write(Serial.read());
  }
}