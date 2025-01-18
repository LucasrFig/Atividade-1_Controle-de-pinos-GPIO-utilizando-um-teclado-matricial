#include <stdio.h>
#include <math.h>
#include "pico/stdlib.h"
#include "hardware/timer.h"

// Definição dos pinos GPIO para os LEDs
#define LED_VERMELHO 13
#define LED_VERDE 11
#define LED_AZUL 12

// Definição do pino GPIO para o buzzer
#define BUZZER 14

// Número de linhas e colunas do teclado matricial
#define LINHAS 4
#define COLUNAS 4

// Definição dos pinos GPIO para as linhas e colunas do teclado
uint8_t pinos_linhas[LINHAS] = {27, 26, 22, 21};
uint8_t pinos_colunas[COLUNAS] = {20, 19, 18, 17};

// Mapeamento das teclas do teclado matricial
char teclas[LINHAS][COLUNAS] = {
    {'1', '2', '3', 'A'},
    {'4', '5', '6', 'B'},
    {'7', '8', '9', 'C'},
    {'*', '0', '#', 'D'}
};

// Variável para controlar o estado de todos os LEDs
bool todos_leds_ligados;

// Função para inicializar o teclado matricial
void inicializar_teclado() {
    // Configura as linhas como saída (estado inicial: ALTO)
    for (int i = 0; i < LINHAS; i++) {
        gpio_init(pinos_linhas[i]);
        gpio_set_dir(pinos_linhas[i], GPIO_OUT);
        gpio_put(pinos_linhas[i], 1);
    }
    // Configura as colunas como entrada com pull-up
    for (int j = 0; j < COLUNAS; j++) {
        gpio_init(pinos_colunas[j]);
        gpio_set_dir(pinos_colunas[j], GPIO_IN);
        gpio_pull_up(pinos_colunas[j]);
    }
}

// Função para exibir o menu de opções
void exibir_menu() {
    printf("\nTeclado matricial disponível com várias funções :D\n");
    printf("Estas são as teclas que você pode pressionar e suas funções:\n");
    printf("A - Liga/Desliga o LED VERMELHO\n");
    printf("B - Liga/Desliga o LED VERDE\n");
    printf("C - Liga/Desliga o LED AZUL\n");
    printf("D - Liga/Desliga todos os LEDs\n");
    printf("# - Ativa o BUZZER\n");
    printf("* - Exibe este menu novamente\n\n");
}

// Função para verificar qual tecla foi pressionada
char obter_tecla() {
    for (int linha = 0; linha < LINHAS; linha++) {
        // Define a linha como BAIXA
        gpio_put(pinos_linhas[linha], 0);

        for (int coluna = 0; coluna < COLUNAS; coluna++) {
            if (gpio_get(pinos_colunas[coluna]) == 0) { // Detecta pressionamento (estado BAIXO)
                // Aguarda o botão ser liberado
                while (gpio_get(pinos_colunas[coluna]) == 0);
                // Restaura o estado da linha para ALTO
                gpio_put(pinos_linhas[linha], 1);
                return teclas[linha][coluna];
            }
        }

        // Restaura o estado da linha para ALTO
        gpio_put(pinos_linhas[linha], 1);
    }

    // Nenhuma tecla pressionada
    return 0;
}

// Função para controlar os LEDs
void controlar_led(int LED, bool estado, char *nome) {
    if (gpio_get(LED) != estado) gpio_put(LED, estado);
    printf("LED %s: %s\n", nome, estado ? "Ligado" : "Desligado");
}

// Função principal de controle do teclado
void processar_teclado() {
    char tecla = obter_tecla();
    if (tecla) printf("Tecla pressionada: %c\n", tecla);

    switch (tecla) {
        case 'A':
            controlar_led(LED_VERMELHO, !gpio_get(LED_VERMELHO), "VERMELHO");
            break;
        case 'B':
            controlar_led(LED_VERDE, !gpio_get(LED_VERDE), "VERDE");
            break;
        case 'C':
            controlar_led(LED_AZUL, !gpio_get(LED_AZUL), "AZUL");
            break;
        case 'D':
            if (todos_leds_ligados) {
                controlar_led(LED_VERMELHO, false, "VERMELHO");
                controlar_led(LED_VERDE, false, "VERDE");
                controlar_led(LED_AZUL, false, "AZUL");
                todos_leds_ligados = false;
            } else {
                controlar_led(LED_VERMELHO, true, "VERMELHO");
                controlar_led(LED_VERDE, true, "VERDE");
                controlar_led(LED_AZUL, true, "AZUL");
                todos_leds_ligados = true;
            }
            break;
        case '#':
            gpio_put(BUZZER, 1);
            sleep_ms(1000);
            gpio_put(BUZZER, 0);
            break;
        case '*':
            exibir_menu();
            break;
        default:
            break;
    }
}

// Função principal
int main() {
    stdio_init_all();

    // Inicializa LEDs como saída
    gpio_init(LED_VERMELHO);
    gpio_init(LED_VERDE);
    gpio_init(LED_AZUL);
    gpio_set_dir(LED_VERMELHO, GPIO_OUT);
    gpio_set_dir(LED_VERDE, GPIO_OUT);
    gpio_set_dir(LED_AZUL, GPIO_OUT);

    // Inicializa o buzzer
    gpio_init(BUZZER);
    gpio_set_dir(BUZZER, GPIO_OUT);

    // Inicializa o teclado
    inicializar_teclado();

    // Variável de controle inicial
    todos_leds_ligados = false;

    printf("Teclado matricial inicializado!\n");
    exibir_menu();

    while (true) {
        processar_teclado();
    }
}
