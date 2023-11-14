#include <ShiftDisplay.h>
#include <RotaryEncoder.h>
#include <GFButton.h>

int cont = 0;
ShiftDisplay display(4, 7, 8,COMMON_ANODE,4,true);
RotaryEncoder encoder(20, 21);
int posicaoAnterior = 0;
unsigned long instanteAnterior = 0; 
bool emAndamento = false;
GFButton botao1(A1);
int terra = A5;
int campainha = 5;

void setup() {
  int origem1 = digitalPinToInterrupt(20);
  attachInterrupt(origem1, tickDoEncoder, CHANGE);
  int origem2 = digitalPinToInterrupt(21);
  attachInterrupt(origem2, tickDoEncoder, CHANGE);
  Serial.begin(9600);
  pinMode(terra, OUTPUT);
  digitalWrite(terra, LOW);
  botao1.setPressHandler(muda_andamento);


}

void tickDoEncoder() {
  encoder.tick();
}

void muda_andamento()
{
  if (emAndamento == false)
    emAndamento = true;
  else if (emAndamento == true)
    emAndamento = false;

  Serial.println(emAndamento);
}



void loop() {
  int cont_inteiro = (cont/60)*100;
  int cont_decimal = (cont%60);
  Serial.println(cont_inteiro);
  Serial.println(cont_decimal);

  //display.changeDot(0, true);
  display.set(cont_inteiro+cont_decimal, true);
  display.changeDot(1, true);
  display.update();
  botao1.process();

  int posicao = encoder.getPosition();
    if (posicao > posicaoAnterior) {
      Serial.println(posicao);
      cont+=15;
    }else if(posicao < posicaoAnterior) {
      cont-=15;
      if (cont<0)
      {
        cont = 0;
      }
    }
    posicaoAnterior = posicao;

  unsigned long instanteAtual = millis();
  if (instanteAtual > instanteAnterior + 1000 && emAndamento == true) {
    cont--;
    Serial.println(cont);
    instanteAnterior = instanteAtual;
  }

  if (cont == 0 && emAndamento == true)
  {
    emAndamento = false;
    tone(campainha, 666, 150);
  }

}
