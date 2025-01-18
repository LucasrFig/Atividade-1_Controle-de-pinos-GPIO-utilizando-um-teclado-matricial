#include <stdio.h>
#include "pico/stdlib.h"

// Definição das linhas e colunas do teclado
uint8_t linhas[4] = {26, 22, 21, 20};
uint8_t colunas[4] = {19, 18, 17, 16};

// Definição dos LEDs
#define LED_VERMELHO 13
#define LED_AZUL 12
#define LED_VERDE 11

// Definição do Buzzer
#define BUZZER 10

// Matriz do teclado
char matriz[4][4] = {
    {'1', '2', '3', 'A'},
    {'4', '5', '6', 'B'},
    {'7', '8', '9', 'C'},
    {'*', '0', '#', 'D'}
}; // Facilita identificar a tecla pressionada

void configuracao() {
    // Configuração das linhas como saída
    for (int i = 0; i < 4; i++) {
        gpio_init(linhas[i]);
        gpio_set_dir(linhas[i], GPIO_OUT);
        gpio_put(linhas[i], 0); // Inicializa em LOW
    }

    // Configuração das colunas como entrada com pull-up
    for (int j = 0; j < 4; j++) {
        gpio_init(colunas[j]);
        gpio_set_dir(colunas[j], GPIO_IN);
        gpio_pull_up(colunas[j]); // Colunas estão conectadas em HIGH
    }

    // Configuração dos LEDs como saída
    gpio_init(LED_VERMELHO);
    gpio_set_dir(LED_VERMELHO, GPIO_OUT);
    gpio_put(LED_VERMELHO, 0);

    gpio_init(LED_AZUL);
    gpio_set_dir(LED_AZUL, GPIO_OUT);
    gpio_put(LED_AZUL, 0);

    gpio_init(LED_VERDE);
    gpio_set_dir(LED_VERDE, GPIO_OUT);
    gpio_put(LED_VERDE, 0);

    // Configuração do buzzer como saída
    gpio_init(BUZZER);
    gpio_set_dir(BUZZER, GPIO_OUT);
    gpio_put(BUZZER, 0); // Inicializa em LOW
}

void acionar_buzzer() {
    gpio_put(BUZZER, 1); // Liga o buzzer
    sleep_ms(3000);       // Mantém o buzzer ligado por 3000ms
    gpio_put(BUZZER, 0); // Desliga o buzzer
}

void acender_led(char tecla) {
    // Ignora acender LEDs para * e #
    if (tecla == '*' || tecla == '#') {
        return;
    }

    // Desliga todos os LEDs
    gpio_put(LED_VERMELHO, 0);
    gpio_put(LED_AZUL, 0);
    gpio_put(LED_VERDE, 0);

    // Lógica para acender LEDs com base no dígito pressionado
    if (tecla == '1' || tecla == '4' || tecla == '7') { // Primeira coluna
        gpio_put(LED_VERMELHO, 1);
    } else if (tecla == '2' || tecla == '5' || tecla == '8') { // Segunda coluna
        gpio_put(LED_AZUL, 1);
    } else if (tecla == '3' || tecla == '6' || tecla == '9') { // Terceira coluna
        gpio_put(LED_VERDE, 1);
    } else if (tecla == 'A' || tecla == 'B' || tecla == 'C' || tecla == 'D') { // Quarta coluna
        gpio_put(LED_VERMELHO, 1);
        gpio_put(LED_AZUL, 1);
        gpio_put(LED_VERDE, 1);
    }
}

char leitura_digito() {
    char tecla_pressionada = '\0';

    for (int line = 0; line < 4; line++) {
        // Ativa a linha atual
        gpio_put(linhas[line], 0);

        // Varre todas as colunas
        for (int col = 0; col < 4; col++) {
            if (gpio_get(colunas[col]) == 0) { // Se uma tecla é pressionada
                sleep_ms(20); // Debounce

                // Confirma que a tecla ainda está pressionada
                if (gpio_get(colunas[col]) == 0) {
                    tecla_pressionada = matriz[line][col];

                    // Aciona o buzzer para as teclas * e #
                    if (tecla_pressionada == '*' || tecla_pressionada == '#') {
                        acionar_buzzer(); // Liga o buzzer
                        while (gpio_get(colunas[col]) == 0) { // Aguarda liberação do botão
                            sleep_ms(10);
                        }
                        gpio_put(linhas[line], 0); // Desativa a linha antes de continuar
                        return tecla_pressionada;
                    }

                    // Aciona o LED correspondente para outras teclas
                    acender_led(tecla_pressionada);

                    // Aguarda o botão ser liberado
                    while (gpio_get(colunas[col]) == 0) {
                        sleep_ms(10); // Reduz uso de CPU
                    }

                    // Desliga os LEDs após o botão ser liberado
                    gpio_put(LED_VERMELHO, 0);
                    gpio_put(LED_AZUL, 0);
                    gpio_put(LED_VERDE, 0);

                    gpio_put(linhas[line], 0); // Desativa a linha
                    return tecla_pressionada; // Retorna a tecla pressionada
                }
            }
        }
        gpio_put(linhas[line], 0); // Desativa a linha caso nenhuma tecla seja pressionada
    }

    return '\0'; // Retorna '\0' se nenhuma tecla for pressionada
}

int main() {
    configuracao();

    while (true) {
        char digito = leitura_digito();
        if (digito != '\0') {
            sleep_ms(200); // Delay para debounce
        }
    }
}
