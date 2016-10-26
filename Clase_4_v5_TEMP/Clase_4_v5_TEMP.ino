const int lmPin = A0;

void setup() {
  // put your setup code here, to run once:
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
  delay(300);
  
}
