#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <stdbool.h>
#include <time.h>

typedef struct{
    char nome[64];
    bool presente;
    short int rodada;
} PARTICIPANTE;

int main(){
    // Abre arquivo turma.txt ou alternativo fornecido pelo usuário ou termina
    char arquivo[256];
    strcpy(arquivo, "turma.txt");
    FILE* fp = fopen(arquivo, "r+");
    while (fp == NULL) {
        printf("Arquivo '%s' não encontrado.\nDigite outro nome de arquivo ou 'sair': ", arquivo);
        scanf("%s", arquivo);
        if (strcmp(arquivo, "sair")==0)
            exit(0);
        fp = fopen(arquivo, "r+");
    }

    // Conta número de participantes  TODO: conta linhas em branco indevidamente
    int quant = 0;
    char ch;
    while((ch = fgetc(fp))!= EOF){
        if(ch == '\n')
            quant++;
    }

    // Copia nomes dos participantes
    PARTICIPANTE* parts = (PARTICIPANTE*) malloc( (quant+1) * sizeof(PARTICIPANTE) ); //+1 Previne o caso da última linha não terminar com \n
    fseek(fp, 0, SEEK_SET); // Reposiciona o cursor início do arquivo
    #define PAROU 0
    #define ESP_EOL_EOF 1
    #define ESP_ALFA_EOF 2
    #define EOL '\n'
    int est = ESP_ALFA_EOF;
    int vez = 0;
    int k = 0;
    while (est != PAROU) {
        switch (est) {
            case ESP_EOL_EOF:
                ch = fgetc(fp);
                if (ch == EOL) {
                    parts[vez].nome[k] = '\0';
                    vez++;
                    k=0;
                    est = ESP_ALFA_EOF;
                } else if (ch == EOF) { // arquivo termina sem um newline
                    parts[vez].nome[k] = '\0';
                    quant++;
                    est = PAROU;
                } else {
                    parts[vez].nome[k] = ch;
                    k++;
                }
                break;
            case ESP_ALFA_EOF:
                ch = fgetc(fp);
                if (ch == EOF) {
                    est = PAROU;
                } else if (ch != EOL) {
                    parts[vez].nome[k] = ch;
                    k++;
                    est = ESP_EOL_EOF;
                } else {
                    quant--; // Achou uma linha em branco
                }
                break;
        }
    }

    // SORTEIO
    int num, i, j;
    bool achou;
    int* sorteados = (int*)malloc(quant*sizeof(int));

    srand(time(NULL));

    for(i = 0; i < quant; i++){
        num = rand() % quant;
        achou=false;
        for(j=0; j<i; j++){
            if(num==sorteados[j]){
                achou=true;
            }
        }

        if(achou){
            i--;
            continue;
        }
        sorteados[i]=num;
 
        printf("%s", parts[num].nome);
        if (i < quant-1) {
            printf(" +");
            ch=getchar();
        } else {
            printf("\n");
        }
    }

    free(sorteados);
    free(parts);
    fclose(fp);

}