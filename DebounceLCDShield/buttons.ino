#include "new_types.h"
#include "settings.h"

unsigned long lastDebounceTime;
const int debounceDelay = 50;

KeyButton keyStatus = KEY_NONE;
KeyButton lastKeyReaded = KEY_NONE;
KeyButton lastKeyHandled = KEY_NONE;

/*
 * Funcion que solo devuelvo el boton presionado una unica vez
 * para controlar los menus que se muevan correctamene,
 * Por mas que siga apretando el boton, me muevo una unica vez en el menu.
 */

KeyButton get_key_debounced_unique (void)
{
  static KeyButton keyHandled = KEY_NONE;
  KeyButton currentButton = KEY_NONE, ret = KEY_NONE;

  currentButton = get_key_debounced();
  if (currentButton != keyHandled)
  {
    keyHandled = currentButton;
    ret = currentButton;
  }
  else
  {
    ret = KEY_NONE;
  }
  return ret;
}

static KeyButton get_key_debounced (void)
{
  KeyButton keyReaded = KEY_NONE;

  keyReaded = read_LCD_buttons ();

  /* Cada vez que cambia establezco un tiempo de referencia. */
  if (keyReaded != lastKeyReaded)
    lastDebounceTime = millis();

  /*
   * La primera vez esto es falso!!.
   * Cuando paso un tiempo y se hace verdadero,
   * Recien ahi verfica si cambio con respecto
   * a la ultima lectura y si es asi, considera que
   * realmente presiono o libero los botones.
   */
  if ((millis() - lastDebounceTime) > debounceDelay) {
    if (keyReaded != keyStatus)
       keyStatus = keyReaded;
  }

  lastKeyReaded = keyReaded;

  return keyStatus;
}

/*
 * Funcion que nos devuelve el estado de los botones
 * Esta funcion devuelve un tipo 'KeyButton' definido en 'new_types.h',
 * que correspondera a uno de los botones, indicando cual esta apretado
 * y no necesita ningun argumento.
 */
KeyButton read_LCD_buttons (void)
{
  /*
   * Los 4 botones estan conectados a una cadena de resistencias que al
   * presionar los pulsadores forman diferentes divisores de tension
   * (Ver el esquematico). Esto nos permite identificar los botones apretados
   * segun la tension aplicada en el pin.
   */  
  int adc_key_in = 0;
  adc_key_in = analogRead(analogButtonsPin);

  /*
   * Si no presiono ningun pulsador solo tengo una resistencia de pull-up a 5v
   * entonces idealmente adc_key_in = 1024
   */
  if (adc_key_in > 1000)
    return KEY_NONE;

  /*
   * Luego corroboro la tension aplicada, que segun el divisor de tension resultante
   * correspondiente a cada pulsador.
   */
  if (adc_key_in < 50)  return KEY_RIGHT;  
  if (adc_key_in < 195) return KEY_UP; 
  if (adc_key_in < 380) return KEY_DOWN; 
  if (adc_key_in < 555) return KEY_LEFT; 
  if (adc_key_in < 790) return KEY_SELECT;

  /*
   * Aunque parece consideramos todos los casos siempre se recomienda en la ultima linea
   * devolver un valor por defecto.
   */
  return KEY_NONE;
}
