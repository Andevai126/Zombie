#include <Arduino.h>

uint16_t calculateCheckSum(uint8_t *buffer){
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
