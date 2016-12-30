/*
  Web client
 
 This sketch connects to a website (http://www.google.com)
 using an Arduino Wiznet Ethernet shield. 
 
 Circuit:
 * Ethernet shield attached to pins 10, 11, 12, 13
 
 created 18 Dec 2009
 by David A. Mellis
 modified 9 Apr 2012
 by Tom Igoe, based on work by Adrian McEwen
 
 */

#include <SPI.h>
#include <Ethernet.h>

byte mac[] = { 0xDE, 0xAD, 0xBE, 0xEF, 0xFE, 0xED };

IPAddress server(192, 168, 250, 184);
//char server[] = "www.google.com";

IPAddress ip(192, 168, 250, 177);

EthernetClient client;


unsigned long lastConnectionTime = 0;          // last time you connected to the server, in milliseconds
boolean lastConnected = false;                 // state of the connection last time through the main loop
const unsigned long postingInterval = 5*1000;  // delay between updates, in milliseconds


// this method makes a HTTP connection to the server:
void httpRequest(double temp)
{
  // if there's a successful connection:
  if (client.connect(server, 5555)) // Hay que usar puerto 80, pero como hago una redireccion cambio de puerto..
  {
    Serial.println("connecting...");
    String sUrl = "";
    String sTemp = String(temp, 3);
    sTemp.replace(".", "%2E");
    sUrl += "GET /"; // El metodo que vamos a utilizar para hacer la llamada..
    sUrl += "api/"; // Vamos a utilizar la direccion nombre-host/api para comunicarnos con el servidor.
    sUrl += "123456/"; // Como metodo de seguridad basico, pasamos un key para identificar quien envia los datos.
    sUrl += "temp/";   // Vamos a hacer un PUT de la temperatura.
    sUrl += sTemp;     // Mandamos la temperatura.
    sUrl += " HTTP/1.0"; // Y estamos usando el protocolo HTTP version 1.0
    client.println(sUrl);
    //client.println("Host: www.some-host.com.ar"); // Como estamos usando este ejemplo con Ip, no mandamos el Host. 
    //client.println("User-Agent: ArduinoExample/1.0"); // El User-Agent define a quien esta haciendo la llamada, pero como producto no como usuario.
    //client.println("Connection: close"); // Cerramos la coneccion automaticamente.
    client.println(); // Vandamos la linea en blanco para finalizar el header..

    // Guardamos la ultima vez que hicimos la llamanda..
    lastConnectionTime = millis();
  } 
  else
  {
    // Si falla cerramos la coneccion..
    Serial.println("connection failed");
    Serial.println("disconnecting.");
    client.stop();
  }
}

void setup() {
  Serial.begin(9600);
   while (!Serial);

  if (Ethernet.begin(mac) == 0) {
    Serial.println("Failed to configure Ethernet using DHCP");
    Ethernet.begin(mac, ip);
  }

  Serial.print("My IP address: ");
  Serial.println(Ethernet.localIP());
}

void loop() {
  // Debug imprimiendo todas las respuestas.
  if (client.available()) {
    char c = client.read();
    Serial.print(c);
  }

  // if there's no net connection, but there was one last time
  // through the loop, then stop the client:
  // Si no esta conectado, 
  if (!client.connected() && lastConnected) {
    Serial.println();
    Serial.println("disconnecting.");
    client.stop();
  }

  // if you're not connected, and ten seconds have passed since
  // your last connection, then connect again and send data:
  if(!client.connected() && (millis() - lastConnectionTime > postingInterval))
  {
    httpRequest(analogRead(0)/2.0);
  }
  // store the state of the connection for next time through
  // the loop:
  lastConnected = client.connected();
}

