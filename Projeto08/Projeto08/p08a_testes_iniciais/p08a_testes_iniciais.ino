#include <GFButton.h>
#include <EEPROM.h>
#include <Servo.h>

int potenciometro = A5;
int pinoDoServoBase = 12;
int pinoDoServoOmbro = 11;
GFButton botaoC(4);
GFButton botaoB(3);
GFButton botaoA(2);
Servo servoOmbro;
Servo servoBase;
int contador=0;
int endereco = 0;
int anguloOmbro = 90;

void botaoPressionado() {
  contador++;
  Serial.println(contador);
  EEPROM.put(endereco, contador);
}
void setup() {
  servoBase.attach(pinoDoServoBase);
  servoOmbro.attach(pinoDoServoOmbro);
  servoOmbro.write(anguloOmbro);
  pinMode(potenciometro, INPUT);

  Serial.begin(9600);
  botaoB.setPressHandler(botaoPressionado);

  EEPROM.get(endereco, contador);
}

void loop() {
  botaoA.process();
  botaoB.process();
  botaoC.process();
  int valorLido = analogRead(potenciometro);
  int valorFinal = map(valorLido, 0, 1023, 0, 180);
  servoBase.write(valorFinal);
  if (botaoA.isPressed()== true)
  {
    if (anguloOmbro>45)
    {
      anguloOmbro--;
      servoOmbro.write(anguloOmbro);
      delay(15);
    }
  }
  if (botaoC.isPressed()== true)
  {
     if (anguloOmbro<135)
    {
      anguloOmbro++;
      servoOmbro.write(anguloOmbro);
      delay(15);
    }
  }

}
