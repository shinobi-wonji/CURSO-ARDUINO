/* Clase 4, TESTER 5V con divisor de tension */
const int lipo1Pin = A0;
const int lipo2Pin = A1;

void setup() 
{
  Serial.begin(9600);
  while(!Serial);  
}

void loop()
{
  int analog = 0;
  double tension1 = 0;
  double tension2 = 0;
  
  analog = analogRead(lipo1Pin);
  tension1 = 5.0*analog /1023.0; //Regla de 3.. 1023 es 5V.

  analog = analogRead(lipo2Pin);
  tension2 = 5.0*analog /1023.0 * 2.0 - tension1;

  
  Serial.print("Tension lipos: ");
  Serial.print(tension1);
  Serial.print(" V, ");
  Serial.print(tension2);
  Serial.println(" V. ");
  delay(1000);
}

