#include <Keypad.h>

const byte rows = 4; //4 filas
const byte cols = 4; //4 columnas
char keys[rows][cols] = {
  {'1','2','3','A'},
  {'4','5','6','B'},
  {'7','8','9','C'},
  {'*','0','#','D'}
};
byte rowPins[rows] = {12, 11, 10, 9}; //primeros 4 pines del keypad son las filas
byte colPins[cols] = {8, 7, 6, 5}; //ultimos 4 pines del keypad son las columnas

Keypad MyKeypad = Keypad( makeKeymap(keys), rowPins, colPins, rows, cols ); //instancio el Keypad con la configuracion


void setup() {
  // put your setup code here, to run once:
  Serial.begin(9600);
}


void loop() {
  // put your main code here, to run repeatedly:
char keypressed = MyKeypad.getKey();
if (keypressed != NO_KEY)
{
Serial.print(keypressed);
}

}
