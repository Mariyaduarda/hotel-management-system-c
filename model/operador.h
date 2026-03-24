#ifndef OPERADOR_H
#define OPERADOR_H
#include <string.h>   // 👈 ADICIONA ISSO

// declaracao da estrutura Operador
typedef struct {
    int id;
    char usuario[100];
    char senha[65]; // para SHA256, 64 caracteres + 1 para o terminador nulo
    char nome[100];
} Operador;

// prototipos para Operador
void criarOperador();
const Operador* obterOperador(void);

#endif // OPERADOR_H