# Aula 5 - Continuação de Arquivos - Roteiro e Notas

## Exercício `sorteio`

1. Considere o programa `sorteio.c` e o arquivo `turma.txt`. 
   - Compile e execute para entender
   - O arquivo é acessado no modo texto e lido caracter a caracter com `fgets`
   - Há uma MEF para copiar os nomes em um array

2. Crie uma versão baseada na leitura e escrita de arquivos
   - O programa é invocado, mostra um nome e termina
   - Nesse processo, ele lê um arquivo de nomes ainda não sorteados, realiza o sorteio, mostra o nome, remove o nome do arquivo e o escreve em outro arquivo de nomes já sorteados.
   - Se não existir o arquivo `turma.txt`, o programa encerra com mensagem de erro.
   - Se não existirem os arquivos `turma-ainda.txt` e `turma-jah.txt`, o programa os cria, copiando o conteúdo de `turma.txt` completamente para `turma-ainda.txt`
   - Se o arquivo `turma-ainda.txt` estiver vazio, uma mensagem de orientação deve ser mostrada.

3. \[Opcional\] Crie uma versão que registra ausências.
   - Após exibir o nome sorteado, o programa não termina, esperando um comando.
   - Se o usuário digitar ENTER, o programa funciona usualmente, movendo o nome entre arquivos e encerrando.
   - Se o usuário digitar 'a' ou 'A', o programa move o nome para um terceiro arquivo (`turma-ausentes.txt`), e exibe o próximo nome sorteado, passando a esperar um comando em seguida.
   - Se o programa for invocado com um argumento no comando de linha (como, por exemplo. `$./sorteio Dionisia`), ele processa a chegada atrasada de um participante que já havia estado ausente, movendo o nome entre arquivos e dando prosseguimento usual ao sorteio.

## Acesso a arquivos no modo binário

1. Dois arquivos no formato binário são fornecidos: `bytes.bin` e `words.bin`
   - Exiba os conteúdos de ambos os arquivos como números inteiros na tela, o primeiro como um conjunto de `short int`, e o segundo, de `int`; mostre um valor por linha.

2. Escolha um dos arquivos, carregue os valores em um array, ordene os valores, e salve em um novo arquivo.

## Ordenação por seleção (_selection sort_)

Ordenar um array de _n_ inteiros
```
Algoritmo:
|   mova o foco (cursor) para o primeiro elemento
|   repita:
|   |   busque o menor elemento do array entre o elemento seguinte ao cursor e o fim do array
|   |   se o menor elemento encontrado for menor que o elemento no foco:
|   |   |   então: troque o elemento encontrado com o elemento no foco
|   |   fim_se
|   |   avance o cursor para o próximo elemento
|   |   se o cursor for o último elemento:
|   |   |   interrompa
|   |   fim_se
|   fim_repita
|   exiba o array ordenado
fim_algoritmo
```

## Orientações sobre a avaliação P1

Ver Aula 6: o arquivo myprintf-rascunho tem a ver

## Biblioteca para desenho em PDF : cairo

Em construção