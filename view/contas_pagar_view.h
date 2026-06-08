#ifndef CONTAS_PAGAR_VIEW_H
#define CONTAS_PAGAR_VIEW_H

#include "../model/contas_pagar.h"

void ContaPagarMenuView(ListaContaPagar **lista);
void ContaPagarCadastrarView(ListaContaPagar **lista);
void ContaPagarListarView(ListaContaPagar **lista);
void ContaPagarBuscarView(ListaContaPagar **lista);
void ContaPagarBaixarView(ListaContaPagar **lista);
void ContaPagarSalvarView(ListaContaPagar **lista);
void ContaPagarCarregarView(ListaContaPagar **lista);

#endif // CONTAS_PAGAR_VIEW_H
