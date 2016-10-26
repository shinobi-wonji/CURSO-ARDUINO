const int pinSwitch = 13;
const int pinLed = 4;

void setup() {
  // put your setup code here, to run once:
  pinMode(pinSwitch, INPUT_PULLUP);
  pinMode(pinLed, OUTPUT);

  Serial.begin(9600);
}


void loop() {
  // put your main code here, to run repeatedly:

  int estado = LOW;
  estado = digitalRead(pinSwitch);
  digitalWrite(pinLed, estado);
  Serial.print("A");

}
