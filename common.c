// common.c CORRETO
#include "common.h"

void limparBuffer() {
    int c;
    while ((c = getchar()) != '\n' && c != EOF);
}

// lerString movida para view/ler_entradas.c
/*
void lerString(char *destino, int tamanho) {
    fgets(destino, tamanho, stdin);
    destino[strcspn(destino, "\n")] = '\0';
}
*/