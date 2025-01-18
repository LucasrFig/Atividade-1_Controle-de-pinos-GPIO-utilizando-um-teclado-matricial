#include <stdio.h>
#include "pico/stdlib.h"

// Definir pinos das linhas e colunas
uint coluna[4] = {19, 18, 17, 16}; // C1|C2|C3|C4
uint linha[4] = {26, 22, 21, 20};  // R1|R2|R3|R4

// Definir pinos de saída do LED
const uint LED_VERDE = 11;
const uint LED_AZUL = 12;
const uint LED_VERMELHO = 13;

// Definir pino buzzer
const uint BUZZER = 10;

// Mapa do teclado
char mapa_teclado[16] = {
  '1', '2', '3', 'a',
  '4', '5', '6', 'b',
  '7', '8', '9', 'c',
  '*', '0', '#', 'd'
};

uint _coluna[4];
uint _linha[4];
char _valores_matriz[16];
uint32_t checar_colunas_todas = 0x0;
uint32_t checar_coluna[4];

// Função para inicializar o teclado
void inicializar_teclado(uint coluna[4], uint linha[4], char valores_matriz[16]) {
    for (int i = 0; i < 16; i++) {
        _valores_matriz[i] = valores_matriz[i];
    }
    for (int i = 0; i < 4; i++) {
        _coluna[i] = coluna[i];
        _linha[i] = linha[i];

        gpio_init(_coluna[i]);
        gpio_init(_linha[i]);

        gpio_set_dir(_coluna[i], GPIO_IN);
        gpio_set_dir(_linha[i], GPIO_OUT);

        // Deixar as linhas em nível alto
        gpio_put(_linha[i], 1);
        
        // Guardar as posições das colunas
        checar_colunas_todas += (1 << _coluna[i]);
        checar_coluna[i] = (1 << _coluna[i]);
    }
}

// Função para obter a tecla pressionada
char obter_tecla() {
    int linha;
    uint32_t colunas; // Vai guardar as colunas que estão ativas

    // Verificar se há alguma coluna em estado ALTO
    colunas = gpio_get_all();
    colunas = colunas & checar_colunas_todas;

    if (colunas == 0x0) {
        return 0;
    }

    // Verificar qual linha foi pressionada
    for (int j = 0; j < 4; j++) {
        gpio_put(_linha[j], 0);
    }

    for (linha = 0; linha < 4; linha++) {
        gpio_put(_linha[linha], 1);
        // Ajuste para diminuir o tempo de espera
        busy_wait_us(1000);  // Agora espera 1ms
        colunas = gpio_get_all();
        gpio_put(_linha[linha], 0);

        colunas = colunas & checar_colunas_todas;

        if (colunas != 0x0) {
            break;
        }
    }

    // Descobrir qual coluna foi pressionada
    for (int j = 0; j < 4; j++) {
        gpio_put(_linha[j], 1);
    }

    if (colunas == checar_coluna[0]) {
        return (char)_valores_matriz[(linha * 4 + 0)];
    } else if (colunas == checar_coluna[1]) {
        return (char)_valores_matriz[(linha * 4 + 1)];
    } else if (colunas == checar_coluna[2]) {
        return (char)_valores_matriz[(linha * 4 + 2)];
    } else if (colunas == checar_coluna[3]) {
        return (char)_valores_matriz[(linha * 4 + 3)];
    } else {
        return 0;
    }
}

// Função para inicializar os LEDs
void inicializar_leds() {
    gpio_init(LED_VERDE);
    gpio_set_dir(LED_VERDE, GPIO_OUT);
    gpio_put(LED_VERDE, 0); // LED verde desligado inicialmente

    gpio_init(LED_AZUL);
    gpio_set_dir(LED_AZUL, GPIO_OUT);
    gpio_put(LED_AZUL, 0); // LED azul desligado inicialmente

    gpio_init(LED_VERMELHO);
    gpio_set_dir(LED_VERMELHO, GPIO_OUT);
    gpio_put(LED_VERMELHO, 0); // LED vermelho desligado inicialmente
}

// Função para inicializar o buzzer
void inicializar_buzzer() {
    gpio_init(BUZZER);
    gpio_set_dir(BUZZER, GPIO_OUT);
    gpio_put(BUZZER, 0); // Buzzer desligado inicialmente
}

// Função para acender o LED de uma cor específica
void acender_led(uint led) {
    gpio_put(LED_VERDE, (led == LED_VERDE) ? 1 : 0);
    gpio_put(LED_AZUL, (led == LED_AZUL) ? 1 : 0);
    gpio_put(LED_VERMELHO, (led == LED_VERMELHO) ? 1 : 0);
}

// Função para apagar todos os LEDs
void apagar_leds() {
    gpio_put(LED_VERDE, 0);
    gpio_put(LED_AZUL, 0);
    gpio_put(LED_VERMELHO, 0);
}

void acender_leds_todos(){
    gpio_put(LED_VERDE, 1);
    gpio_put(LED_AZUL, 1);
    gpio_put(LED_VERMELHO, 1);
}

// Função para tocar o buzzer
void tocar_buzzer() {
    gpio_put(BUZZER, 1);
    sleep_ms(500);  
    gpio_put(BUZZER, 0);
}

// Função para lidar com a tecla pressionada
void processar_tecla(char tecla) {
    switch (tecla) {
        case '1': 
        case '2': 
        case '3': 
        case '4': 
        case '5': 
        case '6': 
        case '7': 
        case '8': 
        case '9': 
        case '0':
            apagar_leds(); // Desliga todos os LEDs
            gpio_put(BUZZER, 0); 
            break;

        case '*': 
        case '#': 
            tocar_buzzer(); // Toca o buzzer
            break;

        case 'a': 
            acender_led(LED_VERDE); // Acende o LED verde
            sleep_ms(500);  // LED acende por 500ms
            gpio_put(LED_VERDE, 0);  // Desliga o LED 
            break;

        case 'b': 
            acender_led(LED_AZUL); // Acende o LED azul
            sleep_ms(500);  // LED acende por 500ms
            gpio_put(LED_AZUL, 0);  // Desliga o LED 
            break;

        case 'c': 
            acender_led(LED_VERMELHO); // Acende o LED vermelho
            sleep_ms(500);  // LED acende por 500ms
            gpio_put(LED_VERMELHO, 0);  // Desliga o LED 
            break;

        case 'd': 
            acender_leds_todos(); // Acende todos os LEDs
            sleep_ms(500);  // LEDs acendem por 500ms
            apagar_leds(); // Desliga todos os LEDs
            break;

        default:
            break;
    }
}

// Função principal
int main() {
    stdio_init_all();

    // Inicializar LEDs, buzzer e teclado
    inicializar_leds();
    inicializar_buzzer();  // O buzzer já estará desligado, mas garantido pela inicialização
    inicializar_teclado(coluna, linha, mapa_teclado);

    while (true) {
        char tecla = obter_tecla();

        if (tecla != 0) {
            processar_tecla(tecla); // Processa a tecla pressionada
        }
    }
}
