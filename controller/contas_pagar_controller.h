#ifndef CONTAS_PAGAR_CONTROLLER_H
#define CONTAS_PAGAR_CONTROLLER_H

#include "../model/contas_pagar.h"

int              controllerContaPagarCadastrar(ListaContaPagar **lista, TipoContaPagar conta);
TipoContaPagar  *controllerContaPagarBuscar(ListaContaPagar **lista, int id);
void             controllerContaPagarListar(ListaContaPagar **lista, int idFornecedor,
                                           const char *dataInicio, const char *dataFim);
int              controllerContaPagarBaixar(ListaContaPagar **lista, int id,
                                            const char *dataPagamento);
int              controllerContaPagarSalvar(ListaContaPagar *lista);
int              controllerContaPagarCarregar(ListaContaPagar **lista);
void             controllerContaPagarLiberar(ListaContaPagar *lista);
void             ContaPagarControllerExecutar(ListaContaPagar **lista);

#endif // CONTAS_PAGAR_CONTROLLER_H
