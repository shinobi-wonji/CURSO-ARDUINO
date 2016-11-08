#include <LiquidCrystal.h>

const int lmPin = A0;
const int motorPin = 13;

const double tempIdeal = 27.0;
const double tempError = 1.0;

bool estadoMotor = false;

unsigned long lastPrint = 0;
const int intervalo = 5000;

byte grado[8] = {
  B01110,
  B10001,
  B10001,
  B01110,
  B00000,
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
  // put your setup code here, to run once:
  pinMode (motorPin,OUTPUT);
  Serial.begin(9600);
  while(!Serial);

  lcd.begin(16,2);
}

void loop() {
  // put your main code here, to run repeatedly:

  int analog = 0;
  double temp = 0;
  unsigned  long currentTime = 0;
  lcd.createChar(0, grado);
  
  analog = analogRead(lmPin);
  temp = analog* 5000.0  /1023.0 /10.0;  //5V -> 1023

  currentTime = millis();
  
  if (currentTime - lastPrint > intervalo)
  {
    Serial.print("Temperatura: ");
    Serial.print(temp);
    Serial.println(" °.");
    
    lcd.setCursor(0,0);
    lcd.print("Temp: ");
    lcd.print(temp);
    lcd.write(byte(0));
    lcd.print("C");
     
    lastPrint = currentTime;
  }
  
  if (temp >= tempIdeal + tempError && estadoMotor == false)
  {
    digitalWrite(motorPin, HIGH);
    Serial.println("Motor Encendido");
    lcd.setCursor(0,1);
    lcd.print("Motor Encendido");
    estadoMotor = true;
  }
  else if (temp <=tempIdeal - tempError && estadoMotor == true)
  {
    digitalWrite(motorPin, LOW);
    Serial.println("Motor Apagado");
    lcd.setCursor(0,1);
    lcd.print("Motor Apagado  ");
    estadoMotor = false;
  }
    
}
