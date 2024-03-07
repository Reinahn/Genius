#include <Arduino.h>

#define PINO_LED_1 8
#define PINO_LED_2 9
#define PINO_LED_3 10

#define BOTAO_1 7
#define BOTAO_2 6
#define BOTAO_3 5

#define TOTAL_PARTIDAS 5 // Quantidade máxima de partidas

bool estadoLed = HIGH; // estado do led

uint8_t btn_1_status = 0;
uint8_t btn_2_status = 0;
uint8_t btn_3_status = 0;

uint8_t btn_pressionado = 0;

int inicio = 0; // 0 - sequencia inicial, 1 - modo jogo

int etapas = 0; // 0 - inicio, 1 - jogo, 2 - ganhou, 3 - perdeu

#define MAX_SEQ 6

uint8_t sequencia[MAX_SEQ];

uint8_t rodada_atual = 0;

void sequencia_inicial();
void gerar_sequencia();
void apagaLeds();
void leitura_botoes();
void jogador();
void genius();
void jogo();
int leitura_botoes_jogo(int rodada);
void ligar_leds(int led_1,int led_2,int led_3);


void setup(){

    // Ativa as entradas pullup nos botoes

    pinMode(BOTAO_1, INPUT_PULLUP);
    pinMode(BOTAO_2, INPUT_PULLUP);
    pinMode(BOTAO_3, INPUT_PULLUP);

    // pinos definidos como saida

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
        jogador();
        break;
    }
    delay(100);
}

void sequencia_inicial(){

    // sequencia inicial vai ficar rodando até que o jogador aperte algum botao

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

    // esta funcao acende dois leds para indicar que esta funcao esta gerando uma nova sequencia

    digitalWrite(PINO_LED_1,HIGH);
    digitalWrite(PINO_LED_2,HIGH);
    delay(1000);

    for (int i = 0; i < MAX_SEQ; i++){
        sequencia[i] = random(1,4); // cores que estao sendo geradas 
    }

    apagaLeds();
    rodada_atual = 1;
}

void jogador(){

    // o jogador vai apertar algum botao e o mesmo vai responde se acertou (1) ou não (0)

    int lance = 0;

    for (int i = 0; i < rodada_atual; i++){
        btn_pressionado = leitura_botoes_jogo(i);
        if (btn_pressionado == 1){
            lance = 1;
            delay(100);
        }else{
            inicio = 0;
            etapas = 0;
            break;
        }
    }
    delay(500);
    rodada_atual++;
}

void genius(){

    // esta função vai implementar a sequencia que foi armazenada no array sequencia

    for (int i = 0; i < rodada_atual; i++){
        switch (sequencia[i])
        {
        case 1:
            ligar_leds(1,0,0);
            break;
        case 2:
            ligar_leds(0,1,0);
            break;
        case 3:
            ligar_leds(0,0,1);
            break;
        }
    }
    delay(1000); // tempo de exibição de cada cor
    apagaLeds();
    delay(100);
}

void leitura_botoes(){ 
  
    // esta funcao vai ler os botoes iniciais quando inicio = 0

    btn_1_status = !digitalRead(BOTAO_1);
    btn_2_status = !digitalRead(BOTAO_2);
    btn_3_status = !digitalRead(BOTAO_3);

    if(inicio == 0){
        if (btn_1_status || btn_2_status || btn_3_status){
            apagaLeds();
            inicio = 1;
        }
    }

    delay(50);
}

int leitura_botoes_jogo(int rodada){

    // estao funcao vai capturar as entradas dos botoes quando inicio = 1

    int botao = 0;

    while (botao == 0){
        btn_1_status = !digitalRead(BOTAO_1);
        btn_2_status = !digitalRead(BOTAO_2);
        btn_3_status = !digitalRead(BOTAO_3);

        if(btn_1_status){
            botao = 1;
        }
        if(btn_2_status){
            botao = 2;
        }
        if(btn_3_status){
            botao = 3;
        }
    }

    // compara a sequencia de entradas com as armazenadas na memoria

    if(botao == sequencia[rodada]){
        return 1; // correto
    }else{
        return 0; // incorreto
    }

}

void apagaLeds(){

    // todos os leds serao apagados quando esta funcao for chamada

    digitalWrite(PINO_LED_1, LOW);
    digitalWrite(PINO_LED_2, LOW);
    digitalWrite(PINO_LED_3, LOW);
}

void ligar_leds(int led_1,int led_2,int led_3){

    // liga cada um dos leds de acordo com os parametros de entrada

    digitalWrite(PINO_LED_1, led_1);
    digitalWrite(PINO_LED_2, led_2);
    digitalWrite(PINO_LED_3, led_3);
}