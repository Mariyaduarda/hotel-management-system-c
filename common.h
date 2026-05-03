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

void lerString(char *dest, int tamanho);
void limparBuffer();

#endif // COMMON_H