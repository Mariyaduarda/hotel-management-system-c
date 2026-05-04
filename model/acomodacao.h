#ifndef ACOMODACAO_H
#define ACOMODACAO_H

#include "../common.h"
#include "categoria_acomodacao.h"   /* TipoCategoria e ListaCategoria */

typedef struct {
    int  id;
    int  idCategoria;               /* FK → TipoCategoria.id */
    char descricao[100];
    char facilidades[200];
    int  ativo;
} TipoAcomodacao;

typedef struct ListaAcomodacao {
    TipoAcomodacao          acomodacao;
    struct ListaAcomodacao *proximo;
} ListaAcomodacao;

void            AcomodacaoInit          (TipoAcomodacao *acom);
int             AcomodacaoCriar         (ListaAcomodacao **lista, TipoAcomodacao acom);
TipoAcomodacao *AcomodacaoBuscar        (ListaAcomodacao **lista, int id);
void            AcomodacaoListar        (ListaAcomodacao **lista, int id,
                                         ListaCategoria **listaCat);
int             AcomodacaoExcluir       (ListaAcomodacao **lista, int id);
int             AcomodacaoAtualizar     (ListaAcomodacao **lista, int id, int op);
void            AcomodacaoListaLiberar  (ListaAcomodacao *lista);
int             AcomodacaoSalvarTxt     (ListaAcomodacao *lista);
int             AcomodacaoSalvarBin     (ListaAcomodacao *lista);
int             AcomodacaoLerTxt        (ListaAcomodacao **lista);
int             AcomodacaoLerBin        (ListaAcomodacao **lista);

#endif