#include <stdio.h>
#include "pico/stdlib.h"



// Definição dos pinos dos LEDs RGB
#define LED_VERDE_PIN 11
#define LED_AZUL_PIN 12
#define LED_VERMELHO_PIN 13
#define BUZZER_PIN 21

// Definição dos pinos do teclado matricial (ajustado conforme o JSON)
#define ROW1 8  // R1 -> GP8
#define ROW2 7  // R2 -> GP7
#define ROW3 6  // R3 -> GP6
#define ROW4 5  // R4 -> GP5

#define COL1 4   // C1 -> GP4
#define COL2 3   // C2 -> GP3
#define COL3 2   // C3 -> GP2
#define COL4 0  // C4 --> GP0


// Mapeamento das teclas do teclado 4x4
const char keymap[4][4] = {
    {'1', '2', '3', 'A'},
    {'4', '5', '6', 'B'},
    {'7', '8', '9', 'C'},
    {'*', '0', '#', 'D'}
};

// Função para inicializar os LEDs, buzzer e teclado
void init_peripherals() {
    // Inicializa os pinos dos LEDs e do buzzer
    gpio_init(LED_VERDE_PIN);
    gpio_init(LED_AZUL_PIN);
    gpio_init(LED_VERMELHO_PIN);
    gpio_init(BUZZER_PIN);

    gpio_set_dir(LED_VERDE_PIN, GPIO_OUT);
    gpio_set_dir(LED_AZUL_PIN, GPIO_OUT);
    gpio_set_dir(LED_VERMELHO_PIN, GPIO_OUT);
    gpio_set_dir(BUZZER_PIN, GPIO_OUT);

    // Inicializa os pinos das linhas do teclado como saída
    gpio_init(ROW1);
    gpio_init(ROW2);
    gpio_init(ROW3);
    gpio_init(ROW4);

    gpio_set_dir(ROW1, GPIO_OUT);
    gpio_set_dir(ROW2, GPIO_OUT);
    gpio_set_dir(ROW3, GPIO_OUT);
    gpio_set_dir(ROW4, GPIO_OUT);

    // Inicializa os pinos das colunas do teclado
    gpio_init(COL1);
    gpio_init(COL2);
    gpio_init(COL3);
    gpio_init(COL4);

    gpio_set_dir(COL1, GPIO_IN);
    gpio_set_dir(COL2, GPIO_IN);
    gpio_set_dir(COL3, GPIO_IN);
    gpio_set_dir(COL4, GPIO_IN);

    gpio_pull_down(COL1);
    gpio_pull_down(COL2);
    gpio_pull_down(COL3);
    gpio_pull_down(COL4);
}

// Função para ler a tecla pressionada 
char read_keypad() {
    for (int row = 0; row < 4; row++) {
        // Define todas as linhas como baixo
        gpio_put(ROW1, 0);
        gpio_put(ROW2, 0);
        gpio_put(ROW3, 0);
        gpio_put(ROW4, 0);

        // Define a linha atual como alta
        switch (row) {
            case 0: gpio_put(ROW1, 1); break;
            case 1: gpio_put(ROW2, 1); break;
            case 2: gpio_put(ROW3, 1); break;
            case 3: gpio_put(ROW4, 1); break;
        }

        // Verifica qual coluna está alta
        if (gpio_get(COL1)) { sleep_ms(50); if (gpio_get(COL1)) return keymap[row][0]; }
        if (gpio_get(COL2)) { sleep_ms(50); if (gpio_get(COL2)) return keymap[row][1]; }
        if (gpio_get(COL3)) { sleep_ms(50); if (gpio_get(COL3)) return keymap[row][2]; }
        if (gpio_get(COL4)) { sleep_ms(50); if (gpio_get(COL4)) return keymap[row][3]; }
    }
    return '\0'; // Nenhuma tecla pressionada
}


// Função para acender o LED correspondente
void acende_led(char tecla) {
    // Desliga todos os LEDs antes de acionar o correto
    gpio_put(LED_VERDE_PIN, 0);
    gpio_put(LED_AZUL_PIN, 0);
    gpio_put(LED_VERMELHO_PIN, 0);

    switch (tecla) {
        case 'A':
            gpio_put(LED_VERDE_PIN, 1);  // Acende o LED verde
            break;
        case 'B':
            gpio_put(LED_AZUL_PIN, 1);   // Acende o LED azul
            break;
        case 'C':
            gpio_put(LED_VERMELHO_PIN, 1); // Acende o LED vermelho
            break;
        case '#':
            gpio_put(BUZZER_PIN, 1);  // Aciona o buzzer
            sleep_ms(100);  // Tempo de duração do som
            gpio_put(BUZZER_PIN, 0);  // Desliga o buzzer
            break;
        default:
            break;
    }
}

int main() {
    // Inicializa os periféricos
    stdio_init_all();
    init_peripherals();

    while (true) {
        char tecla = read_keypad(); // Lê a tecla pressionada

        if (tecla != '\0') { // Se uma tecla for pressionada
            acende_led(tecla); // Acende o LED ou ativa o buzzer
        }

        sleep_ms(100); // Aguarda um pouco para evitar leituras repetidas
    }

    return 0;
}
