#include <LiquidCrystal.h>

const int lmPin = A0;
const int motorPin = 13;

const double tempIdeal = 27.0;
const double tempError = 1.0;

bool estadoMotor = false;

unsigned long lastPrint = 0;
const int intervalo = 5000;

byte grado[8] = {
  B10001,
  B00000,
  B01110,
  B10001,
  B01110,
  B00000,
  B00000,
};

/*
 *  LCD RS pin to digital pin 8
 *  LCD Enable pin to digital pin 9
 *  LCD D4 pin to digital pin 4
 *  LCD D5 pin to digital pin 5
 *  LCD D6 pin to digital pin 6
 *  LCD D7 pin to digital pin 7
 *  
 */

LiquidCrystal lcd(8,9,4,5,6,7);

void setup() {
  lcd.createChar(0, grado);
  lcd.begin(16, 2);  
  lcd.write(byte(0));
}

void loop() {}

