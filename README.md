──────────────────────────────────────────────────────────────────────  
# PROJETO - CONTROLE DE PINOS GPIO UTILIZANDO UM TECLADO MATRICIAL  
(SUB GRUPO 6 - ATIVIDADE 1)  
**Equipe do Projeto:** 

──────────────────────────────────────────────────────────────────────

- João Murillo Brito Taveira  
- Amanda Cardoso Lopes  
- Lucas Ricardo De Lima Figueiredo (Líder da semana)  
- Matheus Leite Machado  
- Vinícius Da Silva Barreto Dos Santos  
- Wendel Souza Santos  

──────────────────────────────────────────────────────────────────────  
## OBJETIVO DO PROJETO  
──────────────────────────────────────────────────────────────────────  

O objetivo deste projeto é criar um sistema de controle de pinos GPIO (General Purpose Input/Output) utilizando um teclado matricial. Através desse sistema, será possível acionar LEDs e buzzer com base nas teclas pressionadas no teclado, oferecendo uma interação simples e prática com o hardware. 

──────────────────────────────────────────────────────────────────────  
## METODOLOGIA ESCOLHIDA PARA REALIZAÇÃO DO PROJETO
──────────────────────────────────────────────────────────────────────  
Comparando o tamanho da tarefa e a grande quantidade de pessoas no grupo, decidimos que a melhor abordagem seria cada membro criar uma branch no git, desenvolver seu código referente a tarefa e dar um commit nos arquivos criados, após isso, fizemos uma reunião onde avaliamos o funcionamento de cada código criado e escolhemos o que estivesse mais otimizado para ser inserido na branch principal. Dessa forma, todos tivemos a experiência de desenvolver o código por completo e espaço para trabalhar as funcionalidades do teclado matricial.

──────────────────────────────────────────────────────────────────────  
## FUNCIONALIDADES DO PROJETO  
──────────────────────────────────────────────────────────────────────  

O programa oferece as seguintes funcionalidades baseadas nas teclas do teclado matricial:

Tecla 'A': Acende o LED Verde.

Tecla 'B': Acende o LED Azul.

Tecla 'C': Acende o LED Vermelho.

Tecla '#': Aciona o Buzzer por um breve período.

──────────────────────────────────────────────────────────────────────  
## ESTRUTURA DO PROGRAMA  
──────────────────────────────────────────────────────────────────────  

O programa segue a seguinte estrutura de funcionamento:

1. *Leitura do Teclado:* O teclado matricial é lido para capturar a tecla pressionada.  
2. *Ação de Cada Tecla:* Dependendo da tecla pressionada, o sistema realiza a ação correspondente, como acender LEDs ou emitir som com o buzzer.  
3. *Controle de GPIO:* O programa utiliza funções para controlar os pinos GPIO, ativando/desativando LEDs e o buzzer.  
4. *Interatividade:* O sistema permite múltiplas interações, com o usuário podendo pressionar diferentes teclas para acionar as funcionalidades desejadas.

──────────────────────────────────────────────────────────────────────  
## TECNOLOGIAS UTILIZADAS  
──────────────────────────────────────────────────────────────────────  
- Linguagem: C
- Microcontrolador: Raspberry Pi Pico (RP2040)
- Biblioteca: pico/stdlib.h
- Simulação: Wokwi


──────────────────────────────────────────────────────────────────────  
## COMO EXECUTAR O PROJETO
──────────────────────────────────────────────────────────────────────  
- **Clone o Repositório:**
  git clone https://github.com/LucasrFig/Atividade-1_Controle-de-pinos-GPIO-utilizando-um-teclado-matricial.git

- **Compile o Código:**
  Utilize o ambiente de desenvolvimento VS Code. 
  Instar extensão: Raspberry Pi Pico.

- **Carregue na Raspberry Pi Pico:**
  Conecte a Raspberry Pi Pico em modo de boot.
  Copie o arquivo .uf2 gerado para a unidade de armazenamento da Pico.
  
──────────────────────────────────────────────────────────────────────  
## CONCLUSÃO  
──────────────────────────────────────────────────────────────────────  

Neste projeto, aprendemos a realizar o controle de pinos GPIO utilizando um teclado matricial, o que nos proporcionou uma compreensão mais profunda da interação entre hardware e software. A simulação foi fundamental para validar a lógica do código, especialmente porque não dispúnhamos de um teclado matricial físico para testar diretamente. Utilizando a ferramenta WOKWI, conseguimos testar um componente de hardware diferente dos disponíveis na BitLabDog, o que nos permitiu expandir nosso conhecimento prático. Esse processo de simulação e teste contribuiu significativamente para o aprimoramento de nossas habilidades em desenvolver e otimizar códigos funcionais para sistemas embarcados.  

──────────────────────────────────────────────────────────────────────  
## EQUIPE DO PROJETO - CONTROLE DE PINOS GPIO  
UTILIZANDO UM TECLADO MATRICIAL  
*Subgrupo 6 - Atividade 1*  
──────────────────────────────────────────────────────────────────────
