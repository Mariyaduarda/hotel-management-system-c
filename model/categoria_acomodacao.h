#ifndef CATEGORIA_ACOMODACAO_H
#define CATEGORIA_ACOMODACAO_H

#include "../common.h"

typedef struct {
    int   id;
    char  descricao[100];
    float valorDiaria;
    int   maxAdultos;
    int   maxCriancas;
    int   ativo;
} TipoCategoria;

typedef struct ListaCategoria {
    TipoCategoria          categoria;
    struct ListaCategoria *proximo;
} ListaCategoria;

void           CategoriasInit        (TipoCategoria *cat);
int            CategoriaCriar        (ListaCategoria **lista, TipoCategoria cat);
TipoCategoria *CategoriaBuscar       (ListaCategoria **lista, int id);
void           CategoriaListar       (ListaCategoria **lista, int id);
int            CategoriaExcluir      (ListaCategoria **lista, int id);
int            CategoriaAtualizar    (ListaCategoria **lista, int id, int op);
void           CategoriaListaLiberar (ListaCategoria *lista);
int            CategoriaSalvarTxt    (ListaCategoria *lista);
int            CategoriaSalvarBin    (ListaCategoria *lista);
int            CategoriaLerTxt       (ListaCategoria **lista);
int            CategoriaLerBin       (ListaCategoria **lista);

#endif