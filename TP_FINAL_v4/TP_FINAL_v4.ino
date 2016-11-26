const int pinTrigger = 4;
const int pinEcho = 5;
const int pinLeds = 6;
bool state = false;
int brillo = 0;


void setup() {
  // put your setup code here, to run once:

  pinMode (pinTrigger, OUTPUT); //Seteo Salida Sensor Distancia
  pinMode (pinEcho, INPUT); //Seteo Entrada Sensor Distancia
  pinMode (pinLeds, OUTPUT); //Seteo Salida para LedBar
  Serial.begin(9600); //Inicializo el puerto serial a 9600 bauds
  while (!Serial); //Para Arduino Leonardo o Mega, tienen un uso distinto del puerto USB


  

}

void loop() {
  // put your main code here, to run repeatedly:
  
  int echoStatus = LOW;
  unsigned long lastHighTime = 0;
  unsigned long lastLowTime = 0;
  unsigned long deltaTime = 0;
  float distance = 0;
  

  digitalWrite (pinTrigger, HIGH); //envio señal ultrasonido
  delayMicroseconds(10); //por 10 microsegundos
  digitalWrite (pinTrigger, LOW); //dejo de enviar la señal

  echoStatus = digitalRead(pinEcho); //Leo señal de retorno de ultrasonido

  while (echoStatus  == LOW)
  {
    echoStatus = digitalRead(pinEcho); //Tengo que seguir leyendo hasta empezar a recibir la señal de echo
  }

  lastHighTime = micros(); //Almaceno el tiempo en el cual empiezo a recibir la señal de echo

  while (echoStatus  == HIGH)
  {
    echoStatus = digitalRead(pinEcho); //Tengo que seguir leyendo hasta terminar de recibir la señal de echo
  }

  lastLowTime = micros(); //Almaceno el tiempo en el cual dejo de recibir la señal de echo

  if (lastLowTime < lastHighTime)
    return;
    
  deltaTime = lastLowTime - lastHighTime; // Resto los 2 tiempos y me quedo con la diferencia que es la cantidad de tiempo
  distance = (float)deltaTime / 58;
      
  if (distance <= 5 && state == false)
  {
    while (brillo <= 255)
    {
      analogWrite(pinLeds , brillo);
      brillo++;
      delay(20);
    }
    brillo = 255;
    state = true;
  } 
  else if (distance <= 5 && state == true)
  {
    while (brillo >=0)
    {
      analogWrite(pinLeds , brillo);
      brillo--;
      delay(10);
    }
    brillo = 0;
    state = false;
  }
  

    
  Serial.print(distance);
  Serial.println(" cm"); 
  Serial.print(deltaTime);
  Serial.println(" MicroS"); 
  Serial.print(brillo);
  Serial.println(" nivel de brillo"); 
  
}
