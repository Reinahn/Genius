#include <Arduino.h>

#define PINO_LED_1 3
#define PINO_LED_2 5
#define PINO_LED_3 7

#define BOTAO_1 2
#define BOTAO_2 4
#define BOTAO_3 6

int valores_leds[3] = {};

bool estado = HIGH; // estado do led

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