/*
 * Ejemplo Arduino Ethernet Shield.
 */

#include <SPI.h>
#include <Ethernet.h>

/*
 * Creo un array de bytes que representa la direccion MAC que utilizara nuestro arduino.
 * Este debe ser un identificador unico a nivel mundial, pero como primer ejemplo utilizaremos
 * el mismo que casi todos los ejemplos.
 */
byte mac[] = { 0xDE, 0xAD, 0xBE, 0xEF, 0xFE, 0xED };

/*
 * Creamos el objeto servidor Ethernet.
 * Se pasa como argumento el puerto que escuchara. (80 es el valor por defecto para HTTP)
 */
EthernetServer server(80);

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
}


void
loop (void)
{
  /*
   * Escuchamos el puerto 80 para responder peticiones.
   */
  EthernetClient client = server.available();
  if (client)
  {
    Serial.println("New client");

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

        if (c == '\n' && currentLineIsBlank)
        {
          /*
           * Enviamos una cabecera estandar.
           */
          client.println("HTTP/1.1 200 OK");
          client.println("Content-Type: text/html");
          client.println("Connection: close");
	  client.println("Refresh: 5");
          client.println();

          /*
           * Enviamos la pagina web.
           */
          client.println("<!DOCTYPE HTML>");
          client.println("<html>");
          client.println("Nuestra primera pagina web con arduino!. =)");
          client.println("</html>");
          break;
        }

        /*
         * Detectamos lalinea en blanco.
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
    Serial.println("client disconnected");
  }
}

