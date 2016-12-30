/*
 * Hago un nuevo tipo de dato enumerado (KEY_NOTE = 0, KEY_RIGHT = 1,..,KEY_SELECT = 5)
 * Le asigno el nombre KeyButton que nos permitira utilizarlo con este nombre como si fuera
 * un nuevo tipo de dato.
 * Una vez definido se utilizan de la misma forma que el resto de las variables.
 *
 * Se definen como:
 *  tipoVariable nombreVariable = valorInicial;
 * 
 * Por ejemplo:
 *  KeyButton boton = KEY_NONE;
 */

#ifndef NEW_TYPES_h
#define NEW_TYPES_h

enum KeyButton {
 KEY_NONE = 0,
 KEY_RIGHT,
 KEY_UP,
 KEY_DOWN,
 KEY_LEFT,
 KEY_SELECT
};


/*
 * Tambin creo una nuevo tipo de datos que enumerara los
 * los estados validos de nuestro problema. En este caso tres
 * estados que representan las tres pantallas del ejercicio.
 */
enum Stado {
  STATE_CURRENT = 0,
  STATE_MAX_MIN,
  STATE_SET_TEMP
};

#endif //NEW_TYPES_h
