const int lmPin = A0;
const int motorPin = 13;

const double tempIdeal = 25.0;
const double tempError = 1.0;

bool estadoMotor = false;

void setup() {
  // put your setup code here, to run once:
  pinMode (motorPin,OUTPUT);
  Serial.begin(9600);
  while(!Serial);

}

void loop() {
  // put your main code here, to run repeatedly:

  int analog = 0;
  double temp = 0;
  analog = analogRead(lmPin);
  temp = analog* 5000.0  /1023.0 /10.0;  //5V -> 1023
  Serial.print("Temperatura: ");
  Serial.print(temp);
  Serial.println(" °.");

  if (temp >= tempIdeal + tempError && estadoMotor == false)
  {
    digitalWrite(motorPin, HIGH);
    Serial.println("Motor Encendido");
    estadoMotor = true;
  }
  else if (temp <=tempIdeal - tempError && estadoMotor == true)
  {
    digitalWrite(motorPin, LOW);
    Serial.println("Motor Apagado");
    estadoMotor = false;
  }
  
  delay(300);
  
}
