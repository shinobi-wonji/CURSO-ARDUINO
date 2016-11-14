/*
   Relacion de los pines del modulo:

     [LCD] <-> [PCF8574]
    1  VSS <-> GND
    2  VDD <-> VCC
    3  V0  <-> *POTENCIOMETRO
    4  RS  <-> P0
    5  RW  <-> P1
    6  E   <-> P2
    7  D0  <-> ?
    8  D1  <-> ?
    9  D2  <-> ?
    10 D3  <-> ?
    11 D4  <-> P4
    12 D5  <-> P5
    13 D6  <-> P6
    14 D7  <-> P7
    15 A   <-> *JUMPER A VCC
    16 K   <-> *GND <-> NPN <-> P3

   Se observa que podemos utilizar libremente los pines
   P0, P1, P2 y P4, P5, P6 y P7.

   Vamos a utilizar los pines los Pines P0, P1 y P2 como
   entradas y reflejaremos su estado en los pines P4, P5
   y P6.

*/

/*
   Incluimos la libreria Wire que no es parte del
   core de Arduino.
*/
#include <Wire.h>

/*
   La direccion principal del dispositivo es 0x40
*/
#define PC_M_ADDRESS 0x20

/*
   La direccion principal se complementa con una
   modificable con los jumpers de la placa.
*/
#define PC_H_ADDRESS 0x07

/*
   La direccion con la que nos comunicamos es la
   union de ambos.
*/
#define PC_ADDRESS PC_M_ADDRESS | PC_H_ADDRESS

/*
   Por defecto se escribe en los puertos. Cuando
   queremos leer tambien tenesmos que hacer 1
   el ultimo bit, y escribir 1 a los pines que son
   entradas.
*/
#define PC_READ_MASK 0x01

/* Mascaras para definir las entras y las salidas. */
#define INPUT_MASK 0x07
#define OUTPUT_MASK 0x70

void
setup()
{
  /*
     Inicializo la libreria Wire que nos da el
     soporte al los dispositivos i2c utilizando
     los pines A4 y A5 como SDA y SCL respectivamente.
  */
  Wire.begin();

  /*
     Debemos configurar las entradas como pull up
     y esto se realiza ponendo es estado alto los
     los pines correspondientes.
  */
  Wire.beginTransmission(PC_ADDRESS); // Iniciamos la cominicacion con el esclavo.
  Wire.write(INPUT_MASK); // h'07' -> b'00000111' Los primeros 3 pines como entradas con pull up.
  Wire.endTransmission(); // Terminamos la comunicacion.
}

void
loop()
{
  byte input = 0, output = 0;

  /* Vamos a leer los el estado de los pines. */

  /*
     Pedimos 1 byte informacion a la direccion PC_ADDRESS | PC_READ_MASK
     y enviamos el mensaje de stop para cerrar la comunicacion automaticamente.
  */
  Wire.requestFrom(PC_ADDRESS, 1, true);

  /* Verfificamos que este la respuesta. */
  while (Wire.available())
  {
    /*
       La respuesta es un byte que representa el estado de tension
       de todos los pines (Tanto las entradas como las salidas.)
       Aplico la mascara para ignorar los pines utilizados como
       salidas.
    */
    input = INPUT_MASK & Wire.read();
  }

  /*
     Vamos a escribir los mismo que leimos a la salida.
     Los pudemos mover los bits de la entrada 4 veces a la
     izquierda, y hay que recordar poner en estado alto los
     bits que utilizamos como entradas.
  */
  output = input << 4 | INPUT_MASK;

  Wire.beginTransmission(PC_ADDRESS); // Iniciamos la escritura.
  Wire.write(output); // Escribimos.
  Wire.endTransmission(); // Cerramos la comunicacion.
}


