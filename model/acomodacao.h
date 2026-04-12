#ifdef ACOMODACAO_H 
#define ACOMODACAO_H

#include "../common.h"
// No seu arquivo common.h ou acomodacao.h

typedef struct {
    int id;
    char descricao[50]; // Ex: Luxo, Standard, Econômica
    float valorDiaria;
} TipoCategoria;

typedef struct {
    int id; // Código único
    char descricao[100];
    char facilidades[200]; // TV, Ar-condicionado, Frigobar...
    TipoCategoria categoria; // Aqui entra a categoria pré-cadastrada
    int ativo;
} TipoAcomodacao;

// E a estrutura da lista, igual você fez com Hóspede
typedef struct ListaAcomodacao {
    TipoAcomodacao acomodacao;
    struct ListaAcomodacao *proximo;
} ListaAcomodacao;



#endif //ACOMODACAO_H