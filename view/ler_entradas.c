#include "ler_entradas.h"

void lerString(char *buffer, int tamanho) {
    // le a stringe n deixa passar do tamanho do buffer
    fgets(buffer, tamanho, stdin);

    // tira o '\n' no final da string
    buffer[strcspn(buffer, "\n")] = '\0';
}

int lerInteiro() {
    // variaveis
    char buffer[20];
    int valor;

    // enquanto n for um inteiro, continua pedindo a entrada
    while (1) {
        // le a entrada do usuario
        fgets(buffer, sizeof(buffer), stdin);

        // se e' um int, retorna ele
        if (sscanf(buffer, "%d", &valor) == 1) 
            return valor;

        // caso contrario manda erro e roda dnv
        else
            printf("[ERRO] Entrada precisa ser um numero inteiro: ");


    }
}

float lerFloat() {
    // variaveis
    char buffer[20];
    float valor;

    // enquanto n for um float, continua pedindo a entrada
    while (1) {
        // le a entrada do usuario
        fgets(buffer, sizeof(buffer), stdin);

        // se e' um float, retorna ele
        if (sscanf(buffer, "%f", &valor) == 1) 
            return valor;

        // caso contrario manda erro e roda dnv
        else
            printf("[ERRO] Entrada precisa ser um numero decimal: ");
    }
}

// fazer dps:
// funcoes pra ler CPF, data, telefone, etc tudo com valid. 