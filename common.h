/* --------------------------------------
    common.h - header file para a biblioteca de funções do projeto
   --------------------------------------

   -- incluir APENAS arquivos em arquivos .c
        #include "common.h" no main.c
        #include"../common.h" em subpastas
*/

#ifndef COMMON_H
#define COMMON_H

/* 1. PADRAO LING. C*/ 
#include <stdio.h>      /* printf, scanf, fopen, fclose, fgets... */

#ifdef USE_STDLIB
    #include <stdlib.h>     /* malloc, free, atoi, atof, exit...      */
#endif

#ifdef USE_STRING
    #include <string.h>     /* strcpy, strcmp, strlen, memset...      */
#endif

#ifdef USE_CTYPE
    #include <ctype.h>      /* isdigit, isalpha, toupper, tolower...  */
#endif

#ifdef USE_TIME
    #include <time.h>       /* time, localtime, mktime (datas)        */
#endif

#ifdef USE_MATH
    #include <math.h>       /* round, floor, ceil, pow               */
#endif

#ifdef USE_VALIDACAO
    #include <validacao.h>       
#endif

#endif // BIBLIOTECA_H