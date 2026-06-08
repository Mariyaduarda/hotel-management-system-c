/* model/venda.c */
#include "venda.h"

void VendaInit(TipoVenda *v) {
    v->id             = 0;
    v->idHospede      = 0;
    v->numItens       = 0;
    v->total          = 0.0f;
    v->formaPagamento = 0;
    v->lancadaNoCaixa = 0;
    v->ativo          = 0;
    strcpy(v->data, "00/00/0000");
}

int VendaCriar(ListaVenda **lista, TipoVenda venda) {
    ListaVenda *novo = (ListaVenda *)malloc(sizeof(ListaVenda));
    if (!novo) return 0;
    novo->venda        = venda;
    novo->venda.ativo  = 1;
    novo->proximo      = NULL;

    if (*lista == NULL) {
        novo->venda.id = 1;
        *lista = novo;
    } else {
        ListaVenda *atual = *lista;
        while (atual->proximo) atual = atual->proximo;
        novo->venda.id = atual->venda.id + 1;
        atual->proximo = novo;
    }
    return 1;
}

TipoVenda *VendaBuscar(ListaVenda **lista, int id) {
    ListaVenda *atual = *lista;
    while (atual) {
        if (atual->venda.id == id) return &atual->venda;
        atual = atual->proximo;
    }
    return NULL;
}

void VendaListar(ListaVenda **lista, int id) {
    if (!lista || !*lista) { printf("Nenhuma venda registrada.\n"); return; }
    ListaVenda *atual = *lista;
    int achou = 0;
    while (atual) {
        TipoVenda *v = &atual->venda;
        if (!v->ativo) { atual = atual->proximo; continue; }
        if (id != 0 && v->id != id) { atual = atual->proximo; continue; }

        printf("Venda ID  : %d\n", v->id);
        printf("Hospede   : %d\n", v->idHospede);
        printf("Data      : %s\n", v->data);
        printf("Pagamento : %s\n", v->formaPagamento == VENDA_AVISTA ? "A vista" : "Anotar");
        printf("Itens:\n");
        for (int i = 0; i < v->numItens; i++) {
            printf("  Produto %d  x%d  R$ %.2f  = R$ %.2f\n",
                   v->itens[i].idProduto, v->itens[i].quantidade,
                   v->itens[i].precoUnitario, v->itens[i].subtotal);
        }
        printf("Total     : R$ %.2f\n\n", v->total);
        achou = 1;
        atual = atual->proximo;
    }
    if (!achou) printf("Venda nao encontrada.\n");
}

void VendaListaLiberar(ListaVenda *lista) {
    ListaVenda *temp;
    while (lista) { temp = lista; lista = lista->proximo; free(temp); }
}

int VendaSalvarBin(ListaVenda *lista) {
    FILE *f = fopen("dados/venda.bin", "wb");
    if (!f) return 0;
    ListaVenda *atual = lista;
    while (atual) { fwrite(&atual->venda, sizeof(TipoVenda), 1, f); atual = atual->proximo; }
    fclose(f);
    return 1;
}

int VendaLerBin(ListaVenda **lista) {
    FILE *f = fopen("dados/venda.bin", "rb");
    if (!f) return 0;
    TipoVenda v;
    while (fread(&v, sizeof(TipoVenda), 1, f)) VendaCriar(lista, v);
    fclose(f);
    return 1;
}

int VendaSalvarTxt(ListaVenda *lista) {
    FILE *f = fopen("dados/venda.txt", "w");
    if (!f) return 0;
    ListaVenda *atual = lista;
    while (atual) {
        TipoVenda *v = &atual->venda;
        fprintf(f, "%d;%d;%s;%d;%.2f;%d;%d;%d\n",
                v->id, v->idHospede, v->data, v->numItens,
                v->total, v->formaPagamento, v->lancadaNoCaixa, v->ativo);
        for (int i = 0; i < v->numItens; i++)
            fprintf(f, "ITEM;%d;%d;%.2f;%.2f\n",
                    v->itens[i].idProduto, v->itens[i].quantidade,
                    v->itens[i].precoUnitario, v->itens[i].subtotal);
        atual = atual->proximo;
    }
    fclose(f);
    return 1;
}

int VendaLerTxt(ListaVenda **lista) {
    FILE *f = fopen("dados/venda.txt", "r");
    if (!f) return 0;
    char linha[300];
    TipoVenda v;
    VendaInit(&v);
    while (fgets(linha, sizeof(linha), f)) {
        if (strncmp(linha, "ITEM", 4) == 0) {
            ItemVenda it = {0};
            sscanf(linha, "ITEM;%d;%d;%f;%f",
                   &it.idProduto, &it.quantidade,
                   &it.precoUnitario, &it.subtotal);
            if (v.numItens < MAX_ITENS_VENDA)
                v.itens[v.numItens++] = it;
        } else {
            if (v.id != 0) VendaCriar(lista, v);
            VendaInit(&v);
            sscanf(linha, "%d;%d;%[^;];%d;%f;%d;%d;%d",
                   &v.id, &v.idHospede, v.data, &v.numItens,
                   &v.total, &v.formaPagamento, &v.lancadaNoCaixa, &v.ativo);
            v.numItens = 0; // itens vem nas linhas seguintes
        }
    }
    if (v.id != 0) VendaCriar(lista, v);
    fclose(f);
    return 1;
}