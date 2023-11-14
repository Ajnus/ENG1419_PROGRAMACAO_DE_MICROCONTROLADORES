#include <meArm.h>
#include <GFButton.h>
#include <EEPROM.h>

int base = 12, ombro = 11, cotovelo = 10, garra = 9;
GFButton botaoA(2);
GFButton botaoB(3);
GFButton botaoC(4);
GFButton botaoD(5);
bool garra_fechada = true;
bool modo = true;  // se true: absoluto, se false: relativo
int eixoX = A0;
int eixoY = A1;
int eixoZ = A5;
int contador = 0;
int pontosSalvos[4][4];
int endereco = 0;


meArm braco(
  180, 0, -pi / 2, pi / 2,      // ângulos da base
  135, 45, pi / 4, 3 * pi / 4,  // ângulos do ombro
  180, 90, 0, -pi / 2,          // ângulos do cotovelo
  30, 0, pi / 2, 0              // ângulos da garra
);

void altera_garra() {
  if (garra_fechada == true) {
    braco.openGripper();
    garra_fechada = false;
  } else {
    braco.closeGripper();
    garra_fechada = true;
  }
}

void altera_modo() {
  if (modo == true) {
    modo = false;
    Serial.println("relativo");
  } else {
    modo = true;
    Serial.println("absoluto");
  }
}

void salva_coord_estado() {
  if (contador <= 3) {
    pontosSalvos[contador][0] = braco.getX();
    pontosSalvos[contador][1] = braco.getY();
    pontosSalvos[contador][2] = braco.getZ();
    pontosSalvos[contador][3] = garra_fechada;
    contador++;
  }
  if (contador == 4) {
    EEPROM.put(endereco, pontosSalvos);
  }
}
void movimenta() {
  for (int i = 0; i < 4; i++) {
    braco.gotoPoint(pontosSalvos[i][0], pontosSalvos[i][1], pontosSalvos[i][2]);
    if (pontosSalvos[i][3] == true) {
      braco.closeGripper();
    } else {
      braco.openGripper();
    }
  }
}

void setup() {
  braco.begin(base, ombro, cotovelo, garra);
  braco.openGripper();
  braco.gotoPoint(0, 130, 0);
  braco.closeGripper();
  botaoC.setPressHandler(salva_coord_estado);
  botaoA.setPressHandler(altera_garra);
  botaoB.setPressHandler(altera_modo);
  botaoD.setPressHandler(movimenta);
  Serial.begin(9600);
  pinMode(eixoX, INPUT);
  pinMode(eixoY, INPUT);
  pinMode(eixoZ, INPUT);
  EEPROM.get(endereco, pontosSalvos);
}

void loop() {
  botaoC.process();
  botaoA.process();
  botaoB.process();
  botaoD.process();


  int valorAnalogicoX = analogRead(eixoX);
  int valorAnalogicoY = analogRead(eixoY);
  int valorAnalogicoZ = analogRead(eixoZ);


  if (modo == true) {
    int valorAbsdoX = map(valorAnalogicoX, 0, 1023, -150, 150);
    int valorAbsdoY = map(valorAnalogicoY, 0, 1023, 100, 200);
    int valorAbsdoZ = map(valorAnalogicoZ, 0, 1023, -30, 100);

    braco.gotoPoint(valorAbsdoX, valorAbsdoY, valorAbsdoZ);
  } else {
    int valorReldoX = braco.getX();
    int valorReldoY = braco.getY();
    int valorReldoZ = braco.getZ();

    int valorMapeadoX = map(valorAnalogicoX, 0, 1023, -10, 10);
    int valorMapeadoY = map(valorAnalogicoY, 0, 1023, -10, 10);
    int valorMapeadoZ = map(valorAnalogicoZ, 0, 1023, -10, 10);

    if (valorMapeadoX != 0 && valorMapeadoY != 0 && valorMapeadoZ != 0) {
      if (valorReldoX + valorMapeadoX > 150) {
        valorReldoX = 150;
      } else {
        valorReldoX = valorReldoX + valorMapeadoX;
      }

      if (valorReldoX + valorMapeadoX < -150) {
        valorReldoX = -150;
      } else {
        valorReldoX = valorReldoX + valorMapeadoX;
      }

      if (valorReldoY + valorMapeadoY > 200) {
        valorReldoY = 200;
      } else {
        valorReldoY = valorReldoY + valorMapeadoY;
      }

      if (valorReldoY + valorMapeadoY < 100) {
        valorReldoY = 100;
      } else {
        valorReldoY = valorReldoY + valorMapeadoY;
      }

      if (valorReldoZ + valorMapeadoZ > 100) {
        valorReldoZ = 100;
      } else {
        valorReldoZ = valorReldoZ + valorMapeadoZ;
      }

      if (valorReldoZ + valorMapeadoZ < -30) {
        valorReldoZ = -30;
      } else {
        valorReldoZ = valorReldoZ + valorMapeadoZ;
      }

      braco.goDirectlyTo(valorReldoX + 2, valorReldoY + 2, valorReldoZ);
      delay(40);
    }
  }
}
