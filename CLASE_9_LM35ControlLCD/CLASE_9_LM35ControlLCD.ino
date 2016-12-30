/*
 * Ejemplo utilizacion del LCD Shield implementando un menu basico.
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
 * La idea es implementar tres pantallas, una pantalla A, otra B y otra C
 *
 * Usando las teclas LEFT y RIGHT nos desplazamos entre las tres pantallas.
 *
 * Cuando estamos en la pantalla A solo muestra un mensaje "Hola Mundo", y presionando la tecla UP
 * encendemos la luz de fondo, y con la tecla DOWN apagamos la pantalla.
 * Estando en la pantalla B muestra el texto "Temporizador" y abajo el tiempo transcurrido desde
 * inicio el arduino. En esta pantalla UP y DOWN no hacen nada.
 * En la pantalla C muestra el texto "Modifica el nro." un numero abajo que modificaremos con las
 * teclas UP y DOWN.
 * Finalmente independientemente de la pantalla donde me encuentro la tecla SELECT alterna el estado
 * de la luz de fondo.
 *
 * Esto lo logramos implementando una pequeña maquina de estados:
 * Lo fundamental es identifacar en que estado (Pantalla) me encuentro, y de acuedo a ello realizar
 * las tareas necesarias para el funcionamiento del estado (En este caso escribir el la pantalla)
 * lo que corresponda.
 * Luego hay que identificar cuales eventos cambian la maquina de estados, (en este caso los
 * pulsadores) y actuar en consecuencia..
 */

/*
 * Incluyo las librerias arduino que utilizaremos.
 */
#include <LiquidCrystal.h>

/*
 * Incluyo el archivo donde defino nuestros nuevo tipo de dato.
 */
#include "new_types.h"

/*
 * Incluyo el archivo donde defino las conecciones y  y otras configuraciones como el debug
 */
#include "settings.h"

#include "LM35.h"

/*
 * En "new_type" cree un nuevo tpo de datos llamando Stado, que puede ser STATE_A, STATE_B
 * o STATE_C.
 * Esta variable es la que almacena en que estado (Pantalla) me encuentro.
 */
Stado lcdStado = STATE_CURRENT;

/*
 * No es necesario escribir continuamente la pantalla.
 * Lo hacemos solo cada 200 ms.
 */
unsigned long lastLcd = 0;
const unsigned long lcdInterval = 200;

/*
 * Una variable donde almacenamos si el blacklight esta encendido o apagado.
 */
bool blStatus = false;

/*
 * Un numero que modificaremos con los botones y mostraremos en al pantalla C.
 */
double temp_control = 24.0;

LM35 sensor(A0);

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
   */
  lcd.begin(16, 2);

  /* Configuro y enciendo el blacklight */

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
   * Segun la tecla presionada tengo que actuar de acuerdo al estado (Pantalla)
   */
  switch (buttonState)
  {
    /*
     * Tanto RIGH y LEFT mueven de una pantalla de un estado a otro.
     * Esto se solamente realiza cambiendo la variable lcdStado.
     */
    case KEY_RIGHT:
      if (lcdStado == STATE_CURRENT)
        lcdStado = STATE_MAX_MIN;
      else if (lcdStado == STATE_MAX_MIN)
        lcdStado = STATE_SET_TEMP;
      else if (lcdStado == STATE_SET_TEMP)
        lcdStado = STATE_CURRENT;
      /*
       * Cuando cambia cualquier estado limpio la pantalla
       * para evitar que quede algun caracter de fondo.
       * Igualmente cada 200ms vuelve a refrescarse.
       */
      lcd.clear();
      break;
    case KEY_LEFT:
      if (lcdStado == STATE_SET_TEMP)
        lcdStado = STATE_MAX_MIN;
      else if (lcdStado == STATE_MAX_MIN)
        lcdStado = STATE_CURRENT;
      else if (lcdStado == STATE_CURRENT)
        lcdStado = STATE_SET_TEMP;
      lcd.clear();
      break;
    case KEY_UP:
      /*
       * La tecla UP enciende el blaclight en el estado A
       * y eleva el nro en la pantalla C. No hace nada en la B.
       */
      if (lcdStado == STATE_CURRENT) {
        digitalWrite(lcdBlackLight, HIGH);
        blStatus = true;
      }
      else if (lcdStado == STATE_SET_TEMP)
        temp_control+=0.5;
      lcd.clear();
      break;
    case KEY_DOWN:
      /*
       * La tecla DONWN apaga el blaclight en el estado A
       * y disminulle el nro en la pantalla C. No hace nada en la B.
       */
      if (lcdStado == STATE_CURRENT) {
        digitalWrite(lcdBlackLight, LOW);
        blStatus = false;
      }
      else if (lcdStado == STATE_SET_TEMP)
        temp_control-=0.5;
      lcd.clear();
      break;
    case KEY_SELECT:
#ifdef DEBUG
      if (lcdStado == STATE_SET_TEMP) {
        Serial.print("SET_TEMP:");
        Serial.println(temp_control);
      }
#endif
      break;
    case KEY_NONE:
    default:
      break;
  }

  /*
   * Esta es la ejecucion de la maquina de estados.
   * En este caso la maquina de estados solo se encarga de
   * gestionar la pantalla LCD, y de acuerdo al estado donde
   * escribe lo necesario cada 200 ms.
   */
  currentLcd = millis();
  if (currentLcd - lastLcd > lcdInterval)
  {
    switch (lcdStado)
    {
      case STATE_CURRENT:
        lcd.setCursor(0, 0);
        lcd.print("TEMP. ACTUAL");
        lcd.setCursor(0, 1);
        lcd.print(sensor.measureC());
        break;
      case STATE_MAX_MIN:
        lcd.setCursor(0, 0);
        lcd.print("Historicos:");
        lcd.setCursor(0, 1);
        break;
      case STATE_SET_TEMP:
        lcd.setCursor(0, 0);
        lcd.print("Temp. de control:");
        lcd.setCursor(0, 1);
        lcd.print(temp_control);
        break;
      default:
        break;
    }
    lastLcd = currentLcd;
  }

  /*
   * Si existe la definicion de DEBUG
   * Nuestras variables de estado canda 500 ms.
   */
#ifdef DEBUG
  if (currentLcd - lastLcd > lcdInterval)
  {
    Serial.print("Estado: ");
    Serial.print((int)lcdStado);
    Serial.print("/ Temp control: ");
    Serial.println(temp_control);
  }
#endif
}

