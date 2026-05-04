#ifndef ACOMODACAO_CONTROLLER_H
#define ACOMODACAO_CONTROLLER_H

#include "../model/acomodacao.h"

/* ── Categoria ──────────────────────────────────────────── */
int            controllerCategoriaCadastrar(ListaCategoria **lista, TipoCategoria cat);
TipoCategoria *controllerCategoriaBuscar(ListaCategoria **lista, int id);
int            controllerCategoriaAtualizar(ListaCategoria **lista, int id, int op);
int            controllerCategoriaExcluir(ListaCategoria **lista, int id);

/* ── Acomodação ─────────────────────────────────────────── */
int             controllerAcomodacaoCadastrar(ListaAcomodacao **lista, TipoAcomodacao acom);
TipoAcomodacao *controllerAcomodacaoBuscar(ListaAcomodacao **lista, int id);
int             controllerAcomodacaoAtualizar(ListaAcomodacao **lista, int id, int op);
int             controllerAcomodacaoExcluir(ListaAcomodacao **lista, int id);

#endif // ACOMODACAO_CONTROLLER_H