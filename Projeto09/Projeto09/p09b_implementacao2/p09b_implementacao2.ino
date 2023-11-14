// NÃO COPIE O IMPLEMENTAÇÃO 1 PARA CÁ NÃO!
// ESSE É UM CÓDIGO SEPARADO DA PRIMEIRA PARTE!

// ESTE É O ARQUIVO DO ARDUINO SÓ COM O SHIELD MULTIFUNÇÃO.
// NÃO TEM MOTOR E SENSOR ÓTICO.

#include <GFButton.h>
#include <ShiftDisplay.h>

ShiftDisplay display(4,7,8, COMMON_ANODE, 4, true);

GFButton botao1(A1);
GFButton botao2(A2);

String funcoes[4] = {"frente", "tras", "esquerda", "direita"};
int i = 0;

int led1 = 13;
int led2 = 12;

void setup() 
{
  botao1.setPressHandler(aperta_botao1);
  Serial1.begin(9600);
  Serial1.setTimeout(10);
  Serial.begin(9600);
  Serial.setTimeout(10);
  botao2.setPressHandler(aperta_botao2);
  botao2.setReleaseHandler(solta_botao2);
  display.set(i);
  pinMode(led1, OUTPUT);
  pinMode(led2, OUTPUT);
}

void loop() 
{
  botao1.process();
  botao2.process();
  display.update();

  if (Serial1.available() > 0)
  {
    String texto = Serial1.readStringUntil("\n");
    texto.trim();

    Serial.println(texto);
    Serial.println(texto.substring(0,1));
    Serial.println(texto.substring(2));

    if (texto.substring(0,1) == "0")
    {
      digitalWrite(led1, LOW);
    }
    else if(texto.substring(0,1) == "1")
    {
      digitalWrite(led1, HIGH);
    }
    else if(texto.substring(2) == "0")
    {
      digitalWrite(led2, LOW);
    }
    else if(texto.substring(2) == "1")
    {
      digitalWrite(led2, HIGH);
    }
  }
}

void aperta_botao1()
{
  if (i<3)
  {
    i++;
  }
  else
  {
    i = 0;
  }
  display.set(i);
}

void aperta_botao2()
{
  Serial.println(funcoes[i]);
  Serial1.println(funcoes[i]);
}

void solta_botao2()
{
  Serial1.println("parar");
}
