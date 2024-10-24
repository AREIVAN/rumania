#include <Arduino.h>

#define LINE_B A7  // IZQUIERDO A
#define LINE_A A2  // DERECHO A5
#define RIGHT A2   // a1
#define FRONT_A A4 // ENFRENTE DERECHP2
#define FRONT_B A5 // ENFRENTE IZQUIERDO1 a3v
#define LEFT A6
// #define SERVO 3 // servo izquierda
// #define Servo 10  //servo derecha si fu nciona bien
#define Mder1 11 // motor1 derechawbn1
#define Mder2 5  // MOTOR 1 IZQUIERDA bni
#define Mizq1 10
#define Mizq2 9
const int buttonPin = 7; // the number of the pushbutton pinc      4

#define REMOTE 2 // 12

int ledRojo = 0;
int ledVerde = 30;
int ledAzul = 1;

int initial = 0;     // hold current  initial
int oldstate = 0;    // hold last  initial
int buttonstate = 0; // variable for reading the pushbutton status

int sensorState;
int lineState;

void setup()
{

  pinMode(LINE_A, INPUT);
  pinMode(LINE_B, INPUT);
  pinMode(RIGHT, INPUT);
  pinMode(LEFT, INPUT);
  pinMode(FRONT_A, INPUT);
  pinMode(FRONT_B, INPUT);
  pinMode(Mizq1, OUTPUT);
  pinMode(Mizq2, OUTPUT);
  pinMode(Mder1, OUTPUT);
  pinMode(Mder2, OUTPUT);
  pinMode(REMOTE, INPUT);
  pinMode(buttonPin, INPUT); // initialize the pushbutton pin as an input:
  pinMode(ledRojo, OUTPUT);
  pinMode(ledVerde, OUTPUT);
  pinMode(ledAzul, OUTPUT);

  Serial.begin(9600);
  Serial.println("Starting booting sequence...");
  delay(500);
}
// --------------- Funciones de sensores --------------- .

int sensorValue()
{
  int sens1 = digitalRead(FRONT_A) * 1; // enfrente derecho
  int sens2 = digitalRead(FRONT_B) * 2;
  int sens3 = !digitalRead(RIGHT) * 4;
  int sens4 = digitalRead(LEFT) * 8;
  int total = sens1 + sens2 + sens3 + sens4;
  return total;
}

int lineValue()
{
  int line1 = digitalRead(LINE_A) * 1; //  derecho
  int line2 = digitalRead(LINE_B) * 2; // izquierdo

  int total = line1 + line2;
  return total;
}

// --------------- Funciones de motores --------------- .

void adelante(int potenciaDerecha, int potenciaIzquierda)
{
  // las potencias pueden tener un valor entre 1 y 255

  analogWrite(Mder1, potenciaDerecha);
  digitalWrite(Mder2, LOW);
  analogWrite(Mizq1, potenciaIzquierda);
  digitalWrite(Mizq2, LOW);
}
void atras(int potenciaDerecha, int potenciaIzquierda)
{
  // las potencias pueden tener un valor entre 1 y 255
  analogWrite(Mder2, potenciaDerecha);
  digitalWrite(Mder1, LOW);
  analogWrite(Mizq2, potenciaIzquierda);
  digitalWrite(Mizq2, LOW);
}
void paro()
{
  digitalWrite(Mder1, LOW);
  digitalWrite(Mder2, LOW);
  digitalWrite(Mizq1, LOW);
  digitalWrite(Mizq2, LOW);
}

void izquierda(int potenciaDerecha, int potenciaIzquierda)
{
  // las potencias pueden tener un valor entre 1 y 255

  analogWrite(Mder1, potenciaDerecha);

  digitalWrite(Mder2, LOW);
  digitalWrite(Mizq1, LOW);

  analogWrite(Mizq2, potenciaIzquierda);
}

void derecha(int potenciaDerecha, int potenciaIzquierda)
{
  // las potencias pueden tener un valor entre 1 y 255

  digitalWrite(Mder1, LOW);
  analogWrite(Mder2, potenciaDerecha);

  analogWrite(Mizq1, potenciaIzquierda);

  digitalWrite(Mizq2, LOW);
}

