Controle de GPIO com Teclado Matricial 4x4 - Raspberry Pi Pico

Sobre o Projeto

Este projeto foi desenvolvido para a Raspberry Pi Pico utilizando a biblioteca pico/stdlib.h. 
O sistema integra um teclado matricial 4x4, LEDs RGB e um buzzer. Ao pressionar teclas específicas no teclado,   
diferentes LEDs acendem ou o buzzer é acionado.

Funcionalidades

Tecla 'A': Acende o LED Verde.

Tecla 'B': Acende o LED Azul.

Tecla 'C': Acende o LED Vermelho.

Tecla '#': Aciona o Buzzer por um breve período.


Tecnologias Utilizadas
Linguagem: C
Microcontrolador: Raspberry Pi Pico (RP2040)
Biblioteca: pico/stdlib.h
Simulação: Wokwi


Como Executar o Projeto

Clone o Repositório:
git clone https://github.com/LucasrFig/Atividade-1_Controle-de-pinos-GPIO-utilizando-um-teclado-matricial.git


Compile o Código:

Utilize o ambiente de desenvolvimento VS Code. 
Instar extensão: Raspberry Pi Pico.



Carregue na Raspberry Pi Pico:
Conecte a Raspberry Pi Pico em modo de boot.
Copie o arquivo .uf2 gerado para a unidade de armazenamento da Pico.

