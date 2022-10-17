#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>
#include <time.h>

typedef struct _cel {
    int p;   // Primeiro elemento
    struct _cel * r;  // Resto
} CEL;

#define VAZIA NULL

CEL* cons(int elem, CEL* lst) {
    CEL* nova = (CEL*) malloc(sizeof(CEL));
    nova->p = elem;
    nova->r = lst;
    return nova;
}

CEL* inverter_aux(CEL* lst, CEL* acm) {  // acm ~ acumulador
    if (lst == VAZIA)
        return acm;
    else
        return inverter_aux(lst->r, cons(lst->p, acm));
}

CEL* inverter(CEL* lst) {
    return inverter_aux(lst, VAZIA);
}

CEL* lista_de_array_aux(int* ar, int n, CEL* acm) {
    if (n == 0)
        return inverter(acm);
    else
        return lista_de_array_aux(ar+1, n-1, cons(ar[0], acm));
}

CEL* lista_de_array(int* ar, int n) {
    return lista_de_array_aux(ar, n, VAZIA);
}

int compr(CEL* lst) {
    if (lst == VAZIA)
        return 0;
    else
        return 1 + compr(lst->r);
}

void array_de_lista_aux(CEL* lst, int* ar, int i) {
    ar[i] = lst->p;
    if (lst->r != VAZIA)
        array_de_lista_aux(lst->r, ar, i+1);
}

int* array_de_lista(CEL* lst, int* n) { // n: para retornar tamanho do array
    int tam = compr(lst);
    int* ar = (int*) malloc( tam * sizeof(int) );
    array_de_lista_aux(lst, ar, 0);
    *n = tam;
    return ar;
}

CEL* lista_de_array_iterativo(int* ar, int n) {
    CEL* lst = VAZIA;
    int i;
    for(i=n-1; i>=0; i--) 
        lst = cons(ar[i], lst);
    return lst;
}

CEL* lista_aleatoria(int n) {
    srand(time(NULL));
    int* arr = (int*) malloc(n * sizeof(int));
    int i;
    for(i=0; i<n; i++)
        arr[i] = rand()%256 - 32;   // faixa de -32 a + 223
    CEL* res = lista_de_array(arr,n);
    free(arr);
    return res;
}

void mostra_lista(CEL* lst) {
    if (lst == VAZIA) 
        putchar('\n');
    else {
        printf("%d ", lst->p);
        mostra_lista(lst->r);
    } 
}

void libera_lista(CEL* lst) {
    if (lst != VAZIA) {
        CEL* tmp = lst->r;
        free(lst);
        libera_lista(tmp);
    }
}

int soma(CEL* lst) {
    if (lst == VAZIA)
        return 0;
    else 
        return lst->p + soma(lst->r);
}

int max(CEL* lst) {
    return 0; // TODO
}

int min(CEL* lst) {
    return 0; // TODO
}

bool todos_pares(CEL* lst) {
    return true; // TODO
}

bool existe_negativo(CEL* lst) {
    return true; // TODO
}

CEL* dobrar(CEL* lst) {
    if (lst == VAZIA) 
        return VAZIA;
    else 
        return cons(2*lst->p, dobrar(lst->r));
}

// remover a primeira ocurrência
// remover 3 (4 3 8 10 3 5 3)   >>>   (4 8 10 3 5 3)
CEL* remover(int elem, CEL* lst) {
    if (lst == VAZIA)
        return VAZIA;
    else if (elem == lst->p)
        return lst->r;
    else
        return cons(lst->p, remover(elem, lst->r));
}

// remover todos
// remover 3 (4 3 8 10 3 5 3)   >>>   (4 8 10 5)
CEL* remover_todos(int elem, CEL* lst) {
    if (lst == VAZIA)
        return VAZIA;
    else if (elem == lst->p)
        return remover_todos(elem, lst->r);
    else
        return cons(lst->p, remover_todos(elem, lst->r));
}

// remover pares
// remover_pares (4 3 8 10 3 5 3)   >>>   (4 8 10)
CEL* remover_pares(CEL* lst) {
    if (lst == VAZIA)
        return VAZIA;
    else if (lst->p%2==0)
        return remover_pares(lst->r);
    else
        return cons(lst->p, remover_pares(lst->r));
}

// gaguinho (stammer)
// gaguinho (7 4 3 0)    >>>>    (7 7 4 4 3 3 0 0)
CEL* gaguinho(CEL* lst) {
    if (lst == VAZIA)
        return VAZIA;
    else
        return cons(lst->p, cons(lst->p, gaguinho(lst->r)));
}

// mantem posições ímpares
// impares (2 10 5 4 0 1)   >>>  (2 5 0)
// impares (1 2 3)    >>>  (1 3)
CEL* impares(CEL* lst) {
    if (lst == VAZIA)
        return VAZIA;
    else if (lst->r == VAZIA)
        return lst;
    else
        return cons(lst->p, impares(lst->r->r));
}

// mantem posições pares
// impares (2 10 5 4 0 1)   >>>  (10 4 1)
// impares (1 2 3)    >>>  (2)
CEL* pares(CEL* lst) {
    return VAZIA; //TODO
}

// alterna posicoes de 2 em 2
// impares (2 10 5 4 0 1)   >>>  (10 2 4 5 1 0)
// impares (1 2 3)    >>>  (2 1 3)
CEL* alternar(CEL* lst) {
    return VAZIA; //TODO
}

// substitui um valor por outro
// subustituir 1 4 (3 2 1 2)   >>>  (3 2 4 2)
CEL* substituir(CEL* lst) {
    return VAZIA;
}

// todos valores que são sucessores de um valor 
// segue 1 (2 1 3 1 4 1 2 4)   >>>  (3 4 2)
// segue 2 (1 2 3 2 4 2)    >>>  (2 4 -1)  se for o último, retorna -1
CEL* segue(int elem, CEL* lst) {
    return VAZIA; //TODO
}

// concatena duas listas recursivamente
// (1 2 3)  (4 5)   >>>  (1 2 3 4 5)
CEL* append(CEL* lst1, CEL* lst2) {
    return VAZIA;
}

// combina duas listas, alternando os valores
// (1 8 100) (9 3 2)    >>>    (1 9 8 3 100 2)
// (4 10) (1 2 0 7)    >>>    (4 1 10 2 0 7)
CEL* ziper(CEL* lst1, CEL* lst2) {
    return VAZIA;
}

// mantém x elementos iniciais
CEL* take(int n, CEL* lst) {
    return VAZIA;
}

// remove x elementos iniciais
CEL* drop(int n, CEL* lst) {
    return VAZIA;
}

int main() {
    int a2[7] = {4, 10, 8, 16, 3, 50, 50};
    CEL* lista2 = lista_de_array(a2, 7);
    CEL* lista3 = impares(lista2);
    mostra_lista(lista2);
    mostra_lista(lista3);

}