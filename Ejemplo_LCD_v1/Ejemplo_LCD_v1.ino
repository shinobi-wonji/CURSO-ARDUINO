#include <LiquidCrystal.h>
#include <Keypad.h>

const byte rows = 4; //4 filas
const byte cols = 4; //4 columnas
char keys[rows][cols] = {
  {'1','2','3','A'},
  {'4','5','6','B'},
  {'7','8','9','C'},
  {'*','0','#','D'}
};
byte rowPins[rows] = {13, 10, 9, 8}; //primeros 4 pines del keypad son las filas
byte colPins[cols] = {7, 6, 1, 0}; //ultimos 4 pines del keypad son las columnas

Keypad MyKeypad = Keypad( makeKeymap(keys), rowPins, colPins, rows, cols ); //instancio el Keypad con la configuracion


// initialize the library with the numbers of the interface pins
LiquidCrystal lcd(12, 11, 5, 4, 3, 2);

void setup() {
  // set up the LCD's number of columns and rows:
  lcd.begin(16, 2);
  // Print a message to the LCD.
  lcd.print("hello, world!");
}

void loop() {
  
  char keypressed = MyKeypad.getKey();
  if (keypressed != NO_KEY)
  lcd.print(keypressed);
  
  // set the cursor to column 0, line 1
  // (note: line 1 is the second row, since counting begins with 0):
  lcd.setCursor(0, 1);
  // print the number of seconds since reset:
  lcd.print(millis() / 1000);
}
