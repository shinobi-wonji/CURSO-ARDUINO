/*
 * Ejemplo utilizacion LCD Shield
 *
 * Conexiones DHT22 (Visto de frente, de izquiera a derecha)
 *
 * DHT22, pin 1, to 5V
 * DHT22, pin 2, to digital pin 2 (A eleccion)
 * DHT22, pin 3, No coneccted
 * DHT22, pin 4, to ground.
 *
 * Connect a 10K resistor from pin 2 (data) to pin 1 (power) of the sensor.
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
 *  Arriba: D13 D12 D11 D3 D1 D0
 *  Abajo IZQ: RST 3.3V 5V GND GND VIN
 *  Abajo DER: A1 A2 A3 A4 A5
 */

/*
 * Incluyo las librerias arduino qque utilizaremos.
 */
#include <LiquidCrystal.h>

/*
 * Incluyo el archivo donde defino nuestro nuevo tipo de dato. (Ver mas abajo)
 */
#include "new_types.h"

/*
 * Incluyo el archivo donde defino las conecciones y  y otras configuraciones como el debug
 */
#include "settings.h"

/*
 * Un numero que modificaremos con los botones y mostraremos en al pantalla.
 */
bool blStatus = false;

Stado lcdStado = STATE_A;

unsigned long lastLcd = 0;

int numero = 0;

/*
 * Inicializamos los objetos que utilizaremos.
 * Un 'LiquidCrystal' llamado 'lcd' conectado segun lo definido en 'settings.h'
 */
LiquidCrystal lcd(rsLcdPin, enableLcdPin,
                  d4LcdPin, d5LcdPin, d6LcdPin, d7LcdPin);


/*
 * Inicializacion de nuestro proyecto..
 */
void setup (void)
{
/*
 * Si esta definido DEBUG (Ver archivo 'settings.h')
 * Inicio el puerto serial para imprimir mensajes.
 */
#ifdef DEBUG
  Serial.begin (9600);
  while (!Serial);
#endif

  /*
   * Inicializo el objeto lcd indicandole que es una pantalla de 16x2
   * Posiciono el cursor arriba a la izquierda y escribo un texto.
   */
  lcd.begin(16, 2);
  lcd.setCursor(0,0);
  lcd.print("Pantalla A");

  /* Enciendo el blacklight */
  pinMode(lcdBlackLight, OUTPUT);
  digitalWrite(lcdBlackLight, HIGH);
  blStatus = true;
}

/*
 * Codigo principal
 */
void loop (void)
{
  /*
   * Creo una nueva variable del tipo KeyButton
   * cuyo tipo esta definido en el archivo 'new_types.h'
   */
  KeyButton buttonState = KEY_NONE;
 
 unsigned long currentLcd = 0;

 
  /*
   * Obtengo el estado del boton.
   *
   * Esta funcion realiza el debounce para evitar el ruido de los botones.
   * y devuelve solo una vez cuando precionamon el pulsador.
   * (Si mantenemos presionado el pulsador  UP solo una vez va informar
   * la tecla de forma que paresca que presionamos muchas veces el pulsador
   * cuando todavia no soltamos el pulsados.)
   */
  buttonState = get_key_debounced_unique ();

  /*
   * Segun la tecla presionada modifico el nro e informo en el LCD
   * o prendo y apago el blackligh del lcd con la tecla SELECT.
   */
  switch (buttonState)
  {
    case KEY_RIGHT:
      if (lcdStado == STATE_A)
        lcdStado = STATE_B;
      else if (lcdStado == STATE_B)
        lcdStado = STATE_C;
      else if (lcdStado == STATE_C)
        lcdStado = STATE_A;      
      lcd.clear();
      break;
    case KEY_LEFT:
      if (lcdStado == STATE_C)
        lcdStado = STATE_B;
      else if (lcdStado == STATE_B)
        lcdStado = STATE_A;
      else if (lcdStado == STATE_A)
        lcdStado = STATE_C;
      lcd.clear();
      break;
    case KEY_UP:
      if (lcdStado == STATE_A) {
        digitalWrite(lcdBlackLight, HIGH);
        blStatus = true;
      }
      else if (lcdStado == STATE_C)
        numero++;
      lcd.clear();
      break;
    case KEY_DOWN:
      if (lcdStado == STATE_A) {
        digitalWrite(lcdBlackLight, LOW);
        blStatus = false;
      }
      else if (lcdStado == STATE_C)
        numero--;
      lcd.clear();
      break;
    case KEY_SELECT:
      if (blStatus) {
        digitalWrite(lcdBlackLight, LOW);
        blStatus = false;
      }
      else {
        digitalWrite(lcdBlackLight, HIGH);
        blStatus = true;
      }
      break;
    case KEY_NONE:
    default:
      break;
  }

  currentLcd = millis();
  if (currentLcd - lastLcd > 200) {
    switch (lcdStado)
    {
      case STATE_A:
        lcd.setCursor(0, 0);
        lcd.print("HOLA MUNDO");
        break;
      case STATE_B:
        lcd.setCursor(0, 0);
        lcd.print("Temporizador");
        lcd.setCursor(0, 1);
        lcd.print(millis()/1000);
        break;
      case STATE_C:
        lcd.setCursor(0, 0);
        lcd.print("Modifica el Nro.");
        lcd.setCursor(0, 1);
        lcd.print(numero);
        break;
      default:
        break;
    }
  }
  /*
   * Si existe la definicion de DEBUG
   * Imprimo el nro en el puerto serial como debug..
   */
#ifdef DEBUG
  //Serial.print("Numero ");
  //Serial.println(numero);
#endif
}

