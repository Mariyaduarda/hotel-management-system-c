/* controller/venda_controller.c */
#include "../common.h"
#include "../model/venda.h"
#include "../view/venda_view.h"
#include "venda_controller.h"

int controllerVendaCadastrar(ListaVenda **lista, TipoVenda venda) {
    return VendaCriar(lista, venda);
}

TipoVenda *controllerVendaBuscar(ListaVenda **lista, int id) {
    return VendaBuscar(lista, id);
}

void controllerVendaListar(ListaVenda **lista, int id) {
    VendaListar(lista, id);
}

int controllerVendaSalvar(ListaVenda *lista) {
    if (!VendaSalvarTxt(lista)) return 0;
    if (!VendaSalvarBin(lista)) return 0;
    return 1;
}

int controllerVendaCarregar(ListaVenda **lista) {
    if (VendaLerBin(lista)) return 1;
    return VendaLerTxt(lista);
}

void controllerVendaLiberar(ListaVenda *lista) {
    VendaListaLiberar(lista);
}

void VendaControllerExecutar(ListaVenda **lista) {
    VendaMenuView(lista);
}
