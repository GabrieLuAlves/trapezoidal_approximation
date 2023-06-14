#include <Arduino.h>

#define NUMBER_OF_POINTS 513
#define NUMBER_OF_TRAPEZOIDS 512

#define FIRST_POINT_INDEX 2
#define LAST_POINT_INDEX  NUMBER_OF_POINTS + 1

/**
 *
 * Authors: André Lucas Mendes Nazareth and Gabriel Luan Alves Valentim
 * Date: 2023-06-01
 *
 * Copyright (C) 2023 André Lucas Mendes Nazareth and Gabriel Luan Alves
 * Valentim - All Rights Reserved You may use, distribute and modify this code
 * under the terms of the Apache 2.0 license.
 *
 * This code DOES NOT reuse any code written before in any ways.
 *
 * Embedded Systems course assignment.
 *
 * Target platform: Arduino UNO R3, but should work with any other
 * platform in which is possible to develop using the Arduino framework
 *
 * This code calculates the integral from a to b of a given function f(x).
 *
 * It receives, from the serial port, 502 single-precision floating-point
 * values. The first one must be the x-value of the start of the integration
 * interval, which will be called "a", the second one must be the x-value of the
 * end of the integration interval, which will be called "b", and the rest of
 * the 500 floating point values are the y-values of 500 evenly distributed
 * points throught the x-axis.
 *
 * After receiving all of them, it writes to the
 * serial port the result of the integration in the format of a single-precision
 * floating-poing point value, and then the loop restarts.
 *
 */


/**
 *
 * The setup function from Arduino framework. Initializes the
 * serial interface.
 *
 * @author Gabriel Luan Alves Valentim
 * @author André Lucas Mendes Nazareth
 *
 */
void setup() {
  Serial.begin(115200);
}

/**
 *
 * The loop function from Arduino framework. Receives the bytes and carries on
 * all the calculations.
 *
 * Modifies the following global variables: a, b, accumulator, aux and n (all of
 * them).
 *
 * @author Gabriel Luan Alves Valentim
 * @author André Lucas Mendes Nazareth
 *
 */
void loop() {

  /**
   *
   * To apply the trapezoidal rule using 500 evenly distributed points through
   * the x-axis, we must sum f(a), f(b) and all the other 498 values for f(x)
   * multiplied by two, and then multiply the result of these sums by dx, which
   * is calculated as shown bellow.
   *
   * dx = (b - a) / (the number of trapezoids)
   *
   * The number of trapezoids in this case equals to 499 since we have 500
   * points and these trapezoids are amoung them.
   *
   * So, being all the y-values of the points indexed from 0 to 499 (500
   * elements), all we need to do is to calcute the result as it follows:
   *
   * Result = dx / 2 * (y[0] + 2 * y[1] + 2 * y[2] + ... + 2 * y[498] + y[499])
   *
   * Which notably can be re-written as it follows for optimization purposes:
   *
   * Result = dx / 2 * 2 * (y[0] / 2 + y[1] + y[2] + ... + y[498] + y[499] / 2)
   * Result = dx * (y[0] / 2 + y[1] + y[2] + ... + y[498] + y[499] / 2)
   *
   * Since storing all these values takes too much memory, we will accumulate
   * the result of each sum in a variable, which is called "accumulator". And
   * make these sums as the values are received.
   *
   * We will also use a variable "n" to count the incoming values, which
   * will be incremented in the end of each iteration.
   *
   * The first value received from the serial port will be considered "a", the
   * second one will be considered "b", and the other ones are the y-axis
   * values, which will be refered to as being simply "y".
   *
   * So when a value is received, it is stored in the "aux" variable.
   * Then,
   * if n = 0, it's the first value, so that's "a"
   * if n = 1, it's the second value, so that's "b"
   * if n = 2, it's the first y-value point and must divided
   *    by two before being summed to the accumulator
   * if n = 501, 's the last y-value point and must divided
   *    by two before being summed to the accumulator
   *
   * in any other case just sum the received value to accumulator.
   *
   * All this process is done in this function.
   *
   */

  float aux;              /* Temporary storage for the received values */

  uint32_t elapsedTime = 0;
  uint32_t t = 0;
  
  /* Read a */
  Serial.readBytes((uint8_t *)&aux, 4);
  t = micros();
  float a = aux;
  elapsedTime += micros() - t;

  /* Read b */
  Serial.readBytes((uint8_t *)&aux, 4);
  t = micros();
  float b = aux;
  elapsedTime += micros() - t;

  float accumulator = 0;  /* Variable that will accumulate the results of the sums */

  /* Read first Y value */
  Serial.readBytes((uint8_t *)&aux, 4);

  t = micros();
  accumulator += aux / 2;
  elapsedTime += micros() - t;

  /* Read the next n Y values */
  for (uint16_t i = 0 ; i < 498 ; i++) {
    Serial.readBytes((uint8_t *)&aux, 4);

    t = micros();
    accumulator += aux;
    elapsedTime += micros() - t;
  }

  /* Read the last Y value */
  Serial.readBytes((uint8_t *)&aux, 4);

  t = micros();

  accumulator += aux / 2;
  float result = accumulator * (b - a) / 499;

  elapsedTime += micros() - t;

  /* Sending the floating-point in four bytes */
  Serial.write((uint8_t *)&result, 4);

  /* Sending the elapsed time in four bytes */
  Serial.write((uint8_t *)&elapsedTime, 4);

  /* Reset */
  accumulator = 0;
  elapsedTime = 0;
} /* end of iteration, and then repeat */