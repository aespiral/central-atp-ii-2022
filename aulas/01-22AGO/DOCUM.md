# myprintf
Código-ensaio sobre representação de números e caracteres, com ênfase na representação em ASCII.
Essay-as-code about number and character representation, featuring ASCII representation.

## Tipos / Types

Resumo / summary:
- MYUINT
- MYINT
- MYFLOAT
- MYCHAR

Um valor em qualquer tipo é uma agregação de representações. 

### MYUINT

Inteiro sem sinal na faixa de 0 a 255.

As representações agregadas no registro são:
- A representação como `unsigned short int` da Linguagem C
    - Representação binária em bits
    - Representação do processador/arquitetura
- Representação decimal
    - 3 algarismos: centenas, dezenas e unidades
    - Cada algarismo é um inteiro de 0 a 9 (short int)
- Representação decimal em ASCII
- Representação binária em bytes
    - 8 algarismos 
    - Cada algarismo é o inteiro 0 ou o inteiro 1 (short int)
- Representação binária em ASCII
- Representação hexadecimal
    - 2 algarismos: "dezesseizenas" e unidades
    - Cada algarismo é um inteiro de 0 a 15 (short int)
- Representação hexadecimal em ASCII

### MYINT

Inteiro com sinal na faixa de -128 a 127.

As representações agregadas no registro são:
- A representação como `short int` da Linguagem C
    - Representação binária em bits, segundo o código de complemento de 2
    - Representação do processador/arquitetura
- Representação decimal
    - Sinal, como booleano, sendo `true` correspondente a `+`
    - Módulo, como MYUINT

### MYFLOAT_DEC

Número real na faixa de +/- 0,0100 até +/- 19,9, como notação científica em base 10

A representação principal contém os seguintes campos:
- Sinal, como booleano, sendo `true` correspondente a `+`
- Mantissa, como MYUINT, na faixa de 100 a 199
- Expoente, como MYINT, na faixa de -4 a -1
- Parte inteira, como MYUINT
- Parte fracionária, como MYINT

Exemplo:
```
MYFLOAT_DEC* f = make_FLOATD(true, 150, -2);

Sinal: true , que representa +
Mantissa: 150
Expoente: -2

numero: 150 x 10^-2 = 1.5 (ou 1.5000)

Parte inteira: 1
Parte fracionaria: 5000
```