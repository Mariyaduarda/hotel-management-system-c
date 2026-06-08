/* controller/nota_fiscal_controller.c */
#include "../common.h"
#include "../model/nota_fiscal.h"
#include "../view/nota_fiscal_view.h"
#include "nota_fiscal_controller.h"

int controllerNotaFiscalCadastrar(ListaNotaFiscal **lista, TipoNotaFiscal nota) {
    return NotaFiscalCriar(lista, nota);
}

TipoNotaFiscal *controllerNotaFiscalBuscar(ListaNotaFiscal **lista, int id) {
    return NotaFiscalBuscar(lista, id);
}

void controllerNotaFiscalListar(ListaNotaFiscal **lista, int id) {
    NotaFiscalListar(lista, id);
}

int controllerNotaFiscalSalvar(ListaNotaFiscal *lista) {
    if (!NotaFiscalSalvarTxt(lista)) return 0;
    if (!NotaFiscalSalvarBin(lista)) return 0;
    return 1;
}

int controllerNotaFiscalCarregar(ListaNotaFiscal **lista) {
    if (NotaFiscalLerBin(lista)) return 1;
    return NotaFiscalLerTxt(lista);
}

void controllerNotaFiscalLiberar(ListaNotaFiscal *lista) {
    NotaFiscalListaLiberar(lista);
}

void NotaFiscalControllerExecutar(ListaNotaFiscal **lista) {
    NotaFiscalMenuView(lista);
}
