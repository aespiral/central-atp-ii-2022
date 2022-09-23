# Aula 2 - Ponteiros

## Representação esquemática da memória

Objetivos:
- Visualizar esquematicamente o ambiente de execução de um programa
- Variáveis: globais e locais
- Execução de um programa (pilha de chamadas de função)

O arquivo [Mem_Exec_Passo_A_Passo.pdf](Mem_Exec_Passo_A_Passo.pdf) serve a dois propósitos:
- É um exemplo de representação esquemática da memória
- É um roteiro de como proceder para representar a memória esquematicamente

O programa do exemplo é o seguinte:
```c
char a = 'M';
int b;
void g(){
  b=b+1;
}
void r(int n){
  b=b+n;
}
int s(int m){
  int z=m+b;
  return z;
}
float t(int x){
  float w;
  w=s(x-2)*3.0;
  return w;
}
int main(int argc, char** argv){
  int i;
  float f;
  b=100;
  g();
  r(15);
  i=s(7);
  f=t(8);
  return 0;
}
```
Comentários sobre o arquivo [Aula-2-Mem_ria.pdf](Aula-2-Mem_oria.pdf), página a página:
1. Ponto de partida: a memória como uma tabela de endereços e conteúdos
   - A memória é representada esquematicamente como uma tabela
   - Há dois campos: endereços e conteúdos
   - Apenas os endereços são mostrados; os endereços são mostrados fora das células de memória
   - Todos os valores são mostrados em base decimal
     - É conveniente pela familiaridade
     - Quando a visualização dos bits é necessária, a representação hexadecimal tem vantagem
     - Obviamente, as representações numéricas são equivalentes, são todas corretas
   - As [folhas de memória em branco](https://github.com/codfig/mem) podem ter alterações na quantidade de colunas, quantidade de células por colunas e faixas de endereço
2.  Áreas da memória de um programa
    -   O primeiro passo é dermacar a memória em [3 áreas](https://en.wikipedia.org/wiki/Data_segment#Program_memory):
        -   Pilha (`.stack`)
            - Área principal para execução de funções
            - Nesses exemplos didáticos, deve ser a maior área
        -   Área estática (`.data`)
            - Os dados tem alocação permanente ao longo de toda a execução do programa
            - Exemplo: variáveis globais
        -   Código (`.text`)
            - Programa objeto em execução
            - Código de máquina em formato binário (o termo `.text` confunde)
        - '_Heap_ : será visto na próxima aula'
    -   Sobre a área de código
        - Todo o interesse da representação esquemática da memória de um programa reside em enteder as áreas de dados
        -   Portanto, a área de código é desconsiderada
        -   Porém, como os endereços de retorno das funções na seção de código se misturam com os dados na pilha, é conveniente representar isso, ainda que de forma muito imprecisa
        - Procedimento:
            - Numere as linhas do código fonte
            - Crie regiões na área de código para cada função
            - Observe no código fonte todas as chamadas de função
                - Se na chamada não houver nada a fazer após o retorno da função, anote a linha **seguinte** em algum ponto da área de código
                - Se na chamada ainda houver alguma ação a ser feita após o retorno da função, anote a própria linha em algum ponto da área de código com a marca: "interno" (no sentido de que é um ponto interno da linha)
3.  Primeira função: main
    - Antes do início do programa propriamente dito, as variáveis estáticas são alocadas e aquelas que devem receber um valor inicial são preenchidas
    - O sistema operacional coloca na pilha os parâmetros digitados na linha de comando e inicia a execução do programa desviando o controle para o endereço associado ao rótulo `_start`
    -   Toda chamada de qualquer função ocupa uma região da pilha com todas as informações referentes à chamada
        - Essa região é conhecida como Registro de Ativação ou _Stack Frame_
        - A função `main`, embora seja a primeira a ser chamada, é uma função como outra qualquer, e, portanto, tem um _stack frame_
        - Os detalhes de um _stack frame_ ficarão mais claros nas próximas páginas, com funções mais simples, e tudo que será visto lá pode ser conferido posteriormente neste _stack frame_ aqui
4.  Um _stack frame_ muito simples: a primeira chamada a `g`
    -   `g` é uma função muito simples, pois não tem parâmetros nem variáveis locais
    -   O _stack frame_ de `g` possui o endereço de retorno
    -   Endereço de retorno é o endereço que será executado quando a função termina
        -   Isso é necessário: **se uma função pode ser chamada de diversos pontos de um programa, como ela sabe para qual deles voltar?**
        -   Para isso, existe a pilha de chamadas, e **a pilha de chamadas é um recurso do processador**: é o processador quem coloca o endereço de retorno na pilha quando ocorre a chamada, e é o processador que retira esse endereço da pilha e desvia o fluxo de execução para ele quando a função encerra
        -   O endereço de retorno possui 32 bits (considerando uma arquitetura de 32 bits), ou 4 bytes
            - 9121 em decimal é 00000000 00000000 00100011 10100001
            - Esses valores se dividem em 4 bytes na memória do endereço de retorno
            - Na figura: 9056 - 10100001 / 9057 - 00100011 / 9058 - 00000000 /9059 - 00000000
            - A ordem inversa de distribuição tem a ver com a propriedade de _endianess_ da arquitetura: essa arquitetura é _little endian_ (o inverso seria _big endian_)
            - (A questão de _endianess_ sempre surge quando um valor precisa ser representado em unidades que são menores do que ele, ou seja, ele precisa ser quebrado, espalhado, entre elas)
        -   Na figura, em vez de representar os 4 bytes separadamente, cada um em seu endereço, optamos por ver os 4 bytes como um todo (a elipse sobrepondo) e mostrar sua interpretação assim
5.  A função se encerra, o processador pega o endereço na pilha e desvia para lá, e a pilha encolhe
    -   Pilha é uma estrutura de dados fundamental na computação, é quase o "_hello world_" das estruturas de dados
    -   Tecnicamente falando, pilhas são mecanismos LIFO (_Last In, First Out_: o último que chega é o primeiro que sai)
    -   O termo pilha é uma analogia com pilhas de prato, de livros, etc.
    -   Pilhas são naturais na execução de funções, pois:
        - Se a função `f` invoca a função `g`, a função `f` fica suspensa esperando o fim de `g`
        - `g`, por sua vez, ao invocar `h` também fica suspensa esperando `h`
        - Só que, quando `h` termina, `g` é retomada antes de `f`
        - `f`, a primeira, será a última a ser retomado, quando `g` encerrar
    -   A pilha encolhe movendo um ponteiro interno do processador
        - Os dados que estavam lá não são apagados, e ficam ali como valores residuais
        - Isso está indicado graficamente pela cor clara
    -   Lembrando que a variável global foi alterada na função
6.  A próxima chamada traz uma novidade: um parâmetro (_n_)
    -   Primeiramente, **a função main vai à pilha e coloca os parâmetros lá**
    -   Em seguida, a função `r` é invocada por meio do processador, que põe o endereço de retorno
    -   Quando a função `r` começa, ela sabe onde encontrar, na pilha, o parâmetro _n_  
7.  A função `s`, além do parâmetro, tem uma variável local, `z`
    -   As variáveis locais são reservadas pela própria função chamada, e ficam além do endereço de retorno
    -   Isso completa o _stack frame_:
        - 0 ou vários parâmetros
        - 1 endereço de retorno
        - 0 ou várias variáveis locais
8.  A função `t` chama outra função, e aqui podemos observar o leiaute da pilha com 3 _stack frames_ simultâneos
9.  De volta à `main` para terminar
