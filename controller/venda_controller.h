#ifndef VENDA_CONTROLLER_H
#define VENDA_CONTROLLER_H

#include "../model/venda.h"

int         controllerVendaCadastrar(ListaVenda **lista, TipoVenda venda);
TipoVenda  *controllerVendaBuscar(ListaVenda **lista, int id);
void        controllerVendaListar(ListaVenda **lista, int id);
int         controllerVendaSalvar(ListaVenda *lista);
int         controllerVendaCarregar(ListaVenda **lista);
void        controllerVendaLiberar(ListaVenda *lista);
void        VendaControllerExecutar(ListaVenda **lista);

#endif // VENDA_CONTROLLER_H
