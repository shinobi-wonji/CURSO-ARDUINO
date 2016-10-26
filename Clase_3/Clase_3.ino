const int pinTrigger = 4;
const int pinEcho = 5;

void setup() {
  // put your setup code here, to run once:
  pinMode (pinTrigger, OUTPUT); //seteo Salida
  pinMode (pinEcho, INPUT); //Seteo Entrada
  Serial.begin(9600); //Inicializo el puerto serial a 9600 bauds
}

void loop() {
  // put your main code here, to run repeatedly:
  int echoStatus = LOW;
  unsigned long lastHighTime = 0;
  unsigned long lastLowTime = 0;
  unsigned long deltaTime = 0;
  float distance = 0;

  delay(500);
  
  digitalWrite (pinTrigger, HIGH); //envio señal 
  delayMicroseconds(10); //de 10microsegundos
  digitalWrite (pinTrigger, LOW); //dejo de enviar señal

  echoStatus = digitalRead(pinEcho); 

  while (echoStatus  == LOW)
  {
    echoStatus = digitalRead(pinEcho); //Tengo que seguir leyendo hasta no recibir la señal de echo
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
  distance = (float)deltaTime / 58; //Calculo distancia en base al tiempo dividiendo por 58.
  Serial.print(distance); //Envío la distancia al puerto Serie para verlo por consola serie
  Serial.println(" cm"); 
  
}
