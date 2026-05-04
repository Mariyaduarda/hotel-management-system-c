// view/acomodacao_view.h
#ifndef ACOMODACAO_VIEW_H
#define ACOMODACAO_VIEW_H

#include "../model/acomodacao.h"
#include "../model/categoria_acomodacao.h"

void AcomodacaoMenuExibir(void);

void AcomodacaoCadastrarView(ListaAcomodacao **lista,
                              ListaCategoria  **listaCat);

void AcomodacaoListarView(ListaAcomodacao **lista,
                           ListaCategoria  **listaCat);

void AcomodacaoAtualizarView(ListaAcomodacao **lista,
                              ListaCategoria  **listaCat);

void AcomodacaoExcluirView(ListaAcomodacao **lista);

void AcomodacaoBuscarView(ListaAcomodacao **lista,
                           ListaCategoria  **listaCat);

#endif // ACOMODACAO_VIEW_H