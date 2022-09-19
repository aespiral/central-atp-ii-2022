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

