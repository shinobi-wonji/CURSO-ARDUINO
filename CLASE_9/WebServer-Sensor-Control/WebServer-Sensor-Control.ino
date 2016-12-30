/*
 * Ejemplo Arduino Ethernet Shield con sensor de temperatura.
 *
 * Conexiones DHT22 (Visto de frente, de izquiera a derecha)
 *
 * DHT22, pin 1, to 5V
 * DHT22, pin 2, to digital pin 2 (A eleccion)
 * DHT22, pin 3, No coneccted
 * DHT22, pin 4, to ground.
 *
 * Connect a 10K resistor from pin 2 (data) to pin 1 (power) of the sensor.
 */

#include <SPI.h>
#include <Ethernet.h>

/*
 * Vamos a leer la temperatura.
 */
#include "DHT.h"

/*
 * Creo un array de bytes que representa la direccion MAC que utilizara nuestro arduino.
 * Este debe ser un identificador unico a nivel mundial, pero como primer ejemplo utilizaremos
 * el mismo que casi todos los ejemplos.
 */
byte mac[] = { 
  0xDE, 0xAD, 0xBE, 0xEF, 0xFE, 0xED };

/*
 * Creamos el objeto servidor Ethernet.
 * Se pasa como argumento el puerto que escuchara. (80 es el valor por defecto para HTTP)
 */
EthernetServer server(80);

/*
 * Conectamos un DHT22 al pin 2.
 */
DHT dht(2, DHT22);
float h = 0.0, t = 0.0;
unsigned long previousMillis = 0;

/*
 * Conectamos un ventilador en el pin 3.
 */
const int fanPin = 4;

void
setup (void)
{
  Serial.begin(9600);

  /*
   * Inicializamos la libreria pasando como argumento la direccion MAC que indentifica nuestra coneccion.
   * Sin mas argumentos intenta estableces la una ip dinamica.
   */
  if (Ethernet.begin (mac))
  {
    Serial.print("Connected as DHCP: ");
  }
  else
  {
    /*
     * Creamos un objeto Ip para establecer una coneccion con ip fija.
     */
    IPAddress ip(192,168,1,177);
    Ethernet.begin (mac, ip);
  }

  /*
   * Inicializamos nuestro servidor.
   */
  server.begin();

  Serial.print("server is at ");
  Serial.println(Ethernet.localIP());

  /*
   * Inicializamos el sensor DHT22
   */
  dht.begin();

  /*
   * Configuarmos el pin del ventilador como salida
   */
  pinMode (fanPin, OUTPUT);
}


void
loop (void)
{
  /*
   * Actualizaremos la temperatura y humedad cada dos segundos.
   */
  unsigned long currentMillis = millis();
  if (currentMillis - previousMillis >= 2000)
  {
    t = dht.readTemperature();
    h = dht.readHumidity();

    previousMillis = currentMillis;   

    if (isnan(h) || isnan(t))
      return;
  }

  /*
   * Escuchamos el puerto 80 para responder peticiones.
   */
  EthernetClient client = server.available();
  if (client)
  {
    Serial.println("New client");

    /*
     * Vamos a guardar la cabecera para analizarla luego.
     */
    String cabecera="";

    /*
     * Bandera para detectar el fin de linea. Las peticiones http terminan de esta forma.
     */
    boolean currentLineIsBlank = true;

    /*
     * Si se detecta un nuevo cliente, y mientras haya texto, leemos caracter a caracter y lo imprimimos como debug.
     * Cuando encutra el fin de linea es que termino la cabecera, y podemos responder a la peticion.
     */
    while (client.connected())
    {
      if (client.available())
      {
        char c = client.read();
        Serial.write(c);

        /*
         * Concatenamos caracter a caracter para tener guardada la cabecera.
         */
        cabecera.concat(c);

        if (c == '\n' && currentLineIsBlank)
        {
          /*
           * Primero buscamos la pocicion del texto que configura el led.
           * y luego comparamos el texto, y actuamos en consecuencia.
           */
          if (cabecera.indexOf("FAN=ON") > 0)
            digitalWrite(fanPin, HIGH);
          else if (cabecera.indexOf("FAN=OFF") > 0)
            digitalWrite(fanPin, LOW);

          /*
           * Enviamos una cabecera estandar.
           */
          client.println("HTTP/1.1 200 OK");
          client.println("Content-Type: text/html");
          client.println("Connection: close");
          client.println("Refresh: 30");
          client.println();

          /*
           * Enviamos la pagina web.
           */
          client.println("<!DOCTYPE HTML>");
          client.println("<html>");
          client.println("Condiciones methorologicas en el aula 6<br><br>");
          client.print("Humedad: ");
          client.println(h);
          client.print("<br>Temperatura: ");
          client.print(t);
          client.println(" *C<br><br>");
          client.println("Ventilador: ");

          if (!digitalRead(fanPin))
            client.println("<button onClick=\"location.href='/?FAN=ON'\">Encender Ventilador</button><br>");
          else
            client.println("<button onClick=\"location.href='/?FAN=OFF'\">Apagar Ventilador</button><br>");

          client.println("</html>");
          break;
        }

        /*
         * Detectamos la linea en blanco.
         */
        if (c == '\n')
          currentLineIsBlank = true;
        else if (c != '\r')
          currentLineIsBlank = false;
      }
    }

    /*
     * Esperamos un tiempo minimo para que el servidor responda.
     */
    delay(1);

    /*
     * Cerramos el conector.
     */
    client.stop();
    cabecera="";
    Serial.println("client disconnected");
  }
}


