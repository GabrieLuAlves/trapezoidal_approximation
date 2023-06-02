#include <Arduino.h>

#define DOUBLE_SIZE 8

/**
 *
 * Command list
 *
 * =========================================================================
 *
 * WRITE COMMANDS
 * COMMAND      NAME        RETURNS
 * 0b10000001   clear       1
 *
 * =========================================================================
 *
 * READ COMMANDS
 * COMMAND      NAME        RETURNS
 * 0b01000001   read_state  A byte which equals to:
 *                          0b00, nothing was done (recent reset)
 *                          0b01, if only the range was set
 *                          0b10, if only the 500 floats where received
 *                          0b11, if the result was already calculated
 *
 * 0b10000010   get_result  The result of the integration
 *
 * =========================================================================
 *
 * WRITE DATA
 * COMMAND      NAME        RETURNS
 * 0b11000001   set_range   1
 * 0b11000010   push        1
 *
 * =========================================================================
 *
 */

float a;
float b;
float accumulator = 0;
float dx;
float aux;

float result = 0;

uint8_t range_set = 0;
uint8_t values_set = 0;

uint16_t nPush = 0;

void setup() { Serial.begin(115200); }

void clear() {
  range_set = 0;
  values_set = 0;
  accumulator = 0;
  nPush = 0;

  a = 0;
  b = 0;
}

void readState() {
  uint8_t value = values_set * 2 + range_set;
  Serial.write(&value, 1);
}

void setRange() {
  float values[2];

  Serial.readBytes((uint8_t *)values, 8);

  a = values[0];
  b = values[1];
  range_set = 1;

  Serial.print((char)1);
}

void push() {
  float values[10];

  // read 10 values
  Serial.readBytes((uint8_t *)values, 40);
  nPush++;

  if (nPush == 1)
    values[0] /= 2;
  else if (nPush == 10) {
    values[9] /= 2.0;
  }

  for (uint8_t i = 0; i < 10; i++) {
    accumulator += values[i];
  }

  if (nPush == 10) {
    values_set = 1;
  }

  Serial.print((char)10);
}

void getResult() {
  Serial.write((uint8_t *)&result, 4);
  clear();
}

void loop() {
  if (Serial.available() > 0) {
    switch (Serial.read()) {

    case 0b10000001:
      clear();
      break;

    case 0b11000001:
      setRange();
      break;

    case 0b11000010:
      push();
      break;

    case 0b10000010:
      getResult();
      break;

    case 0b01000001:
      readState();
      break;

    default:
      Serial.write("F");
      break;
    }

    if (values_set && range_set) {
      result = accumulator * (b - a) / 499.0;
    }
  }
}