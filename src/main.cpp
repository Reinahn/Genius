#include <Arduino.h>

#define PINO_LED_1 3
#define PINO_LED_2 5
#define PINO_LED_3 7

#define BOTAO_1 2
#define BOTAO_2 4
#define BOTAO_3 6

#define TOTAL_PARTIDAS 5 // Quantidade máxima de partidas

bool estadoLed = HIGH; // estado do led
bool estadoBotao = false;

int sequencia[6] = {};

int rodada_atual = 0;

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

}

void sequencia_inicial(){

  digitalWrite(PINO_LED_1,estadoLed);
  delay(500);

  digitalWrite(PINO_LED_2,estadoLed);
  delay(500);

  digitalWrite(PINO_LED_3,estadoLed);
  delay(500);

  digitalWrite(PINO_LED_1,!estadoLed);
  delay(500);

  digitalWrite(PINO_LED_2,!estadoLed);
  delay(500);

  digitalWrite(PINO_LED_3,!estadoLed);
  delay(500);

}