void batallanaval()
{
  Serial.println(digitalRead(REMOTE));
  while (digitalRead(REMOTE) == 0) // mientras esta activo el arrancador poner la bandera a 20 grados y ejecutar battle
  {

    sensorState = sensorValue();
    lineState = lineValue();

    switch (lineState)

    {
    case 3:
      Serial.print("negro - ");

      switch (sensorState)
      {

      case 1: // DETECTA SENSOR ENFRENTE DERECHA.
        Serial.println("caso  1");
        derecha(100, 100); // gira con muy poca potencia a la derecha
        delay(20);
        paro();
        delay(10);
        break;

      case 2: // DETECTA SENSOR ENFRENTE IZQUIERDA.
        Serial.println("caso 2 ");
        izquierda(100, 100);
        delay(20); // gira con poca potencia a la izquierda
        paro();
        delay(10);
        break;

      case 3: // DETECTA DOBLE SENSOR ENFRENTE.
        Serial.println("caso  3");
        adelante(240, 240);
        delay(20); // gira con poca potencia a la izquierda
        paro();
        delay(10);
        break;

      case 4: // DETECTA SOLO SENSOR DERECHO.
        Serial.println("caso  4");
        delay(5);
        derecha(140, 140); // vueltas derecha contra banderas
        delay(20);
        paro();
        delay(10);
        break;

      case 5: // DETECTA ENFRENTE DERECHA Y DERECHA.
        Serial.println("caso  5");
        derecha(105, 105); // vueltas derecha contra banderas
        delay(20);
        paro();
        delay(10);
        break;

      case 8: // DETECTA SOLO SENSOR IZQUIERDO
        Serial.println("caso  8");
        izquierda(140, 140); // gira casi full a la izquierda
        delay(20);
        paro();
        delay(10);
        break;

      case 10: // DETECTA ENFRENTE IZQUIERDA E IZQUIERDA.
        Serial.println("caso  10");
        izquierda(105, 105); // gira con poca potencia a la izquierda
        delay(20);
        paro();
        delay(10);
        break;

      case 15: // DETECTAN TODOS, 1vs10000 kmara qleros, manos les van a faltar para pelarme la verga.
        Serial.println("caso Todos");
        derecha(130, 130); // torbellino mortal a la derecha, impactrueno.
        delay(50);
        break;

      case 11: // 3 sensores izquierda
        Serial.println("caso 11");
        izquierda(115, 115); // vueltas izquierda contra banderas
        delay(20);
        paro();
        delay(10);
        break;

      case 7: // 3 sensores derecha
        Serial.println("caso 12");
        derecha(115, 115); // vueltas derecha contra banderas
        delay(20);
        paro();
        delay(10);
        break;

      default:
        Serial.println("no detecta nada"); // NO DETECTA yyyyyyyy numero izquierda motor izquierda
        adelante(22, 20);                  // valor derecha es motor izquierdo
        delay(30);
        paro();
        delay(20);
        break;
      }
      break;

    case 1:
      Serial.println("Blanco 1 derecha");
      atras(255, 255);
      delay(60);
      paro();
      izquierda(255, 255);
      delay(100);
      paro();
      delay(200);
      break;

    case 2:
      Serial.println("Blanco 2. izquierda");
      atras(255, 255);
      delay(100);
      paro();
      delay(20),
          izquierda(255, 255);
      delay(105);
      paro();
      delay(200);
      break;

    case 0:
      Serial.println("Blanco doble");
      atras(250, 250);
      delay(40);
      izquierda(255, 255);
      delay(60);
      paro();
      delay(200);
      break;

    default:
      Serial.println("Line default");
      break;
    }
  }
  if (digitalRead(REMOTE) == LOW)
    paro();
}
void CurveLeft()
{
  while (digitalRead(REMOTE) == 1)
  {

    adelante(255, 25);
    delay(400);
    paro();
    delay(50);
    batallanaval();
  }
}

void CurveRight()
{
  if (digitalRead(REMOTE) == 1)
  {

    adelante(40, 255);
    delay(400);
    paro();
    batallanaval();
  }
}

void Rocket()
{
  if (digitalRead(REMOTE) == 1)
  {

    adelante(255, 255);
    delay(100);
    paro();
    batallanaval();
  }
}

void RocketDerecha()
{
  if (digitalRead(REMOTE) == 1)
  {
    ;
    adelante(255, 255);
    delay(100);
    paro();
    izquierda(255, 255);
    delay(20);
    paro();
    batallanaval();
  }
}

void loop()
{

  buttonstate = digitalRead(buttonPin); // state the  initial of button
  if (buttonstate == HIGH)
  { // check if it has been pressed
    delay(150);
    buttonstate = digitalRead(buttonPin); // state button again
    if (buttonstate == LOW)
    {                         // if it is 0 considered one press
      initial = oldstate + 1; // increase  initial by 1
      if (initial > 4)
      {
        oldstate = 0;
      }
    }
  }
  else
  { // check if it has been NOT pressed
    delay(150);
  }
  switch (initial)
  {       // react to button press a  initial
  case 1: // if  initial is 1

    Serial.println("rocket");
    Rocket();
    oldstate = initial; // set oldstate  initial as current  initial
    digitalWrite(ledRojo, 255);
    digitalWrite(ledVerde, 0);
    digitalWrite(ledAzul, 0);
    delay(50);
    break;
  case 4:
    Serial.println("curveright");
    CurveRight();
    oldstate = initial;
    digitalWrite(ledRojo, 0);
    digitalWrite(ledVerde, 255);
    digitalWrite(ledAzul, 0);
    delay(50);
    break;

  case 3:
    Serial.println("curveleft");
    CurveLeft();
    oldstate = initial;
    digitalWrite(ledRojo, 0);
    digitalWrite(ledVerde, 0);
    digitalWrite(ledAzul, 255);
    delay(50);
    break;
  case 2: // if  initial is not 1 2 3
    Serial.println("rocketderecha");

    RocketDerecha();
    oldstate = initial; // reset to all off/initial 0
    digitalWrite(ledRojo, 255);
    digitalWrite(ledVerde, 255);
    digitalWrite(ledAzul, 255);
    delay(50);
    break;

  default:
    Serial.println("defaul case 0");

    batallanaval();
    oldstate = 0;
    digitalWrite(ledRojo, 255);
    digitalWrite(ledVerde, 0);
    digitalWrite(ledAzul, 255);
    delay(50);
    break;
  }
}