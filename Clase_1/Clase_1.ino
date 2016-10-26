const int PIN = 13;
int DELTATIME = 100;

void Blink(int PINBLINK, int DELTABLINK)
{
  digitalWrite(PINBLINK,HIGH);
  delay(DELTATIME);
  digitalWrite(PINBLINK,LOW);
  delay(DELTATIME);
}

void setup() {
  // put your setup code here, to run once:

  pinMode(PIN,OUTPUT);
  

}

void loop() {
  // put your main code here, to run repeatedly:

  Blink(PIN, DELTATIME);
}
