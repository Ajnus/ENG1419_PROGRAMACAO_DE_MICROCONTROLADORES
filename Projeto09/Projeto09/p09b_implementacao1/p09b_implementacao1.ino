// ESTE É O ARQUIVO DO ARDUINO COM OS MOTORES E OS SENSORES ÓTICOS.
// NÃO TEM BOTÃO, NEM LED E NEM DISPLAY AQUI.

#include <AFMotor.h>

AF_DCMotor motorA(3);
AF_DCMotor motorB(4);

unsigned long instanteAnterior = 0;

int sensor1 = A11;
int sensor2 = A12;

void setup() {
  motorA.setSpeed(160);
  motorB.setSpeed(160);

  Serial1.begin(9600);
  Serial1.setTimeout(10);
  Serial.begin(9600);
  Serial.setTimeout(10);

  pinMode(sensor1, INPUT);
  pinMode(sensor2, INPUT);

}

void frente()
{
  motorA.run(FORWARD);
  motorB.run(FORWARD);
}

void tras()
{
  motorA.run(BACKWARD);
  motorB.run(BACKWARD);
}

void esquerda()
{
  //if 
  motorA.run(FORWARD);
  motorB.run(RELEASE);
}

void direita()
{
  motorA.run(RELEASE);
  motorB.run(FORWARD);
}

void parar()
{
  motorA.run(RELEASE);
  motorB.run(RELEASE);
}

void loop() {
  if (Serial1.available() > 0)
  {
    String texto = Serial1.readStringUntil('\n');
    texto.trim();
    Serial.println(texto);
    if (texto != "")
    {
      if (texto == "frente")
      {
        frente();
      }
      else if (texto == "tras")
      {
        tras();
      }
      else if (texto == "esquerda")
      {
        esquerda();
      }
      else if (texto == "direita")
      {
        direita();
      }
      else if (texto == "parar")
      {
        parar();
      } 
    }

  }

  unsigned long instanteAtual = millis();


    if (instanteAtual > instanteAnterior + 100)
    { 
      String valores = String(digitalRead(sensor1)) + " " + String(digitalRead(sensor2));
      Serial.println(valores);
      instanteAnterior = instanteAtual;
      Serial1.println(valores);
    }
}

