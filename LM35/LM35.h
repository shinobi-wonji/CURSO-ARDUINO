/*
 * El arhivo .h define la funciones, y obejtos con los que podemos trabajar en arduino.
 * En este caso, definimos una clase llamada LM35 (La clase es el "equeleto" del objeto LM35)
 * Donde definimos 
 */

#ifndef LM35_h // Esto se llama guarda de inclusion.
#define LM35_h // Nos permite  agregar varias veces el archivo LM35.h y que solo se agregue una vez sin error.

class LM35 // Defino la classe
{
  public: // Defino los metodos y variables publicas del objeto LM35
    LM35(int mPin); // Este es el metodo CONSTRUCTOR del objeto que se llama solo cuando definimos el objeto
    float measureC(); // Esta es el metodo publico que devulve la temperatura actual.
    int tempc; // Esta es la variable publica que contiene la temperatura actual
  private: // Defino los metodos y variables privadas. Estas solo pueden utilizarse dentro del mismo objeto, pero no desde arduino.
    int pin; // El pin de configuracion es privado. Una vez que se define el objeto no le importa al programador.
    float measuremV(); // este metodo privado calcula la tension en mV. Se utiliza internamente para medir la tension, pero al programador final no le importa. Solo le interesa la temperatira, no la tension.
};

#endif // Fin guarda de inlucion.
