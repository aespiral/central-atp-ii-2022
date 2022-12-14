# Aula 6 - 26/SET - P1 - Avaliação da I Unidade

## Tópicos e orientações

1. Aula 1
   - Strings
     - Conceito de representação
       - **Conferir as notas de aula sobre representação**
       - **Conferir o EX03, `myprintf`**
     - Biblioteca `string`
       - **Funções `strcpy`, `strcmp`, `strcat`**
     - ~~Técnica de MEF (Máquinas de Estados Finitos)~~
       - Será enfatizado nas avaliações P2 e P3
2. Aula 2
   - Ponteiros
     - Representação de números
     - Tipos de ponteiros
     - Desenho da memória
       - Área estática
       - Pilha
         - Stack frame
     - Aplicação
       - Passagem de parâmetros por referência 
3. _Aula 3_  ORIENTAÇÕES EM CONSTRUÇÃO A PARTIR DAQUI
   - _Alocação dinâmica_ 
     - _Tempo de vida_ 
     - _Heap_
     - _malloc e free_ 
     - _Type casting_
4. _Aula 4_
   - _Uso de passagem por referência e alocação dinâmica em bibliotecas_ 
   - _Introdução a arquivos_
     - _FILE, fopen (modos r, w, a, r+, w+, a+), fclose_
     - _fgetc, fputc_ 

## Exercícios de Revisão

1. Sobre representação de dados em computação:
   - Sabe-se que um número inteiro sem sinal é representado na máquina de forma binária por questões de engenharia. Por que essa informação não é tão relevante na atividade de um programador no dia a dia?
   - Cite um exemplo de utilidade da representação `dec` de um valor do tipo MYUINT
   - Explique como é preenchida a representação `hex2display` no código de `myprintf`. Qual pode ser uma aplicação da representação `hex2display`?
   - Explique a frase: "Um caracter é um número como outro qualquer, mas também pode ter aspectos próprios."
   - Considere a situação: "Um programador usa um editor de arquivos binários para alterar dados de um arquivo. Ele decide visualizar os dados usando a representação decimal. Um colega sugere que a representação binária seria mais correta porque os computadores são binários. O programador não responde, apenas ri e pensa para si: 'decimal, hexadecimal, binária: tanto faz!' " Por que o programador está correto em usar a representação que mais lhe convém?

2. Considere a representação `bin` no tipo MYUINT. Ela consiste em um array de 8 posições contendo um valor que pode ser 0 ou 1 (como um `short int`)
   - Faça um programa que converte um valor em `bin` para a representação nativa da máquina (`arch`), isto é, um único valor
     - `arch = bin[7]*2^7 + bin[6]*2^6 + ... + bin[1]*2^1 + bin[0]^1`
     - Essa conversão é a mesma da avaliação de um polinômio em um certo ponto (confira a biblioteca `poli.c`)
     - Essa conversão pode ser feita de modo a mininizar o número de operações de multiplicação a serem realizadas; a diferença entre os procedimentos é mostrada abaixo para valores de 4 bits
```
1101
Algoritmo 1:
1*2*2*2 + 1*2*2 + 0*2 + 1
-> 6 multiplicações

Algoritmo 2:
((1*2 + 1)*2 + 0)*2 + 1
-> 3 multiplicações

Algoritmo 2 como execução de um laço passo a passo (caso de 4 bits):
arch =          bin[3];
arch = arch*2 + bin[2];
arch = arch*2 + bin[1];
arch = arch*2 + bin[0];
```

3. Representação de números
   - Considere a representação de números negativos proposta na _struct_ abaixo:
```c 
typedef struct {
  bool sinal;
  unsigned short int magnitude;
} SMINT;
```
   - Qual a faixa de valores possíveis com essa representação? Considere que o compilador C usa um byte para implementar um valor do tipo `unsigned short int` (modernamente, os compiladores usam 2 bytes)
   - Quantos valores ao todo são representados?
   - Crie uma função em C para somar dois valores do tipo SMINT
     - `SMINT* soma(SMINT* a, SMINT* b)`

4. Lib _string_

Considere o seguinte programa:
```c
#include <stdio.h>
int main() {
    char s[256] = "oi";
    char* t;

    printf("Valor de s: '%s'\n\n", s);

    t = s;

    printf("Valor de t: '%s'\n", t); 
}
``` 
A execução do programa é mostrada abaixo:
```
Valor de s: 'oi'

Valor de t: 'oi'
```
Comente a afirmação: "É possível copiar uma string sem recorrer à biblioteca _string_."

5. Representação
Crie uma função para multiplicar um valor do tipo MYUINT por 10 usando exclusivamente a representação `dec`.
- `MYUINT* vezes10(MYUINT* v);`

6. Arquivos JSON

O formato de arquivos JSON (_JavaScript Object Notation_) é amplamente usado na troca de informações entre páginas abertas em navegadores e seus respectivos servidores.

O conteúdo de um arquivo JSON é mostrado aqui:
```
{ "idade" : 18,
  "peso" : 70,
  "altura" : 179}
```
Ao importar os dados do arquivo para a memória de um programa, os valores numéricos ali presentes precisam ser registrados em variáveis. Considerando variáveis do tipo MYUINT, que possuem diversas representações do mesmo número, da forma mais variada possível, e todas elas equivalentes entre si, é possível afirmar que os valores numéricos do arquivo JSON já se encontram completamente na **forma de uma das representações de MYUINT**. Comente.

7. Considere o seguinte programa:
```c
void soma(int* total, int* dados, int tam){
  int n;
  int ptr_aux = dados;
  *total = 0;
  for(n=0; n<tam; n++) {
    *total = *total + *ptr_aux;
    ptr_aux = ptr_aux + 1;
  }
}
int main() {
  int ar[3];
  int z;
  int * p = &ar[0];
  int i;
  for(i=0; i<3; i++) {
    *(p+i) = (i+3)*(i+3);
  }
  soma(&z, p, 3);
}

Mostre a representação esquemática de memória da execução desse programa no exato momento em que a função `soma` está para terminar. Use [uma página que ilustra a memória](mem.pdf).
