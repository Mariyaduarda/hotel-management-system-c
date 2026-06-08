/* model/checkin.c */
#include "checkin.h"

void CheckinInit(TipoCheckin *c) {
    c->id            = 0;
    c->idReserva     = 0;
    c->idHospede     = 0;
    c->idAcomodacao  = 0;
    c->totalDiarias  = 0.0f;
    c->totalProdutos = 0.0f;
    c->totalGeral    = 0.0f;
    c->diariasParas  = 0;
    c->encerrado     = 0;
    c->ativo         = 0;
    strcpy(c->dataCheckin,  "00/00/0000");
    strcpy(c->dataCheckout, "");
}

int CheckinCriar(ListaCheckin **lista, TipoCheckin c) {
    ListaCheckin *novo = (ListaCheckin *)malloc(sizeof(ListaCheckin));
    if (!novo) return 0;
    novo->checkin       = c;
    novo->checkin.ativo = 1;
    novo->proximo       = NULL;

    if (*lista == NULL) {
        novo->checkin.id = 1;
        *lista = novo;
    } else {
        ListaCheckin *atual = *lista;
        while (atual->proximo) atual = atual->proximo;
        novo->checkin.id = atual->checkin.id + 1;
        atual->proximo = novo;
    }
    return 1;
}

TipoCheckin *CheckinBuscar(ListaCheckin **lista, int id) {
    ListaCheckin *atual = *lista;
    while (atual) {
        if (atual->checkin.id == id) return &atual->checkin;
        atual = atual->proximo;
    }
    return NULL;
}

TipoCheckin *CheckinBuscarPorReserva(ListaCheckin **lista, int idReserva) {
    ListaCheckin *atual = *lista;
    while (atual) {
        if (atual->checkin.idReserva == idReserva && !atual->checkin.encerrado)
            return &atual->checkin;
        atual = atual->proximo;
    }
    return NULL;
}

void CheckinListar(ListaCheckin **lista, int id) {
    if (!lista || !*lista) { printf("Nenhum check-in registrado.\n"); return; }
    ListaCheckin *atual = *lista;
    while (atual) {
        TipoCheckin *c = &atual->checkin;
        if (!c->ativo || (id != 0 && c->id != id)) { atual = atual->proximo; continue; }
        printf("Check-in ID  : %d\n",    c->id);
        printf("Reserva      : %d\n",    c->idReserva);
        printf("Hospede      : %d\n",    c->idHospede);
        printf("Acomodacao   : %d\n",    c->idAcomodacao);
        printf("Data entrada : %s\n",    c->dataCheckin);
        printf("Data saida   : %s\n",    strlen(c->dataCheckout) > 0 ? c->dataCheckout : "Em aberto");
        printf("Diarias      : R$ %.2f\n", c->totalDiarias);
        printf("Produtos     : R$ %.2f\n", c->totalProdutos);
        printf("Total Geral  : R$ %.2f\n", c->totalGeral);
        printf("Status       : %s\n\n",  c->encerrado ? "Check-out realizado" : "Hospedado");
        atual = atual->proximo;
    }
}

int CheckinEncerrar(ListaCheckin **lista, int id, const char *dataCheckout) {
    TipoCheckin *c = CheckinBuscar(lista, id);
    if (!c) { printf("Check-in nao encontrado.\n"); return 0; }
    if (c->encerrado) { printf("Check-out ja realizado.\n"); return 0; }
    c->encerrado = 1;
    strncpy(c->dataCheckout, dataCheckout, sizeof(c->dataCheckout) - 1);
    c->totalGeral = c->totalDiarias + c->totalProdutos;
    return 1;
}

void CheckinListaLiberar(ListaCheckin *lista) {
    ListaCheckin *temp;
    while (lista) { temp = lista; lista = lista->proximo; free(temp); }
}

int CheckinSalvarBin(ListaCheckin *lista) {
    FILE *f = fopen("dados/checkin.bin", "wb");
    if (!f) return 0;
    ListaCheckin *atual = lista;
    while (atual) { fwrite(&atual->checkin, sizeof(TipoCheckin), 1, f); atual = atual->proximo; }
    fclose(f);
    return 1;
}

int CheckinLerBin(ListaCheckin **lista) {
    FILE *f = fopen("dados/checkin.bin", "rb");
    if (!f) return 0;
    TipoCheckin c;
    while (fread(&c, sizeof(TipoCheckin), 1, f)) CheckinCriar(lista, c);
    fclose(f);
    return 1;
}

int CheckinSalvarTxt(ListaCheckin *lista) {
    FILE *f = fopen("dados/checkin.txt", "w");
    if (!f) return 0;
    ListaCheckin *atual = lista;
    while (atual) {
        TipoCheckin *c = &atual->checkin;
        fprintf(f, "%d;%d;%d;%d;%s;%s;%.2f;%.2f;%.2f;%d;%d;%d\n",
                c->id, c->idReserva, c->idHospede, c->idAcomodacao,
                c->dataCheckin, c->dataCheckout,
                c->totalDiarias, c->totalProdutos, c->totalGeral,
                c->diariasParas, c->encerrado, c->ativo);
        atual = atual->proximo;
    }
    fclose(f);
    return 1;
}

int CheckinLerTxt(ListaCheckin **lista) {
    FILE *f = fopen("dados/checkin.txt", "r");
    if (!f) return 0;
    char linha[300];
    while (fgets(linha, sizeof(linha), f)) {
        TipoCheckin c;
        sscanf(linha, "%d;%d;%d;%d;%[^;];%[^;];%f;%f;%f;%d;%d;%d",
               &c.id, &c.idReserva, &c.idHospede, &c.idAcomodacao,
               c.dataCheckin, c.dataCheckout,
               &c.totalDiarias, &c.totalProdutos, &c.totalGeral,
               &c.diariasParas, &c.encerrado, &c.ativo);
        CheckinCriar(lista, c);
    }
    fclose(f);
    return 1;
}