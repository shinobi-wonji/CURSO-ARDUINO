/*
 * Brazo 
 *
 */

#include <Servo.h>

/*
 * Definicion de secuencia de pasos.
 */
const int
stepsSequence[4][4] = // Dos bobinas a la vez, fuerza y consumo maximo.
{
   {1, 1, 0, 0},
   {0, 1, 1, 0},
   {0, 0, 1, 1},
   {1, 0, 0, 1}
};

/*
 * Ultima posicion util del array
 */
const int lastSequenceIndex = 3;

/*
 * Entero que dice en que punto de la 
 * sequencia me encuentro.
 */
int cstep = 0;

/*
 * Definicion de la conexion de pines.
 */
const int stepPin1 = 4;
const int stepPin2 = 5;
const int stepPin3 = 6;
const int stepPin4 = 7;

const int encoderPin1 = 2;
const int encoderPin2 = 3;
const int encoderSwitchPin = 8;

/*
 * Definicion de los servos utilizados.
 */
Servo elbowServo;
Servo shoulderServo;
Servo gripperServo;

const int elbowPin = 9;
const int shoulderPin = 10;
const int gripperPin = 12;

const int ledPin = 13;

/*
 * Definicion de la conversion de angulo.
 * Cada paso mueve 11.25° o (5.625° x micropaso
 * y a la vez tiene una reductora de 64
 * Sumado a la reduccion 22/50 de la base
 * que invierte el giro.
 */
const double stepAngle = -11.25/64*22/50;

/*
 * Tiempos que controlan la velocidad
 * de los movimientos en milisegundos.
 */
unsigned long lastStepTime = 0;
const long stepInterval = 2;

unsigned long lastServoTime = 0;
const long servoInterval = 25;

/*
 * Posiciones actuales.
 * (Tambien definen la posicion inicial.)
 */
int basePosition = 180;
int elbowPosition = 90;
int shoulderPosition = 90;
int gripperPosition = 90;

// Posiciones requeridas
int baseTarget = 180;
int elbowTarget = 90;
int shoulderTarget = 90;
int gripperTarget = 90;

// Pasos pendientes de la base.
int pendingSteps = 0;

// Indica si hay movimientos pendientes.
bool pendingMovement = false;

// Variable donde almaceno la ultima posicion del encoder.
volatile int lastEncoded = 0;
volatile int pendingEncoded = 0;

/*
 * Codigo principal.
 */

// Ejecuta un paso en la direccion indicada.
void stepperNext (int stepDirection)
{
  if (!stepDirection)
    return;

  if (stepDirection > 0)
    cstep++;
  else
    cstep--;

  if (cstep > lastSequenceIndex)
    cstep = 0;
  else if (cstep < 0)
    cstep = lastSequenceIndex;

  digitalWrite (stepPin1, stepsSequence[cstep][0]);
  digitalWrite (stepPin2, stepsSequence[cstep][1]);
  digitalWrite (stepPin3, stepsSequence[cstep][2]);
  digitalWrite (stepPin4, stepsSequence[cstep][3]);
}

void encoder_interrupt_handler ()
{
  int MSB = digitalRead(encoderPin1); // MSB = most significant bit
  int LSB = digitalRead(encoderPin2); // LSB = least significant bit

  int encoded = (MSB << 1) |LSB; //converting the 2 pin value to single number
  int sum  = (lastEncoded << 2) | encoded; //adding it to the previous encoded value

  if (sum == 0b1110 || sum == 0b0111 || sum == 0b0001 || sum == 0b1000) pendingEncoded++;
  if (sum == 0b1101 || sum == 0b0100 || sum == 0b0010 || sum == 0b1011) pendingEncoded--;

  lastEncoded = encoded; //store this value for next time
}

void setup()
{
  pinMode (stepPin1, OUTPUT);
  pinMode (stepPin2, OUTPUT);
  pinMode (stepPin3, OUTPUT);
  pinMode (stepPin4, OUTPUT);

  pinMode (encoderPin1, INPUT_PULLUP);
  pinMode (encoderPin2, INPUT_PULLUP);
  pinMode (encoderSwitchPin, INPUT_PULLUP);

  pinMode (ledPin, OUTPUT);

  attachInterrupt(digitalPinToInterrupt(encoderPin1), encoder_interrupt_handler, CHANGE);
  attachInterrupt(digitalPinToInterrupt(encoderPin2), encoder_interrupt_handler, CHANGE);

  elbowServo.attach(elbowPin);
  shoulderServo.attach(shoulderPin);
  gripperServo.attach(gripperPin);

  Serial.begin(9600);
  while (!Serial);

  elbowServo.write(elbowPosition);
  shoulderServo.write(shoulderPosition);
  gripperServo.write(gripperPosition);
}

