#ifndef ACOMODACAO_H
#define ACOMODACAO_H

#include "../common.h"

/* ── Acomodação ─────────────────────────────────────────── */
typedef struct {
    int  id;
    char descricao[100];
    char facilidades[200];  // "TV, Ar-condicionado, Frigobar..."
    int  idCategoria;       // referencia a TipoCategoria
    int  ativo;
} TipoAcomodacao;

typedef struct ListaAcomodacao {
    TipoAcomodacao acomodacao;
    struct ListaAcomodacao *proximo;
} ListaAcomodacao;

/* ── Acomodação: funções ────────────────────────────────── */
void            AcomodacaoInit(TipoAcomodacao *acom);
int             AcomodacaoCriar(ListaAcomodacao **lista, TipoAcomodacao acom);
TipoAcomodacao *AcomodacaoBuscar(ListaAcomodacao **lista, int id);
void            AcomodacaoListar(ListaAcomodacao **lista, int id,
                                  ListaCategoria **listaCat);
int             AcomodacaoExcluir(ListaAcomodacao **lista, int id);
int             AcomodacaoAtualizar(ListaAcomodacao **lista, int id, int op);
void            AcomodacaoListaLiberar(ListaAcomodacao *lista);

int  AcomodacaoSalvarBin(ListaAcomodacao *lista);
int  AcomodacaoLerBin(ListaAcomodacao **lista);
int  AcomodacaoSalvarTxt(ListaAcomodacao *lista);
int  AcomodacaoLerTxt(ListaAcomodacao **lista);

#endif // ACOMODACAO_H