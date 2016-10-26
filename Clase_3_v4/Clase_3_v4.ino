/* Clase 3*/

const int pinTrigger = 4;
const int pinEcho = 5;

const int pinLedVerde1 = 8;
const int pinLedVerde2 = 9;
const int pinLedAmarillo = 10;
const int pinLedRojo = 11;

              
void setup() {
  // put your setup code here, to run once:
  pinMode (pinTrigger, OUTPUT); //seteo Salida
  pinMode (pinEcho, INPUT); //Seteo Entrada
  pinMode (pinLedVerde1, OUTPUT);
  pinMode (pinLedVerde2, OUTPUT);
  pinMode (pinLedAmarillo, OUTPUT);
  pinMode (pinLedRojo, OUTPUT);
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
  char letter = 0;

  digitalWrite (pinTrigger, HIGH); //envio señal 
  delayMicroseconds(10); //de 10microsegundos
  digitalWrite (pinTrigger, LOW); //dejo de enviar señal

  echoStatus = digitalRead(pinEcho); 

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

  if (Serial.available()) //Preguntar si se recibio algun dato por puerto serie
  {
     letter = Serial.read(); 
     if (letter == 'C')
     {
        distance = (float)deltaTime / 58; //Calculo distancia en base al tiempo dividiendo por 58 para cm.
        Serial.print(distance); //Envío la distancia al puerto Serie para verlo por consola serie
        Serial.println(" cm"); 
     }
     else if (letter == 'P')
     {
        distance = (float)deltaTime / 148; //Calculo distancia en base al tiempo dividiendo por 148 para pulgadas.
        Serial.print(distance); //Envío la distancia al puerto Serie para verlo por consola serie
        Serial.println(" pulgadas"); 
     }
     else 
     {
        Serial.println("ERROR!."); //Imprimir mensaje de error
     } 
  }       
  distance = (float) deltaTime/58;
  if (distance < 50)
  {
    digitalWrite(pinLedVerde1, LOW);
    digitalWrite(pinLedVerde2, LOW);
    digitalWrite(pinLedAmarillo, LOW);
    digitalWrite(pinLedRojo, HIGH);
  }
  else if (distance < 70) 
  {
    digitalWrite(pinLedVerde1, LOW);
    digitalWrite(pinLedVerde2, LOW);
    digitalWrite(pinLedAmarillo, HIGH);
    digitalWrite(pinLedRojo, LOW);
  }
  else if (distance < 100) 
  {
    digitalWrite(pinLedVerde1, LOW);
    digitalWrite(pinLedVerde2, HIGH);
    digitalWrite(pinLedAmarillo, LOW);
    digitalWrite(pinLedRojo, LOW);
  }
  else  
  {
    digitalWrite(pinLedVerde1, HIGH);
    digitalWrite(pinLedVerde2, LOW);
    digitalWrite(pinLedAmarillo, LOW);
    digitalWrite(pinLedRojo, LOW);
  }
    
}

