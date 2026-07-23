#include <stdlib.h> // strtol()

SoftwareSerial DFSerial(-1, 4); // RX3, TX

uint16_t calculateCheckSum(uint8_t *buffer) {
  uint16_t sum = 0;
  for (int i=1; i<7; i++) {
    sum += buffer[i];
  }
  return -sum;
}

uint8_t* createCommand(uint8_t command, uint8_t argumentHigh, uint8_t argumentLow) {
    static uint8_t array[10] = {0x7E, 0xFF, 06, 00, 01, 00, 00, 00, 00, 0xEF};
    array[3] = command;
    array[5] = argumentHigh;
    array[6] = argumentLow;
    uint16_t checkSum = calculateCheckSum(array);
    array[7] = (uint8_t)(checkSum >> 8);
    array[8] = (uint8_t)(checkSum & 0xFF);
    return array;
}

void play(uint8_t track, uint8_t duration) {
  // Disconnect speaker
  digitalWrite(1, LOW);
  // Power on DFPlayer
  digitalWrite(0, HIGH);
  delay(1000);
  // Set volume to 21 (max 30)
  DFSerial.write(createCommand(0x06, 0x00, 0x15), 10);
  delay(100);
  // Play track
  DFSerial.write(createCommand(0x03, 0x00, track), 10);
  delay(500);
  // Connect speaker
  digitalWrite(1, HIGH);
  // Wait until track is finished
  delay((duration+1)*1000); // Maybe work with mod 8 and deep sleep?
  // Disconnect speaker
  digitalWrite(1, LOW);
  // Power off DFPlayer
  digitalWrite(0, LOW);
}

void randomSetup() {
  randomSeed(millis());
}

void randomShuffle(uint8_t* array, size_t n) {
  for (size_t i = n - 1; i > 0; i--) {
    size_t j = random(0, i + 1);
    uint8_t temp = array[i];
    array[i] = array[j];
    array[j] = temp;
  }
}

void playRandom() {
  static uint8_t durations[] = {0, 6, 16, 4, 4, 5};
  static uint8_t tracks[] = {1, 2, 3, 4, 5};
  static uint8_t pointer = 99;
  if (pointer > 4) {
    pointer = 0;
    randomShuffle(tracks, 5);
  } else {
    pointer++;
  }
  uint8_t track = tracks[pointer];
  play(track, durations[track]);
}