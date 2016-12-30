#ifndef SETTINGS_h
#define SETTINGS_h

/*
 * Conecciones
 */

const int rsLcdPin = 8;
const int enableLcdPin = 9;
const int d4LcdPin = 4;
const int d5LcdPin = 5;
const int d6LcdPin = 6;
const int d7LcdPin = 7;

const int lcdBlackLight = 10;

const int analogButtonsPin = 0;

/*
 * Activacion del debug serial.
 * (Deben decomentar la definicion si quieren imprimir el debug por el puerto serial)
 */
#define DEBUG

#endif //SETTINGS_h
