#include <stdio.h>
#include <stdlib.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>

typedef struct {
    unsigned short int arch;
    short int dec[3];
    char dec2display[3];
    short int bin[8];
    char bin2display[8];
    short int hex[2];
    char hex2display[2]; 
} MYUINT;

char alg2ascii(short int a) {
    return a < 10 ? a + '0' : a - 10 + 'A';
}

short int ascii2alg(char c) {
    if (c > '0' && c < '9')
        return c - '0';
    if (c > 'A' && c < 'F')
        return c - 'A' + 10;
    return -1;
}

MYUINT* make_UINT(int num) {
    if (num < 0 || num > 255) 
        return NULL;
    MYUINT* res = (MYUINT*) malloc(sizeof(MYUINT));
    if (res == NULL)
        return NULL;
    res->arch = num; //(unsigned short int) num;
    int i;
    short int val;
    for(i=2, val=num; i>=0; i=i-1, val=val/10) {
        res->dec[i] = val % 10;
        res->dec2display[i] = alg2ascii(res->dec[i]);
    }
    for(i=7, val=num; i>=0; i=i-1, val=val/2) {
        res->bin[i] = val % 2;
        res->bin2display[i] = alg2ascii(res->bin[i]);
    }
    for(i=1, val=num; i>=0; i=i-1, val=val/16) {
        res->hex[i] = val % 16;
        res->hex2display[i] = alg2ascii(res->hex[i]);
    }
    return res;
}

void myprintf(char* str, MYUINT* val);

int main(int argc, char** argv) {
    MYUINT* n1 = make_UINT(34);

/*
    myprintf("O valor em decimal eh %d\n", n1);
    myprintf("O valor em binario eh %bB\n", n1);
    myprintf("O valor em hexadecimal eh %xH\n", n1);

>>> O valor em decimal eh 34 
>>> O valor em binario eh 00100010B
>>> O valor em hexadecimal eh 22H 
*/
}