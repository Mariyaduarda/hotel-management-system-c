/* controller/contas_receber_controller.c */
#include "../common.h"
#include "../model/contas_receber.h"
#include "../view/contas_receber_view.h"
#include "contas_receber_controller.h"

int controllerContaReceberCadastrar(ListaContaReceber **lista, TipoContaReceber conta) {
    return ContaReceberCriar(lista, conta);
}

TipoContaReceber *controllerContaReceberBuscar(ListaContaReceber **lista, int id) {
    return ContaReceberBuscar(lista, id);
}

void controllerContaReceberListar(ListaContaReceber **lista, int idHospede,
                                  const char *dataInicio, const char *dataFim) {
    ContaReceberListar(lista, idHospede, dataInicio, dataFim);
}

int controllerContaReceberBaixar(ListaContaReceber **lista, int id, const char *dataRecebimento) {
    return ContaReceberBaixar(lista, id, dataRecebimento);
}

int controllerContaReceberSalvar(ListaContaReceber *lista) {
    if (!ContaReceberSalvarTxt(lista)) return 0;
    if (!ContaReceberSalvarBin(lista)) return 0;
    return 1;
}

int controllerContaReceberCarregar(ListaContaReceber **lista) {
    if (ContaReceberLerBin(lista)) return 1;
    return ContaReceberLerTxt(lista);
}

void controllerContaReceberLiberar(ListaContaReceber *lista) {
    ContaReceberListaLiberar(lista);
}

void ContaReceberControllerExecutar(ListaContaReceber **lista) {
    ContaReceberMenuView(lista);
}
