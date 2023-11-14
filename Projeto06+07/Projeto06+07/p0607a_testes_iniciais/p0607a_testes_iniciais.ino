#include <GFButton.h>
#include <ShiftDisplay.h>
#include <stdio.h>
#include <RotaryEncoder.h>
RotaryEncoder encoder(20, 21);

ShiftDisplay display(4, 7, 8,COMMON_ANODE,4,true);
GFButton botao(A2);
GFButton botao3(A3);
int led = 13;
int led2 = 12;
bool estado = false;
int cont = 0;
unsigned long instanteAnterior = 0;
int terra = A5;
int campainha = 5;
int posicaoAnterior = 0;


void muda_estado(){
  if(estado == false){
    digitalWrite(led2, LOW);
    estado = true;
  }else{
    digitalWrite(led2, HIGH);
    estado = false;
  }
}

void adiciona(){
    cont+=1;
    display.set(cont);
    printf(cont);
}

void setup() {
  // put your setup code here, to run once:
  pinMode(led, OUTPUT);
  digitalWrite(led, LOW);
  pinMode(led2, OUTPUT);
  Serial.begin(9600);
  pinMode(terra, OUTPUT);
  digitalWrite(terra, LOW);

  int origem1 = digitalPinToInterrupt(20);
  attachInterrupt(origem1, tickDoEncoder, CHANGE);
  int origem2 = digitalPinToInterrupt(21);
  attachInterrupt(origem2, tickDoEncoder, CHANGE);

  botao.setPressHandler(muda_estado);
  botao3.setPressHandler(adiciona);
  //display.set(cont);

}

void tickDoEncoder() {
  encoder.tick();
}

void loop() {
  // put your main code here, to run repeatedly:
  botao.process();
  botao3.process();
  display.update();

  unsigned long instanteAtual = millis();
  if (instanteAtual > instanteAnterior + 2000) {
    Serial.println(cont);
    instanteAnterior = instanteAtual;
  }

  int posicao = encoder.getPosition();
  if (posicao > posicaoAnterior) {
    Serial.println(posicao);
    tone(campainha, 440, 50);
  }else if(posicao < posicaoAnterior) {
    tone(campainha, 220, 50);
  }
  posicaoAnterior = posicao;
}
