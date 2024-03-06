#include <Arduino.h>

#define PINO_LED_1 8
#define PINO_LED_2 9
#define PINO_LED_3 10

#define BOTAO_1 7
#define BOTAO_2 6
#define BOTAO_3 5

#define TOTAL_PARTIDAS 5 // Quantidade máxima de partidas

bool estadoLed = HIGH; // estado do led
bool estadoBotao = false;
bool perdeu = false;

uint8_t btn_1_status = 0;
uint8_t btn_2_status = 0;
uint8_t btn_3_status = 0;

int inicio = 0; // 0 - sequencia inicial, 1 - modo jogo

int etapas = 0; // 0 - inicio, 1 - jogo, 2 - ganhou, 3 - perdeu

#define MAX_SEQ 6

uint8_t sequencia[MAX_SEQ];

uint8_t rodada_atual = 0;

void sequencia_inicial();
void gerar_sequencia();
void apagaLeds();
void leitura_botoes();
void genius();
void jogo();


void setup(){

  // Ativa as entradas pullup nos botoes

  pinMode(BOTAO_1, INPUT_PULLUP);
  pinMode(BOTAO_2, INPUT_PULLUP);
  pinMode(BOTAO_3, INPUT_PULLUP);

  // pino definidos como saida

  pinMode(PINO_LED_1,OUTPUT);
  pinMode(PINO_LED_2,OUTPUT);
  pinMode(PINO_LED_3,OUTPUT);
}

void loop(){

  while(inicio != 1){
    sequencia_inicial();
    leitura_botoes();
  }

  while(inicio == 1){
    jogo();
  }
}

void jogo(){

  switch (etapas)
  {
  case 0:
    gerar_sequencia();
    etapas++;
    break;
  case 1:
    genius();
    // jogador();
    break;
  }

}

void sequencia_inicial(){

  digitalWrite(PINO_LED_1,estadoLed);
  delay(300);

  digitalWrite(PINO_LED_2,estadoLed);
  delay(300);

  digitalWrite(PINO_LED_3,estadoLed);
  delay(300);

  digitalWrite(PINO_LED_1,!estadoLed);
  delay(300);

  digitalWrite(PINO_LED_2,!estadoLed);
  delay(300);

  digitalWrite(PINO_LED_3,!estadoLed);
  delay(300);

}

void gerar_sequencia(){

  digitalWrite(PINO_LED_1,HIGH);
  digitalWrite(PINO_LED_2,HIGH);
  delay(1000);

  for (int i = 0; i < MAX_SEQ; i++){
    sequencia[i] = random(1,4);
  }

  rodada_atual = 1;
  
}

// void jogador(){

// }

void genius(){

  Serial.print('oi');

  for (int i = 0; i < rodada_atual; i++){
    switch (sequencia[i])
    {
    case 1:
      digitalWrite(PINO_LED_1,HIGH);
      break;
    case 2:
      digitalWrite(PINO_LED_2,HIGH);
      break;
    case 3:
      digitalWrite(PINO_LED_3,HIGH);
      break;
    }
  }
}

void leitura_botoes(){ 
  
  // esta funcao vai ler os botoes iniciais quando inicio = 0

  btn_1_status = !digitalRead(BOTAO_1);
  btn_2_status = !digitalRead(BOTAO_2);
  btn_3_status = !digitalRead(BOTAO_3);

  if (btn_1_status || btn_2_status || btn_3_status){
    apagaLeds();
    inicio = 1;
  }
}

void leitura_botoes_jogo(){

  // estao funcao vai capturar as entradas dos botoes quando inicio = 1

  btn_1_status = !digitalRead(BOTAO_1);
  btn_2_status = !digitalRead(BOTAO_2);
  btn_3_status = !digitalRead(BOTAO_3);

}

void apagaLeds(){
  digitalWrite(PINO_LED_1, LOW);
  digitalWrite(PINO_LED_2, LOW);
  digitalWrite(PINO_LED_3, LOW);
}