# Aula 1 - Strings

Tópicos:
- Representação em computação
- Biblioteca básica para processamento de strings
- Técnica de processamento de strings por máquinas de estados finitos

## A questão da representação em computação

Há uma diferença entre seres humanos e máquinas:
- do lado humano, há o polo da intuição, e há o polo da linguagem 
  - linguagem se manifesta como código, como convenção, através de signos, através de representação
  - nas vivências humanas, há diversas linguagens, há diversas representações, e há equivalências entre elas
- do lado da máquina, **só há** representações; computadores se caracterizam pela manipulação e transformação de representações

Exemplo dos números naturais:
- quando o ser humano pensa em um número, como `34`, ele vivencia, ao mesmo tempo, a intuição da quantidade de 34 e das representações de 34 ('34', 'trinta e quatro', XXXIV, etc.), e tudo isso se articula
- uma máquina tem apenas a representação, que, por questões de engenharia, é binária, ou seja: `100010`

### O caso MYUINT

- `MYUINT` (de _MY Unsigned INTeger_) equivale a um `unsigned short int` em C, ou seja, um valor entre 0 e 255
- `MYUINT` contém diversas representações equivalentes de um mesmo valor
```c
typedef struct {
    unsigned short int arch;
    short int dec[3];
    char dec2display[3];
    short int bin[8];
    char bin2display[8];
    short int hex[2];
    char hex2display[2]; 
} MYUINT;
```
- Acompanhe a discussão com apoio dos arquivos `myprintf.c` e `DOCUM.md`
- Os campos dessa estrutura são:
  1. `arch`, de _architecture_, isto é, a definição arquitetural da máquina
     - Sabemos que a engenharia definiu essa representação como binária, implementada em bits da máquina
     - Mas, poderíamos considerar como uma caixa-preta, como algo a que não temos acesso
       - Poderia ser a representação em números romanos, poderia ser uma coleção de palitos na quantidade correspondente
       - Considerar como caixa-preta, números romanos, coleções de palitos, etc. é um recurso retórico apenas
         - Isso pode ajudar a quebrar impressões superficiais sobre representação em computação
     - Importante:
       - Na experiência humana, temos a intuição de número natural, que não é decimal, nem binária, nem octal, nem hexadecimal, nem romana; ela apenas se articula com todas elas; 
       - Na máquina, não há a intuição, mas há, então, essa representação da máquina
         - Embora saibamos que ela é binária em bits, podemos ignorar isso e considerá-la como desconhecida, nem decimal, nem binária, nem hexadecimal, etc.
       - Exemplo: para decidir se um número é par, devemos dividi-lo por 2 e comparar o resto com 0
         - Então, dividindo-se o número-na-representação-caixa-preta-da-máquina pelo valor 2-na-representação-caixa-preta-da-máquina deve resultar em 0-na-representação-caixa-preta-da-máquina quando o número for par
         - Assim, ficamos desobrigados de saber a representação, desde que, nessa representação, nos sejam fornecidas as operações de divisão inteira e comparação com 0
         - Esse é o princípio de **Abstração** em linguagens de programação, um dos pilares da computação
  2. A coleção `dec`, de 'casas decimais'
     - A intuição humana é muito prodigiosa: frente aos algarismos '3' e '4' escritos em papel, ela pode vivenciar a ideia de 34 como um todo, ou ela pode também vivenciar a ideia do algarismo '3' como dezenas, seguido de '4' como unidades ('3' e '4' como coisas à parte)
     - A máquina tem uma representação que funciona aqui como a intuição funciona para o humano: o número como uma unidade, um todo integral, independentemente da representação
     - Dessa forma, para ter algo correspondente à vivência humana de "separar os algarismos", é preciso proceder, na máquina, à separação das casas decimais
       - Como o maior valor representável aqui é 255, apenas as casas das centenas, dezenas e unidades são necessárias
       - A separação das casas decimais é feita por meio de divisões sucessivas por 10
       - Em suma, essa representação é uma coleção de três números-na-representação-caixa-preta-da-máquina 
     - A representação `dec` pode ser aplicada em algoritmos em que as casas decimais precisam ser consideradas à parte, como coisas em si
       - Exemplo: [números de Armstrong](https://exercism.org/tracks/c/exercises/armstrong-numbers)
  3. A coleção `dec2display`, de 'casas decimais para exibição em display'
     - Uma característica de números-na-representação-caixa-preta-da-máquina é que eles não são diretamente visualizáveis na tela ou no papel (via impressão) ou legíveis por teclado ou scaneamento
       - Apenas números-na-representação-caixa-preta-da-máquina cujo valor corresponda a um 'desenho' de um caracter na tela, na impressora, no teclado, etc. podem ser exibidos
         - Essa convenção entre valor de um número e desenho exibido é um código de caracteres
         - O código de caracteres predominante é o ASCII, juntamente com suas extensões, como o UTF-8, ISO8859, etc.
     - A representação `dec2display` é uma coleção de 3 números-na-representação-caixa-preta-da-máquina que correspondem aos 'desenhos' dos três números-na-representação-caixa-preta-da máquina de `dec`
       - Isso é facilitado porque os valores em `dec` variam de 0 a 9, e, portanto, podem ser representados por um único caracter
     - A representação `dec2display` é conveniente em algoritmos que exibem valores inteiros no formato decimal, como na função `printf` com o _placeholder_ `%d` na string de controle
  4. A coleção `bin`, de 'casas binárias'
     - Equivalente a `dec`, exceto que usando a base 2
     - Consiste em 8 números-na-representação-caixa-preta-na-máquina, valendo 0 ou 1, ocupando um `short int` cada um
       - Enquanto a representação-caixa-preta-na-máquina é binária em bits, a representação `bin` é binária em `short int`s
     - É obtida por divisões sucessivas por 2
     - Útil em algoritmos que manipulam separadamente as casas binárias do número
  5. A coleção `bin2display`, de 'casas binárias para exibição em display'
     - A relação entre `bin2display` e `bin` é análoga à relação entre `dec` e `dec2display`
  6. A coleção `hex`, de 'casas hexadecimais
     - O formato hexadecimal tem estreita relação com o formato binário
       - Pode se dizer que o formato hexadecimais é um "binário compacto"
       - Isso porque cada casa hexadecimal é vinculada a 4 casas binárias **e apenas a elas**
       - Em outras palavras: a mudança de um determinado bit no formato binário influencia apenas uma casa hexadecimal, e mais ninguém
       - No formato decimal, essa propriedade não se aplica: a mudança de um bit pode alterar diversas casas decimais ao mesmo tempo
       - Assim, o desenvolvedor, após alguma prática, rapidamente entende os estados dos bits do valor a partir da representação hexadecimal
     - A representação `hex` é uma coleção de 2 casas hexadecimais
     - Para fins de representação e exibição, os valores entre 10 a 15 correspondem às letras de 'A' a 'F' (maiúsculas ou minúsculas)
       - Isso tem repercussão no procedimento de exibição dos algarismos a partir de um código de caracteres
     - É obtida por meio da divisão por 16
  7. A coleção `hex2display`, de 'casas hexadecimais para exibição em display'
     - Idem a `dec2display` e a `bin2display`
     - A transformação entre um algarismo hexadecimal na representação-caixa-preta-na-máquina e um código de caracter precisa diferenciar os valores entre 0 e 9 dos valores entre 10 e 15

Transformações entre representações de MYUINT:
- É possível converter uma representação de MYUINT em qualquer uma das demais 6, e vice-versa
- Na criação de um valor do tipo MYUINT, é natural partir da representação `arch` para definir todas as outras
- É extravagante manter todas as representações ao mesmo tempo, como em MYUINT
  - Isso é feito aqui para enfatizar o conceito
  - É de pouca utilidade, visto que todas as representações correspondem ao mesmo número
  - Ocupa espaço de memória desnecessariamente
  - É mais natural ter apenas uma representação e fazer a conversão para as demais sob demanda (isto é, quando se faz necessário)
- Exemplos:
  - `arch` -- > `dec2display` é usada pelo `printf("%d",...)` e o inverso por `scanf("%d", ...)`
  - `arch` -- > `hex2display` é usada pelo `printf("%x",...)` e o inverso por `scanf("%x", ...)`

### MYFLOAT

**É POSSÍVEL, ANALOGAMENTE, PENSAR EM TIPOS COMO MYFLOAT !!**

### MYCHAR 
```c
typedef struct {
    unsigned short int arch;
    desenho // campo oculto 
    short int dec[3];
    char dec2display[3];
    short int bin[8];
    char bin2display[8];
    short int hex[2];
    char hex2display[2]; 
} MYCHAR;
```
MYCHAR é um número como outro qualquer. Portanto, ele possui as mesmas representações como número.

A diferença de um caracter para qualquer outro número é indicada aqui como um "campo oculto", o desenho. Pelo código de caracteres, esse número, ao ser apresentado à interface com usuário (tela, papel via impressora, teclado, scanner, etc.), tem, como correlato, um "desenho".

Esse campo não é representado. A representação do desenho já é o número (`arch`). Quem sabe tornar esse campo real é a interface com usuário. 

Em outras palavras:
- para um número qualquer, só podemos ler ou escrever `dec2display`, `bin2display`, `hex2display`, 
- para caracteres, adicionalmente, podemos ler e escrever `arch` (que aparece como `desenho`), além, obviamente, de `dec2display`, `bin2display`, `hex2display`
  - `arch`/`desenho` é o acesso ao valor como interpretação; é sua razão de ser, sua utilidade
  - `dec2display`, `bin2display`, `hex2display` são acesso a `arch` como número para fins secundários

## Binário X Texto

O conceito de representação em computação esclarece as diferenças entre formatos binários e formatos baseados em texto. Isso se refere a formatos de dados em geral, e a formatos de arquivos em particular

**REGRA DOS DESENHOS: NÃO HÁ COMO TER ACESSO À REPRESENTAÇÃO DA MÁQUINA, MAS APENAS ÀS SUAS REPRESENTAÇÕES COMO DESENHOS DE CARACTERES!!**

Tudo a que se tem acesso são desenhos de caracteres, seja na tela, no papel (após impressão), ou vindo do teclado, de _scanner_ com reconhecimento de texto, etc. Não se enxerga a máquina diretamente, mas sempre há uma conversão por meio de um código de caracteres.

Podemos pensar: é como se houvesse uma "redoma" em torno da máquina. Dentro da redoma, tudo é binário (na verdade, representação-caixa-preta-na-máquina), mas isso é inacessível. Na prática, o que temos é o que "toca" a redoma e é apresentado para o lado de fora, ou seja, os desenhos dos caracteres (texto).

Em outras palavras: `arch` é inacessível, só podemos ler ou escrever `dec2display`, `bin2display`, `hex2display`, etc.

**REGRA DA MÁQUINA: NA MÁQUINA, TUDO É BINÁRIO!!**

(A rigor, seria: TUDO É REPRESENTAÇÃO-CAIXA-PRETA-NA-MÁQUINA !!, mas Ok)

Ou seja, lá na máquina, até texto também é binário.
- Um caracter é um número como outro qualquer, portanto pode ser manipulado como tal
- A diferença de um caracter para outro número qualquer, é que um caracter é um número que, quando toca a "redoma" (tela/teclado, papel/scanner), ele causa o surgimento de um 'desenho' de caracter na tela

Vamos aplicar essas regras à análise de situações: 
- **Um trecho de um arquivo é mostrado na tela no formato binário**
  - A interpretação ingênua é de estarmos de frente à realidade da máquina (`arch`), na sua forma natural (binária)
  - Na verdade, estamos vendo `bin2display` (pela Regra dos Desenhos), pois `arch`, de fato, é inacessível (Regra dos Desenhos)
- **Um programa abre um arquivo texto e soma os valores de todos os seus caracteres**
  - Pela Regra dos Desenhos, não temos acesso à realidade do arquivo, à sua representação-na-máquina
    - Considerando o tipo MYCHAR, seria a representação interna `arch`, inacessível
  - Pela Regra da Máquina, um arquivo texto também pode ser manipulado como binário

### Reconhecendo um arquivo texto

Examinando os valores contidos em um arquivo, é possível distinguir um arquivo texto de um arquivo binário em geral.

Um arquivo texto é caracterizado pela presença de uma variedade mais restrita de valores:
- Há muita ocorrência de bytes entre 97 e 122 (letras minúsculas em ASCII) e 32 (espaço em branco)
- Há uma relativa ocorrência de valores entre 65 e 90 (letras maiúsculas), e sinais de pontuação
- Há uma relativa ocorrência de valores como 10 ou 13 (nova linha)
- Há a **inexistência** de códigos em desuso em ASCII, na faixa de justamente entre 0 e 31 (exceções feitas a 10 e 13 e uns pouquíssimos mais)

## Código de caracteres

### ASCII

- _American Standar Code for Interchange of Information_
- 7 bits, 128 combinações possíveis, 128 caracteres em potencial
- Visão geral dos caracteres ( [tabela](https://www.asciitable.com)  )
  - O código 0 não é usado; em C, é representado como '\0'
  - Há uma faixa de "caracteres não imprimíveis", isto é, caracteres de controle
    - 7, _Bell_, "sinal sonoro"; em C: '\a' (de _alert_)
    - 9, _Tabulation_, "tabulação"; em C: '\t'
    - 10, _New line_, ou _line feed_, "nova linha"; em C: '\n' 
    - 13 _Carriage return_, "retorno de carro", nem sempre é implementado; em C: '\r'
      - No Windows, o '\n' é composto de 2 caracteres: 13 e 10
  - 32, espaço em branco, ' '
  - 48 a 57, algarismos de '0' a '9'
  - 65 a 90, letras maiúsculas de 'A' a 'Z'
  - 97 a 122, letras minúsculas de 'a' a 'z'
  - Sinais de pontuação espalhados entre as faixas acima
    - 127, o último código, é DEL ou ESC

### Extendidos

- ISO8859
- Unicode 
  - UTF-8

## A biblioteca `string` da LibC

- A biblioteca _string_, incluída na LibC, apresenta um conjunto de funções para manipulação de strings.
- Algumas funções notáveis:
  - `int strlen(char* s)`
  - `char* strcpy(str* s1, str* s2)`
  - `int strcmp(str* s1, str* s2)`
  - `char* strcat(str* s1, str* s2)`
- Aplicação:
```c
   // ========================================================================
   char* g = "oi";
   int tamanho_string = strlen(g);
   // ========================================================================
   // Com inteiros, faz-se:
   int val = 34;

   // Com strings, faz-se:
   char* str = "oi";
   // ========================================================================
   // Com inteiros, faz-se:
   int a = 62;
   int b;
   b = a;

   // Com strings, NÃO FUNCIONA:
   char* s = "oi";
   char t[256];
   t = s; // COPIA APENAS O PONTEIRO , NÃO FAZ A CÓPIAS DOS CARACTERES UM A UM !!

   // Em vez disso, deve-se fazer:
   char* s2 = "oi";
   char* t2;
   strcpy(t, s); // A STRING t RECEBE A CÓPIA CARACTER A CARACTER DE s
   // ========================================================================
   int c = 71;
   int d = 19;
   if (c == d) {...} 
   else if (c > d) {...}
   else if (c < d) {...};

   char* m = "oi";
   char* n = "hi";
   if (strcmp(m, n) == 0) {...}          // m == n  seria uma comparação de ponteiros, não dos caracteres
   else if (strcmp(m,n) > 0) {...}       // m na frente de n na ordem alfabética;  m > n não faz sentido
   else if (strcmp(m,n) < 0) {...}       // n na frente de m na ordem alfabética
   // ========================================================================
   int x = 5;
   int y = 7;
   y += x;     // y passa a valer 12

   char* u = "oi";
   char* v = "!!";
   strcat(u,v);   // u passa a valer "oi!!"

```
