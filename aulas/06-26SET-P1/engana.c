#include <stdio.h>
int main() {
    char s[256] = "oi";
    char* t;

    printf("Valor de s: '%s'\n\n", s);

    t = s;

    printf("Valor de t: '%s'\n", t); 
}