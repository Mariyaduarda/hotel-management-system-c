#include "../common.h"
#include "../model/caixa.h"
#include "view.h"

/* Modulo Hospede*/
void ViewHospedeNaoEncontrado() {
    printf("Hospede nao encontrado.\n");
}

void ViewEntradaInvalida(){
    printf("Entrada invalida. Por favor, digite um numero inteiro: ");
}

/*  Modulo Caixa */
void ViewVazioCaixa() {
  printf("Nenhuma entrada no caixa.\n");
}

void ViewListaCaixa(){
    printf("ID | Data       | Tipo    | Valor     | Metodo Pagamento | Descricao\n");
    printf("--------------------------------------------------------------------------\n");
}

void ViewCaixaDetalhes(TipoCaixa caixa) {
    printf("%2d | %10s | %7s | R$ %8.2f | %16s | %s\n",
        caixa.id,
        caixa.data,
        (caixa.tipo == CAIXA_ENTRADA) ? "Entrada" : "Saída",
        caixa.valor,
        (caixa.metodoPagamento == PAGAMENTO_DINHEIRO) ? "Dinheiro" : "Cartão",
        caixa.descricao
    );
}

void ViewSaldoCaixa(double saldo) {
    printf("Saldo atual do caixa: R$ %.2f\n", saldo);
}