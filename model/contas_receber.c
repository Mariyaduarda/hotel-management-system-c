/* model/contas_receber.c */
#include "contas_receber.h"

void ContaReceberInit(TipoContaReceber *c) {
    c->id       = 0;
    c->idHospede = 0;
    c->valor    = 0.0f;
    c->status   = CR_PENDENTE;
    c->ativo    = 0;
    strcpy(c->descricao,       "-");
    strcpy(c->dataVencimento,  "00/00/0000");
    strcpy(c->dataRecebimento, "");
}

int ContaReceberCriar(ListaContaReceber **lista, TipoContaReceber conta) {
    ListaContaReceber *novo = (ListaContaReceber *)malloc(sizeof(ListaContaReceber));
    if (!novo) return 0;
    novo->conta       = conta;
    novo->conta.ativo = 1;
    novo->proximo     = NULL;

    if (*lista == NULL) {
        novo->conta.id = 1;
        *lista = novo;
    } else {
        ListaContaReceber *atual = *lista;
        while (atual->proximo) atual = atual->proximo;
        novo->conta.id = atual->conta.id + 1;
        atual->proximo = novo;
    }
    return 1;
}

TipoContaReceber *ContaReceberBuscar(ListaContaReceber **lista, int id) {
    ListaContaReceber *atual = *lista;
    while (atual) {
        if (atual->conta.id == id) return &atual->conta;
        atual = atual->proximo;
    }
    return NULL;
}

void ContaReceberListar(ListaContaReceber **lista, int idHospede,
                         const char *dataInicio, const char *dataFim) {
    if (!lista || !*lista) { printf("Nenhuma conta a receber.\n"); return; }

    int di = (dataInicio && strlen(dataInicio) > 0) ? dataParaInt(dataInicio) : 0;
    int df = (dataFim    && strlen(dataFim)    > 0) ? dataParaInt(dataFim)    : 99999999;

    printf("%-4s %-8s %-30s %-10s %-12s %-10s\n",
           "ID", "Hospede", "Descricao", "Valor", "Vencimento", "Status");
    printf("%-4s %-8s %-30s %-10s %-12s %-10s\n",
           "---","-------","------------------------------","----------","------------","----------");

    ListaContaReceber *atual = *lista;
    while (atual) {
        TipoContaReceber *c = &atual->conta;
        if (!c->ativo) { atual = atual->proximo; continue; }
        if (idHospede != 0 && c->idHospede != idHospede) { atual = atual->proximo; continue; }
        int dv = dataParaInt(c->dataVencimento);
        if (dv < di || dv > df) { atual = atual->proximo; continue; }
        printf("%-4d %-8d %-30s R$%-8.2f %-12s %-10s\n",
               c->id, c->idHospede, c->descricao, c->valor,
               c->dataVencimento,
               c->status == CR_PENDENTE ? "Pendente" : "Recebido");
        atual = atual->proximo;
    }
}

int ContaReceberBaixar(ListaContaReceber **lista, int id, const char *dataRecebimento) {
    TipoContaReceber *c = ContaReceberBuscar(lista, id);
    if (!c) { printf("Conta nao encontrada.\n"); return 0; }
    if (c->status == CR_RECEBIDO) { printf("Conta ja foi baixada.\n"); return 0; }
    c->status = CR_RECEBIDO;
    strncpy(c->dataRecebimento, dataRecebimento, sizeof(c->dataRecebimento) - 1);
    return 1;
}

void ContaReceberListaLiberar(ListaContaReceber *lista) {
    ListaContaReceber *temp;
    while (lista) { temp = lista; lista = lista->proximo; free(temp); }
}

int ContaReceberSalvarBin(ListaContaReceber *lista) {
    FILE *f = fopen("dados/contas_receber.bin", "wb");
    if (!f) return 0;
    ListaContaReceber *atual = lista;
    while (atual) { fwrite(&atual->conta, sizeof(TipoContaReceber), 1, f); atual = atual->proximo; }
    fclose(f);
    return 1;
}

int ContaReceberLerBin(ListaContaReceber **lista) {
    FILE *f = fopen("dados/contas_receber.bin", "rb");
    if (!f) return 0;
    TipoContaReceber c;
    while (fread(&c, sizeof(TipoContaReceber), 1, f)) ContaReceberCriar(lista, c);
    fclose(f);
    return 1;
}

int ContaReceberSalvarTxt(ListaContaReceber *lista) {
    FILE *f = fopen("dados/contas_receber.txt", "w");
    if (!f) return 0;
    ListaContaReceber *atual = lista;
    while (atual) {
        TipoContaReceber *c = &atual->conta;
        fprintf(f, "%d;%d;%s;%.2f;%s;%s;%d;%d\n",
                c->id, c->idHospede, c->descricao, c->valor,
                c->dataVencimento, c->dataRecebimento, c->status, c->ativo);
        atual = atual->proximo;
    }
    fclose(f);
    return 1;
}

int ContaReceberLerTxt(ListaContaReceber **lista) {
    FILE *f = fopen("dados/contas_receber.txt", "r");
    if (!f) return 0;
    char linha[400];
    while (fgets(linha, sizeof(linha), f)) {
        TipoContaReceber c;
        sscanf(linha, "%d;%d;%[^;];%f;%[^;];%[^;];%d;%d",
               &c.id, &c.idHospede, c.descricao, &c.valor,
               c.dataVencimento, c.dataRecebimento, &c.status, &c.ativo);
        ContaReceberCriar(lista, c);
    }
    fclose(f);
    return 1;
}