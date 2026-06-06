#ifndef FORNECEDOR_CONTROLLER_H
#define FORNECEDOR_CONTROLLER_H

#include "../model/fornecedor.h"

int             controllerFornecedorCadastrar(ListaFornecedor **lista, TipoFornecedor f);
TipoFornecedor *controllerFornecedorBuscar(ListaFornecedor **lista, int id);
void            controllerFornecedorListar(ListaFornecedor **lista, int id);
int             controllerFornecedorAtualizar(ListaFornecedor **lista, int id, int op);
int             controllerFornecedorExcluir(ListaFornecedor **lista, int id);
int             controllerFornecedorSalvar(ListaFornecedor *lista);
int             controllerFornecedorCarregar(ListaFornecedor **lista);
void            controllerFornecedorLiberar(ListaFornecedor *lista);

#endif // FORNECEDOR_CONTROLLER_H