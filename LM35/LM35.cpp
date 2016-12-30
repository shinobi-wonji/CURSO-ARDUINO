#include "LM35.h" // Incluimos la clase LM35 que es la que definie el objeto.

#include "Arduino.h" // Agragamos las funciones basicas de arduino, como por ejemplo analogRead()

/*
 * Implementamos el metodo Constructor LM35 del objecto LM35
 * (Siempre llevan el mismo nombre)
 * Los "::" es la forma de definir los metodos de una clase
 * en c++.
 */
LM35::LM35(int mPin)
{
  /*
   * El constructor recibe lo que se envia al memento de
   * crear el objeto. Noten que "pin" parece que no existe,
   * pero esta definido como variable privada en la clase.
   * LM35.h linea 17
   * Esta variable al ser privada solo puede accederse desde
   * metodos del mismo objetos como este.
   */
  pin = mPin;
}

/*
 * Implementamos el metodo privado que devulve llamado measuremV
 * que devuelve la tension medida como float.
 * Es prievado por lo tanto no puede utilizarse puera de este archivo!.
 */
float LM35::measuremV()
{
  float retVal = (float) analogRead(pin); //Mido el pin analogico "pin" que tambien es privado.
  retVal = (retVal*5.0*1000L)/1023.0; // Calculo los mV
  return retVal; // Devuelvo el valor calculado.
}

/*
 * Implementamos el metodo publico measureC que devuelve la temperatura actual.
 */
float LM35::measureC()
{
  /*
   * tempc parece no estar definida, pero es una variable publica
   * de la clase LM35. Ver: LM35.h linea 15
   * Utilizo el metodo privado measuremV() para obtener la tension
   * y luegi calcular la temperatura.
   */
  tempc = measuremV()/10;
  return tempc; // Devolviemos el valor calculado.
}
