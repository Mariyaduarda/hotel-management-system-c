#ifndef CONTAS_RECEBER_CONTROLLER_H
#define CONTAS_RECEBER_CONTROLLER_H

#include "../model/contas_receber.h"

int               controllerContaReceberCadastrar(ListaContaReceber **lista, TipoContaReceber conta);
TipoContaReceber *controllerContaReceberBuscar(ListaContaReceber **lista, int id);
void              controllerContaReceberListar(ListaContaReceber **lista, int idHospede,
                                              const char *dataInicio, const char *dataFim);
int               controllerContaReceberBaixar(ListaContaReceber **lista, int id,
                                               const char *dataRecebimento);
int               controllerContaReceberSalvar(ListaContaReceber *lista);
int               controllerContaReceberCarregar(ListaContaReceber **lista);
void              controllerContaReceberLiberar(ListaContaReceber *lista);
void              ContaReceberControllerExecutar(ListaContaReceber **lista);

#endif // CONTAS_RECEBER_CONTROLLER_H
