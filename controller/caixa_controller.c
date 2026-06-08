#include "../common.h"
#include "caixa_controller.h"
#include "../view/view.h"

void CaixaControllerListar(ListaCaixa **lista, char *dataInicio, char *dataFim) {
    if (!lista || !*lista) {
        ViewVazioCaixa();
        return;
    }

    int di = (dataInicio && strlen(dataInicio) > 0) ? dataParaInt(dataInicio) : 0;
    int df = (dataFim && strlen(dataFim) > 0) ? dataParaInt(dataFim) : 99999999;

    int total = CaixaListar(lista, dataInicio, dataFim);
    if (total == 0) {
        ViewVazioCaixa();
        return;
    }

    ViewListaCaixa();
    ListaCaixa *atual = *lista;
    while (atual) {
        if (atual->caixa.ativo) {
            int d = dataParaInt(atual->caixa.data);
            if (d >= di && d <= df) {
                ViewCaixaDetalhes(atual->caixa);
            }
        }
        atual = atual->proximo;
    }

    ViewSaldoCaixa(CaixaSaldo(lista));
}
