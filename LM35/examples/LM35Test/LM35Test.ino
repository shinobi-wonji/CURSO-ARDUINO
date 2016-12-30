#include "LM35.h"  // Incluimos la clase LM35 que es la que definie el objeto y sus metodos.

//#include "LM35.h"  // Sin la guarda de inclusion si decomentan esta linea el ejemplo devolveria error.

// Creo un objeto LM35 llamado mTemp, y le paso al constructor el Pin a utilizar.
LM35 mTemp(A1);

void setup()
{
  Serial.begin(9600);
}

void loop()
{
  /*
   * Calculo la temperatura utilizando el metodo publico measureC() y la imprimo.
   * VER: LM35.h linea 14 y LM35.cpp linea 
   */
  Serial.println("Temperatura: ");
  Serial.println(mTemp.measureC());

  /*
   * Puedo obtener la ultima temperatura utilizando la variable publica tempc
   * Ver: LM35.h linea 15
   */
  Serial.println("Temperatura: ");
  Serial.println(mTemp.tempc);

  /*
   * Si quisiera utilizar un metodo privado devuelve un error.
   * prueven decomentar lo siguiente y luego convertir el metodo
   * measuremV para que sea publico en la clase.
   */
  //Serial.println("Tension: ");
  //Serial.println(mTemp.measuremV());

  /*
   * De la misma forma si quisiera leer o modificar el pin donde estoy midiendo
   * la temperatura devolveria un error porque 'pin' esta definido de forma privada.
   * Prueven decomentar lo siguente y luego hacerlo publico si quieren en la clase.
   */
  //mTemp.pin = A2;

  delay(1000);
}

