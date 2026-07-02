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
#define USE_CAIXA

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
#ifdef USE_CAIXA
#include "model/caixa.h"
#endif

/* Terminal color macros used by views */
#ifndef RESET
#define RESET "\x1b[0m"
#endif
#ifndef VERDE
#define VERDE "\x1b[32m"
#endif
#ifndef VERMELHO
#define VERMELHO "\x1b[31m"
#endif
#ifndef AMARELO
#define AMARELO "\x1b[33m"
#endif
#ifndef CIANO
#define CIANO "\x1b[36m"
#endif
#ifndef CINZA
#define CINZA "\x1b[90m"
#endif
#ifndef NEGRITO
#define NEGRITO "\x1b[1m"
#endif

/* ════════════════════════════════════════════════════════════════ */
/* Estrutura de Endereco (unificada)                                */
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

// ==================================================
// Utilitarios
void limparTela();

void pausar();

void limparBuffer();
int dataParaInt(const char* data);

/* View helpers used by common utilities */
void ViewEntradaInvalida(void);

// ==================================================
// Leitura de dados

// numeros
int    ler_int(char *prompt);
long   ler_long(char *prompt);
float  ler_float(char *prompt);
double ler_double(char *prompt);

// numeros com intervalo
int   ler_int_intervalo(char *prompt, int min, int max);
float ler_float_intervalo(char *prompt, float min, float max);

// texto
void ler_string(char *prompt, char *buffer, int tamanho);
char ler_char(char *prompt);

// outros
int ler_confirmacao(char *prompt);

// ==================================================

#endif // COMMON_H