void loop()
{
  char movement;
  unsigned long currentTime = 0;

  // Sin no hay movimientos pendientes, lee el puerto serial buscando nuevos movimientos.
  if (Serial.available())
  {
    movement = Serial.peek();
    switch (movement)
    {
      case 'b':
      case 'B':
        baseTarget = Serial.parseInt(); // Leo cual es el angulo requerido.
        if (baseTarget != basePosition) {
          pendingSteps = (baseTarget - basePosition)/stepAngle; // Lo convierto en pasos de la base.
          pendingMovement = true; // Indico que hay un movimiento pendiente.
        }
        break;
      case 'e':
      case 'E':
        elbowTarget = Serial.parseInt(); // Leo cual es el angulo requerido.
        if (elbowTarget != elbowPosition) // Si estoy en otra posicion..
          pendingMovement = true;         // Indico que hay otro movimiento pendiente.
        break;
      case 's':
      case 'S':
        shoulderTarget = Serial.parseInt();
        if (shoulderTarget != shoulderPosition)
          pendingMovement = true;
        break;
      case 'g':
      case 'G':
        gripperTarget = Serial.parseInt();
        if (gripperTarget != gripperPosition)
          pendingMovement = true;
        break;
      case 'l':
      case 'L':
        if (Serial.parseInt() > 0)
          digitalWrite(ledPin, HIGH);
        else
          digitalWrite(ledPin, LOW);
        break;
      default: // En cualquier otro caso esta fuera del protocolo e ignoro su contenido.
        Serial.println("Error: Fuera de sequencia");
        Serial.read();
        break;
    }
  }

  // Si rote el encoder tambien muevo la base.
  if (pendingEncoded) {
    baseTarget += pendingEncoded; // Divido por dos para mayor precision.
    pendingSteps = (baseTarget - basePosition)/stepAngle; // Lo convierto en pasos de la base.
    pendingMovement = true; // Indico que hay un movimiento pendiente.
    pendingEncoded = 0; // Vuelvo a cero el encoder.
  }

  // Si no hay movimiento y pulso el enconder, cosidero la posicion actual de la base como por defecto.
  if (!pendingMovement && (digitalRead(encoderSwitchPin) == LOW)) {
    baseTarget = basePosition = 180;
  }

  // Si no hay movimientos pendientes no ajecuto lo proximo.
  if (!pendingMovement)
    return;

  currentTime = millis();

  // Si paso el intervalo de los pasos controlo la base.
  if (currentTime - lastStepTime >= stepInterval)
  {
    // Si no esta en la posicion ideal muevo la base.
    if (basePosition != baseTarget)
    {
      // Ejecuto un movimiento.
      stepperNext (pendingSteps);

      // Descuento el movimiento.
      if (pendingSteps > 0)
        pendingSteps--;
      else
        pendingSteps++;
 
      // Si no quedan movimientos llegue a la posicion requerida.
      if (pendingSteps == 0)
        basePosition = baseTarget;
    }

    // Guardo el ultimo tiempo para hacer un movimiento uniforme.
    lastStepTime = currentTime;
  }

  // Si paso el intervalo de los servos ejecuto los movimientos.
  if (currentTime - lastServoTime >= servoInterval)
  {
    // Si la posicion del codo es diferente lo muevo para llegar al angulo requerido
    if (elbowTarget != elbowPosition)
    {
      // Muevo un grado en la posicion requerida.
      if (elbowTarget > elbowPosition)
        elbowPosition++;
      else
        elbowPosition--;

      elbowServo.write(elbowPosition); // Muevo el brazo para acercarnos a la posicion ideal.
    }

    if (shoulderTarget != shoulderPosition)
    {
      if (shoulderTarget > shoulderPosition)
        shoulderPosition++;
      else
        shoulderPosition--;

      shoulderServo.write(shoulderPosition);
    }
    if (gripperTarget != gripperPosition)
    {
      if (gripperTarget > gripperPosition)
        gripperPosition++;
      else
        gripperPosition--;

      gripperServo.write(gripperPosition);
    }

    // Guardo el ultimo tiempo para hacer un movimiento uniforme.
    lastServoTime = currentTime;
  }

  // Si estaba en movimiento y llegue a la posicion reporto a la aplicacion de escritorio.
  if (pendingMovement &&
      baseTarget == basePosition &&
      elbowTarget == elbowPosition &&
      shoulderTarget == shoulderPosition &&
      gripperTarget == gripperPosition)
  {
    pendingMovement = false;
    Serial.print("B");
    Serial.print(basePosition);
    Serial.print("E");
    Serial.print(elbowPosition);
    Serial.print("S");
    Serial.print(shoulderPosition);
    Serial.print("G");
    Serial.println(gripperTarget);
  }
}

