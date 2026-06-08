#include "caixa.h"

void CaixaInit(TipoCaixa *caixa){
    caixa->id = 0;
    caixa->tipo = 0;
    caixa->valor = 0.0;
    caixa->metodoPagamento = 0;
    caixa->idReferencia = 0;
    caixa->ativo = 1;
    strcpy(caixa->data,      "00/00/0000");
    strcpy(caixa->descricao, "-");
}

int CaixaInserir(ListaCaixa **lista, TipoCaixa caixa){
    ListaCaixa *novo = (ListaCaixa *)malloc(sizeof(ListaCaixa));
    if (!novo) return 0;

    novo->caixa = caixa;
    novo->caixa.ativo = 1; // garante que nova entrada é ativa
    novo->proximo = NULL;

    if(*lista == NULL){
        novo->caixa.id = 1; // primeiro ID
        *lista = novo;
    } else{
        ListaCaixa *atual = *lista;
        while(atual->proximo) atual = atual->proximo;
        novo->caixa.id = atual->caixa.id+1; // ID sequencial
        atual->proximo = novo;
    }

    return 1;
}

TipoCaixa CaixaBuscar(ListaCaixa **lista, int id) {
    if (!lista || !*lista) return (TipoCaixa){0}; // retorna caixa vazio se lista for nula

    ListaCaixa *atual = *lista;
    while (atual != NULL) {
        if (atual->caixa.id == id)
            return atual->caixa; // caixa encontrado
        atual = atual->proximo;
    }
    return (TipoCaixa){0}; // caixa vazio se não encontrado
}

int CaixaListar(ListaCaixa **lista, char *dataInicio, char *dataFim) {
    if(!lista || !*lista) return 0;

    int di = (dataInicio && strlen(dataInicio) > 0) ? dataParaInt(dataInicio) : 0;
    int df = (dataFim && strlen(dataFim) > 0) ? dataParaInt(dataFim) : 99999999;

    ListaCaixa *atual = *lista;
    int count = 0;
    while(atual){
        TipoCaixa *c = &atual->caixa;
        if(c->ativo){
            int d = dataParaInt(c->data);
            if(d >= di && d <= df){
                count++;
            }
        }
        atual = atual->proximo;
    }
    return count;
}

double CaixaSaldo(ListaCaixa **lista) {
    double saldo = 0.0;
    ListaCaixa *atual = *lista;
    while(atual) {
        if(atual->caixa.ativo) {
            if(atual->caixa.tipo == CAIXA_ENTRADA)  saldo += atual->caixa.valor;
            else  saldo -= atual->caixa.valor;
        }
        atual = atual->proximo;
    }
    return saldo;
}

void CaixaListaLiberar(ListaCaixa *lista) {
    while(lista) {
        ListaCaixa *temp = lista;
        lista = lista->proximo;
        free(temp);
    }
}

int CaixaSalvarTxt(ListaCaixa *lista) {
    FILE *f = fopen("dados/caixa.txt", "w");
    if (!f) return 0;
    ListaCaixa *atual = lista;
    while (atual) {
        TipoCaixa *l = &atual->caixa;
        fprintf(f, "%d;%s;%s;%.2f;%d;%d;%d;%d\n",
                l->id, l->data, l->descricao, l->valor,
                l->tipo, l->metodoPagamento, l->idReferencia, l->ativo);
        atual = atual->proximo;
    }
    fclose(f);
    return 1;
}
 
int CaixaSalvarBin(ListaCaixa *lista) {
    FILE *f = fopen("dados/caixa.bin", "wb");
    if (!f) return 0;
    ListaCaixa *atual = lista;
    while (atual) {
        fwrite(&atual->caixa, sizeof(TipoCaixa), 1, f);
        atual = atual->proximo;
    }
    fclose(f);
    return 1;
}
 
int CaixaLerTxt(ListaCaixa **lista) {
    FILE *f = fopen("dados/caixa.txt", "r");
    if (!f) return 0;
    char linha[300];
    while (fgets(linha, sizeof(linha), f)) {
        TipoCaixa l;
        sscanf(linha,
            "%d;%10[^;];%99[^;];%lf;%d;%d;%d;%d",
            &l.id,
            l.data,
            l.descricao,
            &l.valor,
            &l.tipo,
            &l.metodoPagamento,
            &l.idReferencia,
            &l.ativo);
            
        CaixaInserir(lista, l);
    }
    fclose(f);
    return 1;
}
 
int CaixaLerBin(ListaCaixa **lista) {
    FILE *f = fopen("dados/caixa.bin", "rb");
    if (!f) return 0;
    TipoCaixa c;
    while (fread(&c, sizeof(TipoCaixa), 1, f))
        CaixaInserir(lista, c);
    fclose(f);
    return 1;
}