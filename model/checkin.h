#ifndef CHECKIN_H
#define CHECKIN_H

#include "../common.h"
#include "reserva.h"
#include "caixa.h"

typedef struct {
    int   id;
    int   idReserva;
    int   idHospede;
    int   idAcomodacao;
    char  dataCheckin[12];
    char  dataCheckout[12];  // preenchida no checkout
    float totalDiarias;
    float totalProdutos;
    float totalGeral;
    int   diariasParas;      // 1 = pagas no checkin, 0 = no checkout
    int   encerrado;         // 1 apos checkout
    int   ativo;
} TipoCheckin;

typedef struct ListaCheckin {
    TipoCheckin       checkin;
    struct ListaCheckin *proximo;
} ListaCheckin;

void         CheckinInit(TipoCheckin *c);
int          CheckinCriar(ListaCheckin **lista, TipoCheckin c);
TipoCheckin *CheckinBuscar(ListaCheckin **lista, int id);
TipoCheckin *CheckinBuscarPorReserva(ListaCheckin **lista, int idReserva);
void         CheckinListar(ListaCheckin **lista, int id);
int          CheckinEncerrar(ListaCheckin **lista, int id, const char *dataCheckout);
void         CheckinListaLiberar(ListaCheckin *lista);

int CheckinSalvarTxt(ListaCheckin *lista);
int CheckinSalvarBin(ListaCheckin *lista);
int CheckinLerTxt(ListaCheckin **lista);
int CheckinLerBin(ListaCheckin **lista);

#endif // CHECKIN_H