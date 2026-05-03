#include "common.h"

void limparBuffer() {
    int c;
    while ((c = getchar()) != '\n' && c != EOF);
}

void lerString(char *destino, int tamanho) {
    setbuf(stdin, NULL); // Limpa o buffer de entrada
    fgets(destino, tamanho, stdin); // Lê a string, incluindo espaços
    destino[strcspn(destino, "\n")] = '\0'; // Remove o caractere de nova linha
}