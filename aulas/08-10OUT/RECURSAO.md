# Recursão

## Dados com estrutura recursiva: listas

-   Lista pode ser:
    -   vazia
    -   constituída de 1 ou mais células
-   Cada célula contém uma unidade de dado e um ponteiro para uma outras células (ou lista vazia)
-   No último elemento, a próxima célula é uma lista vazia

## Lógica de programação

Ao processar listas:
-   crie funções recursivas para listas
-   considere que o acesso é apenas ao primeiro elemento (tudo o que pode ser feito, restringe-se ao primeiro elemento)
-   considere que o resto dos elementos já foram processados pela chamada recursiva da própria função em construção
-   crie o resultado final combinando o processamento do primeiro elemento com o resultado pronto da chamada recursiva sobre o resto dos elementos

## Biblioteca de testes : cunit