#ifndef RESERVA_H
#define RESERVA_H

// Status possiveis da reserva
#define RESERVA_ATIVA      1
#define RESERVA_CANCELADA  2
#define RESERVA_CHECKIN    3  // hospede fez check-in
#define RESERVA_CHECKOUT   4  // hospede fez check-out (encerrada)

typedef struct {
    int  id;
    int  idHospede;
    int  idAcomodacao;
    char dataEntrada[13];   // DD/MM/AAAA
    char dataSaida[13];     // DD/MM/AAAA
    int  numAdultos;
    int  numCriancas;
    int  pagarNaEntrada;    // 1 = paga no check-in, 0 = paga no check-out
    int  status;            // RESERVA_*
    float totalDiarias;     // calculado na criacao/checkin
} TipoReserva;

typedef struct ListaReserva {
    struct ListaReserva *proximo;
    TipoReserva reserva;
} ListaReserva;

// Funcoes base
void ReservaInit(TipoReserva *reserva);
void ReservaListaInit(ListaReserva *lista);

int  ReservaCriar(ListaReserva **lista, TipoReserva reserva);
void ReservaListar(ListaReserva **lista, int id);
TipoReserva* ReservaBuscar(ListaReserva **lista, int id);
int  ReservaCancelar(ListaReserva **lista, int id);
void ReservaListaLiberar(ListaReserva *lista);

// Verificacoes de disponibilidade
// Retorna 1 se a acomodacao estiver livre no periodo, 0 se ocupada
int ReservaVerificarDisponibilidade(ListaReserva **lista, int idAcomodacao,
                                    const char *dataEntrada, const char *dataSaida);

// Calcula numero de diarias entre duas datas (DD/MM/AAAA)
int ReservaCalcularDiarias(const char *dataEntrada, const char *dataSaida);

// Funcoes de arquivo
int ReservaSalvarTxt(ListaReserva *lista);
int ReservaSalvarBin(ListaReserva *lista);
int ReservaLerTxt(ListaReserva **lista);
int ReservaLerBin(ListaReserva **lista);

#endif // RESERVA_H