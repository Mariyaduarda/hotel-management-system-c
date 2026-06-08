/* model/nota_fiscal.c */
#include "nota_fiscal.h"

void NotaFiscalInit(TipoNotaFiscal *n) {
    n->id            = 0;
    n->idFornecedor  = 0;
    n->frete         = 0.0f;
    n->imposto       = 0.0f;
    n->numItens      = 0;
    n->totalNota     = 0.0f;
    n->formaPagamento = 0;
    n->valorEntrada  = 0.0f;
    n->numParcelas   = 0;
    n->ativo         = 0;
    strcpy(n->data, "00/00/0000");
}

/* Calcula frete/imposto por produto e preco de venda
   margemLucro: ex: 10.0 = 10%                          */
void NotaFiscalCalcular(TipoNotaFiscal *n, float margemLucro) {
    // soma total de unidades
    int totalUnidades = 0;
    for (int i = 0; i < n->numItens; i++)
        totalUnidades += n->itens[i].quantidade;

    if (totalUnidades == 0) return;

    float fretePorUnidade   = n->frete   / totalUnidades;
    float impostoPorUnidade = n->imposto / totalUnidades;

    n->totalNota = 0.0f;
    for (int i = 0; i < n->numItens; i++) {
        ItemNotaFiscal *it = &n->itens[i];
        it->fretePorProduto   = fretePorUnidade;
        it->impostoPorProduto = impostoPorUnidade;

        float base  = it->precoCusto + fretePorUnidade + impostoPorUnidade;
        float lucro = base * (margemLucro / 100.0f);
        it->precoVenda = base + lucro;

        it->subtotal  = it->precoCusto * it->quantidade;
        n->totalNota += it->subtotal;
    }
    n->totalNota += n->frete + n->imposto;
}

int NotaFiscalCriar(ListaNotaFiscal **lista, TipoNotaFiscal nota) {
    ListaNotaFiscal *novo = (ListaNotaFiscal *)malloc(sizeof(ListaNotaFiscal));
    if (!novo) return 0;
    novo->nota       = nota;
    novo->nota.ativo = 1;
    novo->proximo    = NULL;

    if (*lista == NULL) {
        novo->nota.id = 1;
        *lista = novo;
    } else {
        ListaNotaFiscal *atual = *lista;
        while (atual->proximo) atual = atual->proximo;
        novo->nota.id = atual->nota.id + 1;
        atual->proximo = novo;
    }
    return 1;
}

TipoNotaFiscal *NotaFiscalBuscar(ListaNotaFiscal **lista, int id) {
    ListaNotaFiscal *atual = *lista;
    while (atual) {
        if (atual->nota.id == id) return &atual->nota;
        atual = atual->proximo;
    }
    return NULL;
}

void NotaFiscalListar(ListaNotaFiscal **lista, int id) {
    if (!lista || !*lista) { printf("Nenhuma nota fiscal registrada.\n"); return; }
    ListaNotaFiscal *atual = *lista;
    while (atual) {
        TipoNotaFiscal *n = &atual->nota;
        if (!n->ativo || (id != 0 && n->id != id)) { atual = atual->proximo; continue; }
        printf("NF ID       : %d\n",    n->id);
        printf("Fornecedor  : %d\n",    n->idFornecedor);
        printf("Data        : %s\n",    n->data);
        printf("Frete       : R$ %.2f\n", n->frete);
        printf("Imposto     : R$ %.2f\n", n->imposto);
        printf("Total Nota  : R$ %.2f\n", n->totalNota);
        printf("%-30s %-6s %-10s %-10s %-10s %-10s\n",
               "Descricao", "Qtd", "Custo", "Frete/un", "Imp/un", "Venda");
        for (int i = 0; i < n->numItens; i++) {
            ItemNotaFiscal *it = &n->itens[i];
            printf("%-30s %-6d R$%-8.2f R$%-8.2f R$%-8.2f R$%-8.2f\n",
                   it->descricao, it->quantidade, it->precoCusto,
                   it->fretePorProduto, it->impostoPorProduto, it->precoVenda);
        }
        printf("\n");
        atual = atual->proximo;
    }
}

void NotaFiscalListaLiberar(ListaNotaFiscal *lista) {
    ListaNotaFiscal *temp;
    while (lista) { temp = lista; lista = lista->proximo; free(temp); }
}

int NotaFiscalSalvarBin(ListaNotaFiscal *lista) {
    FILE *f = fopen("dados/nota_fiscal.bin", "wb");
    if (!f) return 0;
    ListaNotaFiscal *atual = lista;
    while (atual) { fwrite(&atual->nota, sizeof(TipoNotaFiscal), 1, f); atual = atual->proximo; }
    fclose(f);
    return 1;
}

int NotaFiscalLerBin(ListaNotaFiscal **lista) {
    FILE *f = fopen("dados/nota_fiscal.bin", "rb");
    if (!f) return 0;
    TipoNotaFiscal n;
    while (fread(&n, sizeof(TipoNotaFiscal), 1, f)) NotaFiscalCriar(lista, n);
    fclose(f);
    return 1;
}

int NotaFiscalSalvarTxt(ListaNotaFiscal *lista) {
    FILE *f = fopen("dados/nota_fiscal.txt", "w");
    if (!f) return 0;
    ListaNotaFiscal *atual = lista;
    while (atual) {
        TipoNotaFiscal *n = &atual->nota;
        fprintf(f, "%d;%d;%s;%.2f;%.2f;%.2f;%d;%.2f;%d;%d;%d\n",
                n->id, n->idFornecedor, n->data, n->frete, n->imposto,
                n->totalNota, n->formaPagamento, n->valorEntrada,
                n->numParcelas, n->numItens, n->ativo);
        for (int i = 0; i < n->numItens; i++) {
            ItemNotaFiscal *it = &n->itens[i];
            fprintf(f, "ITEM;%d;%s;%.2f;%d;%.2f;%.2f;%.2f;%.2f\n",
                    it->idProduto, it->descricao, it->precoCusto,
                    it->quantidade, it->subtotal,
                    it->fretePorProduto, it->impostoPorProduto, it->precoVenda);
        }
        atual = atual->proximo;
    }
    fclose(f);
    return 1;
}

int NotaFiscalLerTxt(ListaNotaFiscal **lista) {
    FILE *f = fopen("dados/nota_fiscal.txt", "r");
    if (!f) return 0;
    char linha[400];
    TipoNotaFiscal n;
    NotaFiscalInit(&n);
    while (fgets(linha, sizeof(linha), f)) {
        if (strncmp(linha, "ITEM", 4) == 0) {
            if (n.numItens < MAX_ITENS_NOTA) {
                ItemNotaFiscal *it = &n.itens[n.numItens++];
                sscanf(linha, "ITEM;%d;%[^;];%f;%d;%f;%f;%f;%f",
                       &it->idProduto, it->descricao, &it->precoCusto,
                       &it->quantidade, &it->subtotal,
                       &it->fretePorProduto, &it->impostoPorProduto, &it->precoVenda);
            }
        } else {
            if (n.id != 0) NotaFiscalCriar(lista, n);
            NotaFiscalInit(&n);
            int ni = 0;
            sscanf(linha, "%d;%d;%[^;];%f;%f;%f;%d;%f;%d;%d;%d",
                   &n.id, &n.idFornecedor, n.data, &n.frete, &n.imposto,
                   &n.totalNota, &n.formaPagamento, &n.valorEntrada,
                   &n.numParcelas, &ni, &n.ativo);
            n.numItens = 0;
        }
    }
    if (n.id != 0) NotaFiscalCriar(lista, n);
    fclose(f);
    return 1;
}