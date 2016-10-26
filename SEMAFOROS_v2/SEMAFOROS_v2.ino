int leds[]={3,4,5,6,7,8};//semaforo 1 y 2 (rojo, amarillo, verde)
int tiempo1=3000;
int tiempo2=500;
int n;
void setup() {
for (n=0;n<6;n++) {
pinMode (leds[n],OUTPUT);
}}

void secuencia(){
digitalWrite (leds[1],LOW);//amarillo1 off  
digitalWrite (leds[0],HIGH);//rojo1 on
digitalWrite (leds[3],LOW);//rojo2 off
digitalWrite (leds[5],HIGH);//verde2 on
delay (tiempo1);
digitalWrite (leds[5],LOW);//verde2 off
digitalWrite (leds[4],HIGH);//amarillo2 on
delay (tiempo2);
digitalWrite(leds[0],LOW);//rojo1 off
digitalWrite (leds[2],HIGH);//verde1 on
digitalWrite (leds[4],LOW);//amarillo2 off
digitalWrite (leds[3],HIGH);//rojo2 on
delay (tiempo1);
digitalWrite (leds[2],LOW);//verde1 off
digitalWrite(leds[1],HIGH);//amarillo on
delay (tiempo2);
}

void loop () {
  secuencia();
}
