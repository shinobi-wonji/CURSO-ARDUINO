#include <LiquidCrystal.h>

const int lmPin = A0;
const int motorPin = 13;

const double tempIdeal = 27.0;
const double tempError = 1.0;

double tempActual = 0.0;

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


void printTempLcd()
{

  lcd.setCursor(0,0);
  lcd.print("Temp: ");
  lcd.print(tempActual);
  lcd.print(" ");
  lcd.write(byte(0));
  lcd.print("C");
}

void printMotorStatusLcd()
{
  lcd.setCursor(0,1);
  if(estadoMotor == true)
    lcd.print("Motor Encendido");
  else
    lcd.print("Motor Apagado  ");
}

void actualizarTemp()
{
  int analog = 0;
  analog = analogRead(lmPin);
  tempActual = analog* 5000.0  /1023.0 /10.0;  //5V -> 1023
}

void setup() 
{
  pinMode (motorPin,OUTPUT);
  lcd.createChar(0, grado);
  Serial.begin(9600);
  while(!Serial);

  lcd.begin(16,2);
  actualizarTemp();
  printMotorStatusLcd();
  printTempLcd();
  
}

void loop() 
{
  unsigned  long currentTime = 0;
  

  actualizarTemp();
  
  currentTime = millis();
  
  if (currentTime - lastPrint > intervalo)
  {
    Serial.print("Temperatura: ");
    Serial.print(tempActual);
    Serial.println(" °C");

    printTempLcd();   
        
    lastPrint = currentTime;
  }
  
  if (tempActual >= tempIdeal + tempError && estadoMotor == false)
  {
    digitalWrite(motorPin, HIGH);
    Serial.println("Motor Encendido");
    estadoMotor = true;
    printMotorStatusLcd();
  }
  else if (tempActual <=tempIdeal - tempError && estadoMotor == true)
  {
    digitalWrite(motorPin, LOW);
    Serial.println("Motor Apagado");
    estadoMotor = false;
    printMotorStatusLcd();
  }
    
}
