/* model/contas_pagar.c */
#include "contas_pagar.h"

void ContaPagarInit(TipoContaPagar *c) {
    c->id            = 0;
    c->idFornecedor  = 0;
    c->idNotaFiscal  = 0;
    c->valor         = 0.0f;
    c->numeroParcela = 1;
    c->totalParcelas = 1;
    c->status        = CP_PENDENTE;
    c->ativo         = 0;
    strcpy(c->descricao,      "-");
    strcpy(c->dataVencimento, "00/00/0000");
    strcpy(c->dataPagamento,  "");
}

int ContaPagarCriar(ListaContaPagar **lista, TipoContaPagar conta) {
    ListaContaPagar *novo = (ListaContaPagar *)malloc(sizeof(ListaContaPagar));
    if (!novo) return 0;
    novo->conta       = conta;
    novo->conta.ativo = 1;
    novo->proximo     = NULL;

    if (*lista == NULL) {
        novo->conta.id = 1;
        *lista = novo;
    } else {
        ListaContaPagar *atual = *lista;
        while (atual->proximo) atual = atual->proximo;
        novo->conta.id = atual->conta.id + 1;
        atual->proximo = novo;
    }
    return 1;
}

TipoContaPagar *ContaPagarBuscar(ListaContaPagar **lista, int id) {
    ListaContaPagar *atual = *lista;
    while (atual) {
        if (atual->conta.id == id) return &atual->conta;
        atual = atual->proximo;
    }
    return NULL;
}

void ContaPagarListar(ListaContaPagar **lista, int idFornecedor,
                       const char *dataInicio, const char *dataFim) {
    if (!lista || !*lista) { printf("Nenhuma conta a pagar.\n"); return; }

    int di = (dataInicio && strlen(dataInicio) > 0) ? dataParaInt(dataInicio) : 0;
    int df = (dataFim    && strlen(dataFim)    > 0) ? dataParaInt(dataFim)    : 99999999;

    printf("%-4s %-10s %-30s %-10s %-12s %-12s %-10s\n",
           "ID", "Fornecedor", "Descricao", "Valor", "Vencimento", "Parcela", "Status");

    ListaContaPagar *atual = *lista;
    while (atual) {
        TipoContaPagar *c = &atual->conta;
        if (!c->ativo) { atual = atual->proximo; continue; }
        if (idFornecedor != 0 && c->idFornecedor != idFornecedor) { atual = atual->proximo; continue; }
        int dv = dataParaInt(c->dataVencimento);
        if (dv < di || dv > df) { atual = atual->proximo; continue; }

        char parcela[15];
        snprintf(parcela, sizeof(parcela), "%d/%d", c->numeroParcela, c->totalParcelas);
        printf("%-4d %-10d %-30s R$%-8.2f %-12s %-12s %-10s\n",
               c->id, c->idFornecedor, c->descricao, c->valor,
               c->dataVencimento, parcela,
               c->status == CP_PENDENTE ? "Pendente" : "Pago");
        atual = atual->proximo;
    }
}

int ContaPagarBaixar(ListaContaPagar **lista, int id, const char *dataPagamento) {
    TipoContaPagar *c = ContaPagarBuscar(lista, id);
    if (!c) { printf("Conta nao encontrada.\n"); return 0; }
    if (c->status == CP_PAGO) { printf("Conta ja foi paga.\n"); return 0; }
    c->status = CP_PAGO;
    strncpy(c->dataPagamento, dataPagamento, sizeof(c->dataPagamento) - 1);
    return 1;
}

void ContaPagarListaLiberar(ListaContaPagar *lista) {
    ListaContaPagar *temp;
    while (lista) { temp = lista; lista = lista->proximo; free(temp); }
}

int ContaPagarSalvarBin(ListaContaPagar *lista) {
    FILE *f = fopen("dados/contas_pagar.bin", "wb");
    if (!f) return 0;
    ListaContaPagar *atual = lista;
    while (atual) { fwrite(&atual->conta, sizeof(TipoContaPagar), 1, f); atual = atual->proximo; }
    fclose(f);
    return 1;
}

int ContaPagarLerBin(ListaContaPagar **lista) {
    FILE *f = fopen("dados/contas_pagar.bin", "rb");
    if (!f) return 0;
    TipoContaPagar c;
    while (fread(&c, sizeof(TipoContaPagar), 1, f)) ContaPagarCriar(lista, c);
    fclose(f);
    return 1;
}

int ContaPagarSalvarTxt(ListaContaPagar *lista) {
    FILE *f = fopen("dados/contas_pagar.txt", "w");
    if (!f) return 0;
    ListaContaPagar *atual = lista;
    while (atual) {
        TipoContaPagar *c = &atual->conta;
        fprintf(f, "%d;%d;%d;%s;%.2f;%s;%s;%d;%d;%d;%d\n",
                c->id, c->idFornecedor, c->idNotaFiscal, c->descricao,
                c->valor, c->dataVencimento, c->dataPagamento,
                c->numeroParcela, c->totalParcelas, c->status, c->ativo);
        atual = atual->proximo;
    }
    fclose(f);
    return 1;
}

int ContaPagarLerTxt(ListaContaPagar **lista) {
    FILE *f = fopen("dados/contas_pagar.txt", "r");
    if (!f) return 0;
    char linha[400];
    while (fgets(linha, sizeof(linha), f)) {
        TipoContaPagar c;
        sscanf(linha, "%d;%d;%d;%[^;];%f;%[^;];%[^;];%d;%d;%d;%d",
               &c.id, &c.idFornecedor, &c.idNotaFiscal, c.descricao,
               &c.valor, c.dataVencimento, c.dataPagamento,
               &c.numeroParcela, &c.totalParcelas, &c.status, &c.ativo);
        ContaPagarCriar(lista, c);
    }
    fclose(f);
    return 1;
}