// controller/acomodacao_controller.c
#include "../common.h"
#include "../model/acomodacao.h"
#include "acomodacao_controller.h"

/* ══════════════════════════════════════════════════════════
   CATEGORIA
   ══════════════════════════════════════════════════════════ */

int controllerCategoriaCadastrar(ListaCategoria **lista, TipoCategoria cat) {
    return CategoriaCriar(lista, cat);
}

TipoCategoria *controllerCategoriaBuscar(ListaCategoria **lista, int id) {
    return CategoriaBuscar(lista, id);
}

void controllerCategoriaListar(ListaCategoria **lista, int id) {
    CategoriaListar(lista, id);
}

/* op: 1=descricao 2=valorDiaria 3=maxAdultos 4=maxCriancas */
int controllerCategoriaAtualizar(ListaCategoria **lista, int id, int op) {
    return CategoriaAtualizar(lista, id, op);
}

int controllerCategoriaExcluir(ListaCategoria **lista, int id) {
    return CategoriaExcluir(lista, id);
}

int controllerCategoriaSalvar(ListaCategoria *lista) {
    if (!CategoriaSalvarTxt(lista)) return 0;
    if (!CategoriaSalvarBin(lista)) return 0;
    return 1;
}

int controllerCategoriaCarregar(ListaCategoria **lista) {
    if (CategoriaLerBin(lista)) return 1;
    return CategoriaLerTxt(lista);
}

void controllerCategoriaLiberar(ListaCategoria *lista) {
    CategoriaListaLiberar(lista);
}

/* ══════════════════════════════════════════════════════════
   ACOMODAÇÃO
   ══════════════════════════════════════════════════════════ */

int controllerAcomodacaoCadastrar(ListaAcomodacao **lista, TipoAcomodacao acom) {
    return AcomodacaoCriar(lista, acom);
}

TipoAcomodacao *controllerAcomodacaoBuscar(ListaAcomodacao **lista, int id) {
    return AcomodacaoBuscar(lista, id);
}

void controllerAcomodacaoListar(ListaAcomodacao **lista, int id,
                                 ListaCategoria **listaCat) {
    AcomodacaoListar(lista, id, listaCat);
}

/* op: 1=descricao 2=facilidades 3=idCategoria */
int controllerAcomodacaoAtualizar(ListaAcomodacao **lista, int id, int op) {
    return AcomodacaoAtualizar(lista, id, op);
}

int controllerAcomodacaoExcluir(ListaAcomodacao **lista, int id) {
    return AcomodacaoExcluir(lista, id);
}

int controllerAcomodacaoSalvar(ListaAcomodacao *lista) {
    if (!AcomodacaoSalvarTxt(lista)) return 0;
    if (!AcomodacaoSalvarBin(lista)) return 0;
    return 1;
}

int controllerAcomodacaoCarregar(ListaAcomodacao **lista) {
    if (AcomodacaoLerBin(lista)) return 1;
    return AcomodacaoLerTxt(lista);
}

void controllerAcomodacaoLiberar(ListaAcomodacao *lista) {
    AcomodacaoListaLiberar(lista);
}