
/*
***************************************************************************************
*                               CURSO ARDUINO SCEU - UTN.BA                           *
*                                                                                     *
*                                TP 1: SEMAFORO - 04.10.16                            *
*                                     Ing. Pablo Sualdo                               *
*                                      v3.3 - 10.10.16                                *
*       El objetivo es realizar una transición simplificada de luces de semaforo      *
*                                 en dos esquinas (1) y (2)                           *
*                                                                                     *                                      
***************************************************************************************
*/

// Definicion de constantes:
const int paso = 5000;
const int trans = 2000;

void setup() {
  pinMode(8,OUTPUT);  //ROJO1
  pinMode(7,OUTPUT);  //AMARILLO1
  pinMode(6,OUTPUT);  //VERDE1
  pinMode(5,OUTPUT);  //ROJO2
  pinMode(4,OUTPUT);  //AMARILLO2
  pinMode(3,OUTPUT);  //VERDE2
}

void loop() {
  digitalWrite(8,HIGH); //PRENDO ROJO1
  digitalWrite(3,HIGH); //PRENDO VERDE2
  delay(paso);          //Retardo de paso
  digitalWrite(4,HIGH); //PRENDO AMARILLO2
  delay(trans);         //Retardo de transicion
  digitalWrite(4,LOW);  //APAGO AMARILLO2
  digitalWrite(8,LOW);  //APAGO ROJO1
  digitalWrite(3,LOW);  //APAGO VERDE2
  digitalWrite(5,HIGH); //PRENDO ROJO2
  digitalWrite(6,HIGH); //PRENDO VERDE1
  delay(paso);          //Retardo de paso
  digitalWrite(7,HIGH); //PRENDO AMARILLO1
  delay(trans);         //Retardo de transicion
  digitalWrite(7,LOW);  //APAGO AMARILLO1
  digitalWrite(5,LOW);  //APAGO ROJO2
  digitalWrite(6,LOW);  //APAGO VERDE1
}

