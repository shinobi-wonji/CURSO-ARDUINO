#include <LiquidCrystal.h> // uso libreria de LCD
#include <Keypad.h> // uso libreria de Keypad

const byte rows = 4; //4 filas
const byte cols = 4; //4 columnas
char keys[rows][cols] = { 
  {'1','2','3','A'},
  {'4','5','6','B'},
  {'7','8','9','C'},
  {'*','0','#','D'}
}; // cargo la matriz con la config del keypad

byte rowPins[rows] = {13, 10, 9, 8}; //primeros 4 pines del keypad son las filas
byte colPins[cols] = {7, 6, 1, 0}; //ultimos 4 pines del keypad son las columnas

Keypad MyKeypad = Keypad( makeKeymap(keys), rowPins, colPins, rows, cols ); //instancio el Keypad con la configuracion de arriba indicada

LiquidCrystal lcd(12, 11, 5, 4, 3, 2); //incializo el display con los pines 12 11 5 4 3 2

void setup() {
  
  lcd.begin(16, 2); //configuro el display con 16 columnas y 2 lineas
  lcd.setCursor(0, 0); //seteo el cursor en linea 0 columna 0
}

void loop() {
  char keypressed = MyKeypad.getKey(); // Uso funcion getkey y guardo en variable keypressed
  if (keypressed != NO_KEY) // Si se apreta una tecla entra en el IF
  {
    if (keypressed == '*') // Si la tecla apretada es el asterisco entonces entra en el Sub IF
    {
        lcd.clear();  //borro pantalla
        lcd.setCursor(0, 0); // situo el curso en 0 0 otra vez
    }
    else
    {
      lcd.print(keypressed);  //mando la tecla que se apreto al display
    }
  }  
}
