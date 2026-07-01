#include <stdio.h>
#include <string.h>
#include <ctype.h>
#include "input.h"

/*
    Aqui vai ficar tds as funções de leitura
    O ideal seria n ter nenhum scanf ou funcao de leitura fora daqui
*/

// ================================================================================
// UTILS

// Limpar o buffer de entrada
void limpar_buffer_entrada(void) {
    int c;
    while ((c = getchar()) != '\n' && c != EOF);
}

// ================================================================================
// NUMEROS

// Para inteiros
int ler_int(char *prompt) {
    // Declaracao de variaveis
    int valor;
    int ok;

    // enquanto n tiver ok, tenta ler o valor
    do {
        printf("%s", prompt);
        ok = scanf("%d", &valor);
        limpar_buffer_entrada(); // limpar buffer smp q usar scanf so' pra ter ctz

        if (!ok) printf("Entrada invalida! Digite um numero inteiro.\n");

    } while (!ok);

    // Se saiu do loop e' pq ta' de boa
    return valor;
}

// Para Long
long ler_long(char *prompt) {
    // Declaracao de variaveis
    long valor;
    int ok;

    // enquanto n tiver ok, tenta ler o valor
    do {
        printf("%s", prompt);
        ok = scanf("%ld", &valor);
        limpar_buffer_entrada(); // limpar buffer smp q usar scanf so' pra ter ctz

        if (!ok) printf("Entrada invalida! Digite um numero inteiro (long).\n");

    } while (!ok);

    // Se saiu do loop e' pq ta' de boa
    return valor;
}

// Para Float
float ler_float(char *prompt) {
    // Declaracao de variaveis
    float valor;
    int ok;

    do {
        printf("%s", prompt);
        ok = scanf("%f", &valor);
        limpar_buffer_entrada();

        if (!ok) {
            printf("Entrada invalida! Digite um numero (ex: 3.14).\n");
        }
    } while (!ok);

    return valor;
}

// Para Double
double ler_double(char *prompt) {
    // Declaracao de variaveis
    double valor;
    int ok;

    do {
        printf("%s", prompt);
        ok = scanf("%lf", &valor);
        limpar_buffer_entrada();

        if (!ok) {
            printf("Entrada invalida! Digite um numero (ex: 3.14).\n");
        }
    } while (!ok);

    return valor;
}

// Para Int q ta entre dois valores
int ler_int_intervalo(char *prompt, int min, int max) {
    // Declaracao de variaveis
    int valor;

    do {
        valor = ler_int(prompt);
        if (valor < min || valor > max) {
            printf("Valor deve estar entre %d e %d.\n", min, max);
        }
    } while (valor < min || valor > max);

    return valor;
}

float ler_float_intervalo(char *prompt, float min, float max) {
    float valor;

    do {
        valor = ler_float(prompt);
        if (valor < min || valor > max) {
            printf("Valor deve estar entre %.2f e %.2f.\n", min, max);
        }
    } while (valor < min || valor > max);

    return valor;
}



// ================================================================================
// TEXTO

// Para a string
void ler_string(char *prompt, char *buffer, int tamanho) {
    printf("%s", prompt);

    if (fgets(buffer, tamanho, stdin) != NULL) {
        // Se conseguiu ler, tem q remover o \n do final
        //  ja' que fgets n tira sozinho
        int len = strlen(buffer);
        if (len > 0 && buffer[len - 1] == '\n')
            buffer[len - 1] = '\0';
        else
            limpar_buffer_entrada();


    } else {
        // Se n conseguiu ler nd, dx a string vazia
        buffer[0] = '\0';
    }
}

// Para Char
char ler_char(char *prompt) {
    // Declaracao de variaveis
    char valor, ok;

    do {
        printf("%s", prompt);
        ok = scanf(" %c", &valor);
        limpar_buffer_entrada();

        if (!ok) {
            printf("Entrada invalida! Digite um unico caractere.\n");
        }
    } while (!ok);

    return valor;
}

// ================================================================================
// OUTROS

// Para quando o usuario tem q ter ctz
int ler_confirmacao(char *prompt) {
    char resposta;

    do {
        resposta = ler_char(prompt);
        resposta = (char) tolower((unsigned char) resposta);

        if (resposta != 's' && resposta != 'n') {
            printf("Responda apenas com 's' ou 'n'.\n");
        }
    } while (resposta != 's' && resposta != 'n');

    return (resposta == 's');
}