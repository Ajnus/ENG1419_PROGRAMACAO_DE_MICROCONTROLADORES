// 7 notas
int frequenciasDasNotas[7] = {659.26, 659.26, 659.26, 523.26, 659.26, 784.00, 392.00};
int intervalosEntreNotas[7] = {100, 200, 200, 100, 200, 400, 200};

#include <ShiftDisplay.h>
#include <RotaryEncoder.h>
#include <GFButton.h>

int cont[] = { 0, 0, 0, 0 };
ShiftDisplay display(4, 7, 8, COMMON_ANODE, 4, true);
RotaryEncoder encoder(20, 21);
int posicaoAnterior = 0;
unsigned long instanteAnterior[] = { 0, 0, 0, 0 };
bool emAndamento[] = { false, false, false, false };
GFButton botao1(A1);
GFButton botao2(A2);
int terra = A5;
int campainha = 5;
int indiceDaContagemAtual = 0;
int leds[] = { 13, 12, 11, 10 };
unsigned long instanteAtualGiro = 0;
unsigned long instanteAnteriorGiro = 0;


void setup() {
  int origem1 = digitalPinToInterrupt(20);
  attachInterrupt(origem1, tickDoEncoder, CHANGE);
  int origem2 = digitalPinToInterrupt(21);
  attachInterrupt(origem2, tickDoEncoder, CHANGE);
  Serial.begin(9600);
  pinMode(terra, OUTPUT);
  digitalWrite(terra, LOW);
  botao1.setPressHandler(muda_andamento);
  botao2.setPressHandler(novo_indice);
  for (int i = 0; i < 4; i++) {
    pinMode(leds[i], OUTPUT);
    digitalWrite(leds[i], HIGH);
  }
  digitalWrite(leds[0], LOW);
}

void novo_indice() {
  indiceDaContagemAtual += 1;
  if (indiceDaContagemAtual > 3) {
    indiceDaContagemAtual = 0;
  }

  for (int i = 0; i < 4; i++) {
    if (i == indiceDaContagemAtual) {
      digitalWrite(leds[i], LOW);
    } else {
      digitalWrite(leds[i], HIGH);
    }
  }
}
void tickDoEncoder() {
  encoder.tick();
}

void muda_andamento() {
  if (emAndamento[indiceDaContagemAtual] == false)
    emAndamento[indiceDaContagemAtual] = true;
  else if (emAndamento[indiceDaContagemAtual] == true)
    emAndamento[indiceDaContagemAtual] = false;

  Serial.println(emAndamento[indiceDaContagemAtual]);
}



void loop() {
  int cont_inteiro = (cont[indiceDaContagemAtual] / 60) * 100;
  int cont_decimal = (cont[indiceDaContagemAtual] % 60);
  Serial.println(cont_inteiro);
  Serial.println(cont_decimal);

  //display.changeDot(0, true);
  display.set(cont_inteiro + cont_decimal, true);
  display.changeDot(1, true);
  display.update();
  botao1.process();
  botao2.process();

  int posicao = encoder.getPosition();
  instanteAtualGiro = millis();

  if (posicao > posicaoAnterior) {
    if (instanteAtualGiro > instanteAnteriorGiro + 50)
    {
      cont[indiceDaContagemAtual] += 1;
    }
    else{
    cont[indiceDaContagemAtual] += 15;
    }
    Serial.println(posicao);
    instanteAnteriorGiro = instanteAtualGiro;
  } else if (posicao < posicaoAnterior) {
    if (instanteAtualGiro < instanteAnteriorGiro + 50)
    {
      cont[indiceDaContagemAtual] -= 1;
    }
    else{
    cont[indiceDaContagemAtual] -= 15;
    }
    Serial.println(posicao);
    instanteAnteriorGiro = instanteAtualGiro;
  }

    if (cont[indiceDaContagemAtual] < 0) {
      cont[indiceDaContagemAtual] = 0;
    }
  posicaoAnterior = posicao;

  for (int i = 0; i < 4; i++) {
    unsigned long instanteAtual = millis();
    if (instanteAtual > instanteAnterior[i] + 1000 && emAndamento[i] == true) {
      cont[i]--;
      Serial.println(cont[i]);
      instanteAnterior[i] = instanteAtual;
    }
    if (cont[i] < 0) {
      cont[i] = 0;
    }

    if (cont[i] == 0 && emAndamento[i] == true) {
      emAndamento[i] = false;
      for (int i=0;i<7;i++)
      {
      tone(campainha, frequenciasDasNotas[i], intervalosEntreNotas[i]);
      }
    }
  }


  if (cont[indiceDaContagemAtual] == 0 && emAndamento[indiceDaContagemAtual] == true) {
    emAndamento[indiceDaContagemAtual] = false;
    for (int i=0;i<7;i++)
    {
      tone(campainha, frequenciasDasNotas[i], intervalosEntreNotas[i]);
    }
  }
}


