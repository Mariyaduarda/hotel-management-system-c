#ifndef NOTA_FISCAL_CONTROLLER_H
#define NOTA_FISCAL_CONTROLLER_H

#include "../model/nota_fiscal.h"

int             controllerNotaFiscalCadastrar(ListaNotaFiscal **lista, TipoNotaFiscal nota);
TipoNotaFiscal *controllerNotaFiscalBuscar(ListaNotaFiscal **lista, int id);
void            controllerNotaFiscalListar(ListaNotaFiscal **lista, int id);
int             controllerNotaFiscalSalvar(ListaNotaFiscal *lista);
int             controllerNotaFiscalCarregar(ListaNotaFiscal **lista);
void            controllerNotaFiscalLiberar(ListaNotaFiscal *lista);
void            NotaFiscalControllerExecutar(ListaNotaFiscal **lista);

#endif // NOTA_FISCAL_CONTROLLER_H
