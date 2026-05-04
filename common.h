#ifndef COMMON_H
#define COMMON_H

/* ============================
   Ative/desative as bibliotecas aqui
   ============================ */
#define USE_STDLIB
#define USE_STRING
#define USE_CTYPE
#define USE_TIME
#define USE_MATH
#define USE_UNISTD
#define USE_FCNTL
#define USE_OPENSSL

/* ============================ */

#include <stdio.h>

#ifdef USE_STDLIB
#include <stdlib.h>
#endif
#ifdef USE_STRING
#include <string.h>
#endif
#ifdef USE_CTYPE
#include <ctype.h>
#endif
#ifdef USE_TIME
#include <time.h>
#endif
#ifdef USE_MATH
#include <math.h>
#endif
#ifdef USE_UNISTD
#include <unistd.h>
#endif
#ifdef USE_FCNTL
#include <fcntl.h>
#endif
#ifdef USE_OPENSSL
#include <openssl/sha.h>
#endif

/* ════════════════════════════════════════════════════════════════ */
/* Cores ANSI para Terminal                                         */
/* ════════════════════════════════════════════════════════════════ */
#define RESET   "\x1b[0m"
#define PRETO   "\x1b[30m"
#define VERMELHO "\x1b[31m"
#define VERDE   "\x1b[32m"
#define AMARELO "\x1b[33m"
#define AZUL    "\x1b[34m"
#define MAGENTA "\x1b[35m"
#define CIANO   "\x1b[36m"
#define BRANCO  "\x1b[37m"
#define CINZA   "\x1b[90m"

/* ════════════════════════════════════════════════════════════════ */
/* Estrutura de Endereço (unificada)                                */
/* ════════════════════════════════════════════════════════════════ */
typedef struct {
    char rua[100];
    char numero[10];
    char complemento[50];
    char bairro[50];
    char cidade[50];
    char estado[50];
    char cep[20];
} Endereco;

void lerString(char *dest, int tamanho);
void limparBuffer();

#endif // COMMON_H