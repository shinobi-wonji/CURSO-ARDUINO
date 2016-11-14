/*
 * Ejemplo utilizacion Arduino LCD KeyPad Shield
 *
 * Conexiones LCD KeyPad Shield:
 *  LCD RS pin to digital pin 8
 *  LCD Enable pin to digital pin 9
 *  LCD D4 pin to digital pin 4
 *  LCD D5 pin to digital pin 5
 *  LCD D6 pin to digital pin 6
 *  LCD D7 pin to digital pin 7
 *
 *  LCD BL pin to digital pin 10
 *
 *  KEYS BUTTONS to analog pin 0
 *
 * Pines libres:
 *  Arriba: D13 D12 D11 D3 D2 D1 D0
 *  Abajo IZQ: RST 3.3V 5V GND GND VIN
 *  Abajo DER: A1 A2 A3 A4 A5
 */

/*
 * Primero debe incluirse la libreria LiquidCrystal.h. Luego creamos un objeto
 * publico (Por que esta fuera de la funcion setup o loop), del tipo LiquidCrystal,
 * al cual llamamos lcd, donde le indicamos como se encuentra conectado.
 *
 * Mas informacion: http://arduino.cc/en/Reference/LiquidCrystal
 */
#include <LiquidCrystal.h>
LiquidCrystal lcd(8, 9, 4, 5, 6, 7);

/*
 * Macros para 
 */
#define btnRIGHT  0
#define btnUP     1
#define btnDOWN   2
#define btnLEFT   3
#define btnSELECT 4
#define btnNONE   5

int
read_LCD_buttons (void)
{
  int adc_key_in  = 0;

  /*
   * Los 4 botones estan conectados a una resistencia encadenada,
   * que simulan un potenciomentro, usado como un divisor de tension.
   */
  adc_key_in = analogRead(0);

  if (adc_key_in > 1000)
    return btnNONE;

  if (adc_key_in < 50)  return btnRIGHT;  
  if (adc_key_in < 195) return btnUP; 
  if (adc_key_in < 380) return btnDOWN; 
  if (adc_key_in < 555) return btnLEFT; 
  if (adc_key_in < 790) return btnSELECT;   

  return btnNONE;
}

void
setup (void)
{
  /*
   * Seteo el pin digital 10 como salida, y le doy una señal alta,
   * para activar la luz de fondo.
   */
  pinMode(10, OUTPUT);
  digitalWrite(10, HIGH);

  /*
   * Inicializa la libreria de la pantalla LCD especificando sus dimenciones.
   * Luego se coloca el cursor en el primer catacter (Arriba a la izquierda),
   * y finalmente se escribe en esta posicion un mensaje.
   */
  lcd.begin(16, 2);
  lcd.setCursor(0,0);
  lcd.print("Push the buttons");
}

void
loop(void)
{
  int lcd_key = 0;

  lcd.setCursor(9,1);
  lcd.print(millis()/1000);

  lcd.setCursor(0,1);

  lcd_key = read_LCD_buttons();

  switch (lcd_key)
  {
  case btnRIGHT:
    {
      lcd.print("RIGHT ");
      break;
    }
  case btnLEFT:
    {
      lcd.print("LEFT   ");
      break;
    }
  case btnUP:
    {
      lcd.print("UP    ");
      break;
    }
  case btnDOWN:
    {
      lcd.print("DOWN  ");
      break;
    }
  case btnSELECT:
    {
      lcd.print("SELECT");
      break;
    }
  case btnNONE:
  default:
    {
      lcd.print("NONE  ");
      break;
    }
  }
  delay (50);
}

