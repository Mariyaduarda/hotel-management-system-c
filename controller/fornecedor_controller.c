/* controller/fornecedor_controller.c */
#include "../common.h"
#include "fornecedor_controller.h"

int controllerFornecedorCadastrar(ListaFornecedor **lista, TipoFornecedor f) {
    return FornecedorCriar(lista, f);
}

TipoFornecedor *controllerFornecedorBuscar(ListaFornecedor **lista, int id) {
    return FornecedorBuscar(lista, id);
}

void controllerFornecedorListar(ListaFornecedor **lista, int id) {
    FornecedorListar(lista, id);
}

int controllerFornecedorAtualizar(ListaFornecedor **lista, int id, int op) {
    return FornecedorAtualizar(lista, id, op);
}

int controllerFornecedorExcluir(ListaFornecedor **lista, int id) {
    return FornecedorExcluir(lista, id);
}

int controllerFornecedorSalvar(ListaFornecedor *lista) {
    if (!FornecedorSalvarTxt(lista)) return 0;
    if (!FornecedorSalvarBin(lista)) return 0;
    return 1;
}

int controllerFornecedorCarregar(ListaFornecedor **lista) {
    if (FornecedorLerBin(lista)) return 1;
    return FornecedorLerTxt(lista);
}

void controllerFornecedorLiberar(ListaFornecedor *lista) {
    FornecedorListaLiberar(lista);
}