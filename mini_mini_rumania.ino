#include <Servo.h>
#include <Arduino.h>
#define LINE_A A3
#define LINE_B A0
#define RIGHT 2
#define FRONT_A 4
#define FRONT_B 7
#define LEFT A2
#define SERVO 10
int Mder1 = 6;
int Mder2 = 3;
int Mizq1 = 5;
int Mizq2 = 9;
#define SW1 1
#define SW2 12
#define REMOTE A5

Servo FLAG;

int sensorState;
int lineState;

int yaSensoEnfrente;

void setup() {
  FLAG.attach(SERVO);
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
  Serial.begin(9600);

  yaSensoEnfrente = 0;
}

void loop() {
  Serial.println(digitalRead(REMOTE));

  while (digitalRead(REMOTE) == 1) //mientras esta activo el arrancador poner la bandera a 20 grados y ejecutar battle
  {
    FLAG.write(5);
    sensorState = sensorValue();
    lineState = lineValue();

    switch (lineState) {
      case 41:
        Serial.println("negro");

        switch (sensorState) {

          case 1:  //DETECTA SENSOR ENFRENTE DERECHA.
            Serial.println("caso  1");
            derecha(255, 255); //gira con muy poca potencia a la derecha
            delay(20);
            paro();
            delay(20);
            yaSensoEnfrente = 0;
            break;

          case 2: //DETECTA SENSOR ENFRENTE IZQUIERDA.
            Serial.println("caso 2 ");
            izquierda(250, 250);
            delay(20);//gira con poca potencia a la izquierda
            paro();
            delay(20);
            yaSensoEnfrente = 0;
            break;

          case 3: //DETECTA DOBLE SENSOR ENFRENTE.
            Serial.println("caso  3");

            if (yaSensoEnfrente == 0) {
              adelante(80, 80); //avanza con poca potencia
              delay(20);
              adelante(170, 170); //avanza con media potencia
              delay(150);
              adelante(255, 255); //avanza al full

              yaSensoEnfrente = 1;
            } else if (yaSensoEnfrente == 1) {
              adelante(255, 255); //avanza al full
            }

            break;

          case 4: //DETECTA SOLO SENSOR DERECHO.
            Serial.println("caso  4");
            derecha(255, 255); //gira casi full a la derecha.
            delay(20);
            paro();
            delay(20);
            yaSensoEnfrente = 0;
            break;

          case 5: //DETECTA ENFRENTE DERECHA Y DERECHA.
            Serial.println("caso  5");
            derecha(255, 255); //gira con poca potencia a la derecha
            delay(20);
            paro();
            delay(20);
            yaSensoEnfrente = 0;
            break;

          case 8: //DETECTA SOLO SENSOR IZQUIERDO
            Serial.println("caso  8");
            izquierda(255, 255); //gira casi full a la izquierda
            delay(20);
            paro();
            delay(20);
            yaSensoEnfrente = 0;
            break;

          case 10:  //DETECTA ENFRENTE IZQUIERDA E IZQUIERDA.
            Serial.println("caso  10");
            izquierda(255, 255); //gira con poca potencia a la izquierda
            delay(20);
            paro();
            delay(20);
            yaSensoEnfrente = 0;
            break;

          case 15:  //DETECTAN TODOS, 1vs10000 kmara qleros, manos les van a faltar para pelarme la verga.
            Serial.println("caso Todos");
            derecha(130, 130); //torbellino mortal a la derecha, impactrueno.
            delay(50);
            
            yaSensoEnfrente = 0;
            break;

          case 11: // 3 sensores izquierda
            Serial.println("caso 11");
            izquierda(255, 255); //vueltas izquierda contra banderas
            paro();
            delay(20);
            yaSensoEnfrente = 0;
            break;

          case 7: //3 sensores derecha
            Serial.println("caso 12");
            derecha(255, 255); // vueltas derecha contra banderas
            paro();
            delay(20);
            yaSensoEnfrente = 0;
            break;

          default:
            Serial.println("yyyyy"); //NO DETECTA yyyyyyyy numero izquierda motor izquierda

            adelante (25, 25);
            delay(40);
            paro();
            delay(20);
            yaSensoEnfrente = 0;
            break;
        }
        break;

      case 20:
        Serial.println("Blanco 1");
        atras(255, 255);
        delay(30);
        paro();
        derecha(255, 255);
        delay(100);
        paro();
        delay(300);
        yaSensoEnfrente = 0;
        break;

      case 21:
        Serial.println("Blanco 2");
        atras(255, 255);
        delay(30);
        paro();
        izquierda(255, 255);
        delay(100);
        paro();
        delay(300);
        yaSensoEnfrente = 0;
        break;

      case 0:
        Serial.println("Blanco doble");
        atras(250, 250);
        delay(40);
        izquierda(255, 255);
        delay(100);
        paro();
        delay(300);
        yaSensoEnfrente = 0;
        break;

      default:
        Serial.println("Line default");
        yaSensoEnfrente = 0;
        break;
    }
  }
  paro ();
  FLAG.write(90);

}

// --------------- Funciones de sensores --------------- .

int sensorValue() {
  int sens1 = !digitalRead(FRONT_A) * 2;
  int sens2 = !digitalRead(FRONT_B) * 1;
  int sens3 = digitalRead(RIGHT) * 4;
  int sens4 = digitalRead(LEFT) * 8;
  int total = sens1 + sens2 + sens3 + sens4;
  return total;
}

int lineValue() {
  int line1 = digitalRead(LINE_A) * 20;
  int line2 = digitalRead(LINE_B) * 21;
  int total = line1 + line2;
  return total;
}


// --------------- Funciones de motores --------------- .

void adelante(int potenciaDerecha, int potenciaIzquierda) {
  //las potencias pueden tener un valor entre 1 y 255

  analogWrite(Mder1, potenciaDerecha);
  digitalWrite(Mder2, LOW);
  analogWrite(Mizq1, potenciaIzquierda);
  digitalWrite(Mizq2, LOW);
}
void atras(int potenciaDerecha, int potenciaIzquierda) {
  //las potencias pueden tener un valor entre 1 y 255
  analogWrite(Mder1, LOW);
  digitalWrite(Mder2, potenciaDerecha);
  analogWrite(Mizq1, LOW);
  digitalWrite(Mizq2, potenciaIzquierda);
}
void paro() {
  digitalWrite(Mder1, LOW);
  digitalWrite(Mder2, LOW);
  digitalWrite(Mizq1, LOW);
  digitalWrite(Mizq2, LOW);
}

void derecha(int potenciaDerecha, int potenciaIzquierda) {
  //las potencias pueden tener un valor entre 1 y 255

  analogWrite(Mder1, potenciaDerecha);
  digitalWrite(Mder2, LOW);
  digitalWrite(Mizq1, LOW);
  analogWrite(Mizq2, potenciaIzquierda);
}

void izquierda(int potenciaDerecha, int potenciaIzquierda) {
  //las potencias pueden tener un valor entre 1 y 255

  digitalWrite(Mder1, LOW);
  analogWrite(Mder2, potenciaDerecha);
  analogWrite(Mizq1, potenciaIzquierda);
  digitalWrite(Mizq2, LOW);
}
