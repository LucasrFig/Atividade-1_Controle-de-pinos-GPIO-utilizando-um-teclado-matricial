#include <stdio.h>
#include "pico/stdlib.h"

//definir pinos das linhas e colunas
uint coluna[4]={19,18,17,16};//C1|C2|C3|C4
uint linha[4]={26,22,21,20};//R1|R2|R3|R4

//Definir pinos de saída do LED
const uint LED_GREEN = 11;
const uint LED_BLUE = 12;
const uint LED_RED = 13;

//Definir pino buzzer
const uint BUZZER = 10;

//mapa do keyboard
char key_map [16] = {
  '1','2','3','a',
  '4','5','6','b',
  '7','8','9','c',
  '*','0','#','d'
};

uint _coluna[4];
uint _linha[4];
char _matrix_values[16];
uint32_t all_col_mask = 0x0;
uint32_t col_mask[4];


//Inicializa o teclado
void keyboard_init(uint coluna[4],uint linha[4],char matrix_values[16]){
  //inicializar matriz de teclas
    for(int i = 0;i<16;i++){
      _matrix_values[i]=matrix_values[i];
    }
  //inicializar pinos das linhas e colunas
    for(int i=0;i<4;i++){

      _coluna[i] = coluna[i];
      _linha[i] = linha[i];

      gpio_init(_coluna[i]);
      gpio_init(_linha[i]);

      gpio_set_dir(_coluna[i],GPIO_IN);
      gpio_set_dir(_linha[i],GPIO_OUT);

      //Deixar as linhas em nível alto
      gpio_put(_linha[i],1);

      //guardar posições das colunas

      all_col_mask = all_col_mask + (1<<_coluna[i]);
      col_mask[i] = (1<<_coluna[i]);

    }
}

//Retorna a tecla pressioanda
char keyboard_get_key(){
    int linha;
    uint32_t cols;//vai guardar as colunas que estão ativas

  //Verificar se há alguma coluna em estado ALTO
    cols = gpio_get_all();
    cols = cols & all_col_mask;

    if (cols == 0x0){
      return 0;
    }

  //Verificar qual linha foi pressionada
    for(int j=0;j<4;j++){
      gpio_put(_linha[j],0);
    }

    for(linha=0;linha<4;linha++){
      gpio_put(_linha[linha],1);

      busy_wait_us(10000);

      cols = gpio_get_all();
      gpio_put(_linha[linha],0);

      cols = cols & all_col_mask;

      if(cols != 0x0){
        break;
      }
    }//quando ocorre o break, vai estar armazenado a linha na variavel 'linha' e o pino da coluna na variável cols.

  //descobrir qual coluna foi pressionada
    for(int j=0;j<4;j++){
      gpio_put(_linha[j],1);
    }

    if(cols==col_mask[0]){
      return (char)_matrix_values[(linha *4 + 0)];
    }else if(cols==col_mask[1]){
      return (char)_matrix_values[(linha * 4 + 1)];
    }else if(cols==col_mask[2]){
      return (char)_matrix_values[(linha * 4 + 2)];
    }else if(cols==col_mask[3]){
      return (char)_matrix_values[(linha * 4 + 3)];
    }else{
      return 0;
    }
}


//Função principal
int main()
{
    stdio_init_all();
    //inicializar buzzer
    gpio_init(BUZZER);
    gpio_set_dir(BUZZER,GPIO_OUT);

    //inicializar leds
    gpio_init(LED_GREEN);
    gpio_set_dir(LED_GREEN, GPIO_OUT);

    gpio_init(LED_BLUE);
    gpio_set_dir(LED_BLUE, GPIO_OUT);

    gpio_init(LED_RED);
    gpio_set_dir(LED_RED, GPIO_OUT);
    //Inicializar keyboard
    keyboard_init(coluna,linha,key_map);

    while (true) {
        char tecla = keyboard_get_key();
        printf("\nTecla pressionada: %c\n", tecla);

        switch (tecla)
        {
        case '1':
          break;
        case '2':
          break;
        case '3':
          break;
        case '4':
          break;
        case '5':
          break;
        case '6':
          break;
        case '7':
          break;
        case '8':
          break;
        case '9':
          break;
        case '0':gpio_put(LED_GREEN,0);gpio_put(LED_BLUE,0);gpio_put(LED_RED,0);//leds off
          break;
        case '*':
          break;
        case '#':gpio_put(BUZZER,1);sleep_ms(2000);gpio_put(BUZZER,0);
          break;
        case 'a':gpio_put(LED_GREEN,1);gpio_put(LED_BLUE,0);gpio_put(LED_RED,0);//led verde on
          break;
        case 'b':gpio_put(LED_GREEN,0);gpio_put(LED_BLUE,1);gpio_put(LED_RED,0);//led azul on
          break;
        case 'c':gpio_put(LED_GREEN,0);gpio_put(LED_BLUE,0);gpio_put(LED_RED,1);//led vermelho on
          break;
        case 'd':gpio_put(LED_GREEN,1);gpio_put(LED_BLUE,1);gpio_put(LED_RED,1);//leds on
          break;
        default:
          break;
        }
    }
    sleep_ms(10);
}
