/* controller/contas_pagar_controller.c */
#include "../common.h"
#include "../model/contas_pagar.h"
#include "../view/contas_pagar_view.h"
#include "contas_pagar_controller.h"

int controllerContaPagarCadastrar(ListaContaPagar **lista, TipoContaPagar conta) {
    return ContaPagarCriar(lista, conta);
}

TipoContaPagar *controllerContaPagarBuscar(ListaContaPagar **lista, int id) {
    return ContaPagarBuscar(lista, id);
}

void controllerContaPagarListar(ListaContaPagar **lista, int idFornecedor,
                                const char *dataInicio, const char *dataFim) {
    ContaPagarListar(lista, idFornecedor, dataInicio, dataFim);
}

int controllerContaPagarBaixar(ListaContaPagar **lista, int id, const char *dataPagamento) {
    return ContaPagarBaixar(lista, id, dataPagamento);
}

int controllerContaPagarSalvar(ListaContaPagar *lista) {
    if (!ContaPagarSalvarTxt(lista)) return 0;
    if (!ContaPagarSalvarBin(lista)) return 0;
    return 1;
}

int controllerContaPagarCarregar(ListaContaPagar **lista) {
    if (ContaPagarLerBin(lista)) return 1;
    return ContaPagarLerTxt(lista);
}

void controllerContaPagarLiberar(ListaContaPagar *lista) {
    ContaPagarListaLiberar(lista);
}

void ContaPagarControllerExecutar(ListaContaPagar **lista) {
    ContaPagarMenuView(lista);
}
