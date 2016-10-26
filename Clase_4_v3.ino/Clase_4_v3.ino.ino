/* Clase 4, TESTER 5V */
const int analogPin = A0;
void setup() 
{
  Serial.begin(9600);
  while(!Serial);  
}

void loop()
{
  int analog = 0;
  double tension = 0;
  
  analog = analogRead(analogPin);
  tension = 5.0*analog /1023.0; //Regla de 3.. 1023 es 5V.

  Serial.print("Tension: ");
  Serial.print(tension);
  Serial.println(" V. ");
}

