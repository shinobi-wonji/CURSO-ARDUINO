
void setup() {
  // put your setup code here, to run once:

  pinMode(8,OUTPUT);
  pinMode(7,OUTPUT);
  pinMode(6,OUTPUT);
  pinMode(5,OUTPUT);
  pinMode(4,OUTPUT);
  pinMode(3,OUTPUT);
  

}

void loop() {
  // put your main code here, to run repeatedly:

  digitalWrite(8,HIGH); //PRENDO ROJO1
  digitalWrite(3,HIGH); //PRENDO VERDE2
  delay(3000);
  digitalWrite(4,HIGH); //PRENDO AMARILLO2
  digitalWrite(3,LOW); //APAGO VERDE2
  delay(1000);
  digitalWrite(8,LOW); //APAGO ROJO1
  digitalWrite(3,LOW); //APAGO VERDE2
  digitalWrite(5,HIGH); //PRENDO ROJO2
  digitalWrite(6,HIGH); //PRENDO VERDE1
  digitalWrite(4,LOW); //APAGO AMARILLO2
  delay(3000);
  digitalWrite(6,LOW); //APAGO VERDE1
  digitalWrite(7,HIGH); //PRENDO AMARILLO1
  delay(1000);
  digitalWrite(7,LOW); //APAGO AMARILLO2
  digitalWrite(5,LOW); //APAGO ROJO2
}

