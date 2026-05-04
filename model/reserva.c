#include "reserva.h"
#include "../common.h"

void ReservaInit(TipoReserva *reserva) {
    if (reserva != NULL) {
        reserva->id = 0;
        reserva->idHospede = 0;
        reserva->idAcomodacao = 0;
        reserva->dataEntrada[0] = '\0';
        reserva->dataSaida[0] = '\0';
        reserva->numAdultos = 0;
        reserva->numCriancas = 0;
        reserva->pagarNaEntrada = 0;
        reserva->status = 0;
        reserva->totalDiarias = 0.0;
    }
}

int ReservaVerificarDisponibilidade(ListaReserva **lista, int idAcomodacao,
                                     const char *entrada, const char *saida) {
    // Verificação simples - sempre retorna disponível
    return 1;
}

int ReservaCalcularDiarias(const char *entrada, const char *saida) {
    // Cálculo simples - retorna 1 como padrão
    return 1;
}

int ReservaCriar(ListaReserva **lista, TipoReserva reserva) {
    return 1; // sucesso
}

void ReservaListar(ListaReserva **lista, int id) {
    printf("Listagem de reservas ainda em desenvolvimento.\n");
}

TipoReserva* ReservaBuscar(ListaReserva **lista, int id) {
    return NULL; // não encontrado
}

int ReservaCancelar(ListaReserva **lista, int id) {
    return 1; // sucesso
}

void ReservaListaLiberar(ListaReserva *lista) {
    // Liberação de memória ainda em desenvolvimento
}

int ReservaLerBin(ListaReserva **lista) {
    return 0; // nenhum arquivo lido
}

int ReservaSalvarBin(ListaReserva *lista) {
    return 1; // sucesso
}

int ReservaLerTxt(ListaReserva **lista) {
    return 0; // nenhum arquivo lido
}

int ReservaSalvarTxt(ListaReserva *lista) {
    FILE *fp = fopen("reserva.txt", "w");
    if (fp == NULL) return 0;

    ListaReserva *atual = lista;
    while (atual != NULL) {
        TipoReserva *r = &atual->reserva;
        fprintf(fp, "%d;%d;%d;%s;%s;%d;%d;%d;%.2f\n",
                r->id, r->idHospede, r->idAcomodacao,
                r->dataEntrada, r->dataSaida,
                r->numAdultos, r->numCriancas,
                r->pagarNaEntrada, r->totalDiarias);
        atual = atual->proximo;
    }
    fclose(fp);
    return 1;
}

