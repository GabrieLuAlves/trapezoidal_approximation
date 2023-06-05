#include <Arduino.h>

#define DOUBLE_SIZE 8

/**
 *
 * Command list
 * set_interval 0b10000001
 * push values  0b10000010
 * get_result   0b10000100
 * clear        0b10001000
 *
 */

float a;
float b;
float accumulator = 0;
float aux;
uint16_t n = 0;

void setup() { Serial.begin(115200); }

void loop() {
  while (n < 502) {
    if (Serial.available() > 0) {
      aux = Serial.readStringUntil('\n').toFloat();

      if (n == 0) {
        a = aux;
      } else if (n == 1) {
        b = aux;
      } else if (n == 2 || n == 501) {
        accumulator += aux / 2.0;
      } else {
        accumulator += aux;
      }

      n++;
    }
  }

  float dx = (b - a) / 499.0;
  accumulator *= dx;

  Serial.write((uint8_t *)&accumulator, 4);

  accumulator = 0;
  n = 0;
}