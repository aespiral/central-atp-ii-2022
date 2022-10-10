#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>
#include <time.h>
#include <CUnit/Basic.h>

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

CEL* lista = VAZIA;
CEL* lista_pares = VAZIA;

int prepara_suite(void) {
    int a[7] = {12, 20, 19, 80, 1, 42, 7};
    lista = lista_de_array(a, 7);
    int array_pares[6] = {10, 8, -2, 30, 0, 4};
    lista_pares = lista_de_array(array_pares, 6);
    return 0;
}

int finaliza_suite(void) {
    libera_lista(lista);
    libera_lista(lista_pares);
    return 0;
}

void teste_soma(void) {
    CU_ASSERT(181 == soma(lista));
    CU_ASSERT(50 == soma(lista_pares));
}

void teste_compr(void) {
    CU_ASSERT(7 == compr(lista));
    CU_ASSERT(6 == compr(lista_pares));
}

void teste_max(void) {
    CU_ASSERT(80 == max(lista));
    CU_ASSERT(30 == max(lista_pares));
}

void teste_min(void) {
    CU_ASSERT(1 == min(lista));
    CU_ASSERT(-2 == min(lista_pares));
}

void testes_todos_pares(void) {
    CU_ASSERT( !todos_pares(lista) );
    CU_ASSERT( todos_pares(lista_pares) );
    CU_ASSERT( !existe_negativo(lista) );
    CU_ASSERT( existe_negativo(lista_pares) );
}

int main() {

   /* Abre o cartório (tenta) */
   if (CUE_SUCCESS != CU_initialize_registry())
      return CU_get_error();
 
   /* Cadastra a suíte de testes */
   CU_pSuite pSuite = CU_add_suite("Funções de resultados numéricos e booleanos", prepara_suite, finaliza_suite);
   if (NULL == pSuite) {
      CU_cleanup_registry();
      return CU_get_error();
   }

   /* Adiciona os testes à suíte de testes */
   if ((NULL == CU_add_test(pSuite, "teste do comprimento", teste_compr)) ||
       (NULL == CU_add_test(pSuite, "teste da soma", teste_soma)) ||
       (NULL == CU_add_test(pSuite, "teste de max", teste_max)) ||
       (NULL == CU_add_test(pSuite, "teste da min", teste_min)) ||
       (NULL == CU_add_test(pSuite, "teste de todos/existe", testes_todos_pares)))
   {
      CU_cleanup_registry();
      return CU_get_error();
   }

   /* Roda os testes na interface básica */
   CU_basic_set_mode(CU_BRM_VERBOSE);
   CU_basic_run_tests();

   /* Finalização */
   CU_cleanup_registry();
   return CU_get_error();
}