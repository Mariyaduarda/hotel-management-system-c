#include "reserva.h"
#include "../common.h"

/* ════════════════════════════════════════════════════════════════ */
/* Funções auxiliares de data                                       */
/* ════════════════════════════════════════════════════════════════ */

// Converte "DD/MM/AAAA" para inteiro AAAAMMDD — facil de comparar
static int dataParaInt(const char *data) {
    int d = 0, m = 0, a = 0;

    if (strlen(data) == 10 && data[2] == '/' && data[5] == '/') {
        // formato DD/MM/AAAA
        sscanf(data, "%d/%d/%d", &d, &m, &a);
    } else if (strlen(data) == 8) {
        // formato DDMMAAAA sem separador
        char buf[9];
        strncpy(buf, data, 8);
        buf[8] = '\0';
        d = (buf[0]-'0')*10 + (buf[1]-'0');
        m = (buf[2]-'0')*10 + (buf[3]-'0');
        a = (buf[4]-'0')*1000 + (buf[5]-'0')*100 + (buf[6]-'0')*10 + (buf[7]-'0');
    }
    return a * 10000 + m * 100 + d;
}

// Retorna diferenca em dias - aproximada, suficiente para comparar
static int diffDias(const char *entrada, const char *saida) {
    return dataParaInt(saida) - dataParaInt(entrada);
}

// Retorna 1 se os intervalos [e1,s1) e [e2,s2) se sobrepoem
static int datasSeOverpoem(const char *e1, const char *s1,
                            const char *e2, const char *s2) {
    int ie1 = dataParaInt(e1), is1 = dataParaInt(s1);
    int ie2 = dataParaInt(e2), is2 = dataParaInt(s2);
    // Sobreposicao: e1 < s2 && e2 < s1
    return (ie1 < is2) && (ie2 < is1);
}

/* ════════════════════════════════════════════════════════════════ */
/* Inicialização da Reserva                                         */
/* ════════════════════════════════════════════════════════════════ */

void ReservaInit(TipoReserva *reserva) {
    if (reserva == NULL) return;
    reserva->id             = 0;
    reserva->idHospede      = 0;
    reserva->idAcomodacao   = 0;
    reserva->dataEntrada[0] = '\0';
    reserva->dataSaida[0]   = '\0';
    reserva->numAdultos     = 0;
    reserva->numCriancas    = 0;
    reserva->pagarNaEntrada = 0;
    reserva->status         = 0;
    reserva->totalDiarias   = 0.0f;
}

void ReservaListaInit(ListaReserva *lista) {
    (void)lista; /* parâmetro não utilizado */
}

/* ════════════════════════════════════════════════════════════════ */
/* Verificação de disponibilidade e cálculo de diárias             */
/* ════════════════════════════════════════════════════════════════ */

int ReservaVerificarDisponibilidade(ListaReserva **lista, int idAcomodacao,
                                    const char *entrada, const char *saida) {
    if (!lista || !entrada || !saida) return 0;

    ListaReserva *atual = *lista;
    while (atual != NULL) {
        TipoReserva *r = &atual->reserva;
        if (r->idAcomodacao == idAcomodacao &&
            (r->status == RESERVA_ATIVA || r->status == RESERVA_CHECKIN)) {
            if (datasSeOverpoem(entrada, saida, r->dataEntrada, r->dataSaida))
                return 0; // ocupada
        }
        atual = atual->proximo;
    }
    return 1; // disponivel
}

int ReservaCalcularDiarias(const char *entrada, const char *saida) {
    int dias = diffDias(entrada, saida);
    return (dias > 0) ? dias : 0;
}

/* ════════════════════════════════════════════════════════════════ */
/* Geração de ID único                                             */
/* ════════════════════════════════════════════════════════════════ */

static int gerarId(ListaReserva **lista) {
    int maior = 0;
    ListaReserva *atual = *lista;
    while (atual != NULL) {
        if (atual->reserva.id > maior)
            maior = atual->reserva.id;
        atual = atual->proximo;
    }
    return maior + 1;
}

/* ════════════════════════════════════════════════════════════════ */
/* CRUD principal                                                   */
/* ════════════════════════════════════════════════════════════════ */

int ReservaCriar(ListaReserva **lista, TipoReserva reserva) {
    if (!lista) return 0;

    if (reserva.idHospede <= 0 || reserva.idAcomodacao <= 0) {
        printf("Erro: hospede ou acomodacao invalidos.\n");
        return 0;
    }
    if (reserva.dataEntrada[0] == '\0' || reserva.dataSaida[0] == '\0') {
        printf("Erro: datas invalidas.\n");
        return 0;
    }
    if (ReservaCalcularDiarias(reserva.dataEntrada, reserva.dataSaida) <= 0) {
        printf("Erro: data de saida deve ser apos a data de entrada.\n");
        return 0;
    }
    if (!ReservaVerificarDisponibilidade(lista, reserva.idAcomodacao,
                                         reserva.dataEntrada, reserva.dataSaida)) {
        printf("Erro: acomodacao indisponivel no periodo informado.\n");
        return 0;
    }

    ListaReserva *novo = (ListaReserva *)malloc(sizeof(ListaReserva));
    if (!novo) {
        printf("Erro: falha ao alocar memoria.\n");
        return 0;
    }

    reserva.id     = gerarId(lista);
    reserva.status = RESERVA_ATIVA;
    novo->reserva  = reserva;
    novo->proximo  = NULL;

    if (*lista == NULL) {
        *lista = novo;
    } else {
        ListaReserva *atual = *lista;
        while (atual->proximo != NULL)
            atual = atual->proximo;
        atual->proximo = novo;
    }
    return 1;
}

TipoReserva *ReservaBuscar(ListaReserva **lista, int id) {
    if (!lista) return NULL;
    ListaReserva *atual = *lista;
    while (atual != NULL) {
        if (atual->reserva.id == id)
            return &atual->reserva;
        atual = atual->proximo;
    }
    return NULL;
}

int ReservaCancelar(ListaReserva **lista, int id) {
    if (!lista) return 0;
    TipoReserva *r = ReservaBuscar(lista, id);
    if (!r) {
        printf("Erro: reserva %d nao encontrada.\n", id);
        return 0;
    }
    if (r->status == RESERVA_CANCELADA) {
        printf("Aviso: reserva %d ja esta cancelada.\n", id);
        return 0;
    }
    if (r->status == RESERVA_CHECKIN || r->status == RESERVA_CHECKOUT) {
        printf("Erro: nao e possivel cancelar reserva com check-in/out realizado.\n");
        return 0;
    }
    r->status = RESERVA_CANCELADA;
    printf("Reserva %d cancelada com sucesso.\n", id);
    return 1;
}

/* ════════════════════════════════════════════════════════════════ */
/* Listagem                                                         */
/* ════════════════════════════════════════════════════════════════ */

static const char *statusStr(int status) {
    switch (status) {
        case RESERVA_ATIVA:     return "Ativa";
        case RESERVA_CANCELADA: return "Cancelada";
        case RESERVA_CHECKIN:   return "Check-in";
        case RESERVA_CHECKOUT:  return "Check-out";
        default:                return "Desconhecido";
    }
}

void ReservaListar(ListaReserva **lista, int id) {
    if (!lista || *lista == NULL) {
        printf("Nenhuma reserva cadastrada.\n");
        return;
    }

    printf("%-5s %-8s %-10s %-12s %-12s %-7s %-8s %-10s %-12s\n",
           "ID", "Hospede", "Acomod.", "Entrada", "Saida",
           "Adults", "Criancas", "Pag.Entr.", "Status");
    printf("%-5s %-8s %-10s %-12s %-12s %-7s %-8s %-10s %-12s\n",
           "---", "-------", "-------", "----------", "----------",
           "------", "--------", "---------", "----------");

    ListaReserva *atual = *lista;
    int encontrou = 0;
    while (atual != NULL) {
        TipoReserva *r = &atual->reserva;
        if (id == 0 || r->id == id) {
            printf("%-5d %-8d %-10d %-12s %-12s %-7d %-8d %-10s %-12s\n",
                   r->id, r->idHospede, r->idAcomodacao,
                   r->dataEntrada, r->dataSaida,
                   r->numAdultos, r->numCriancas,
                   r->pagarNaEntrada ? "Sim" : "Nao",
                   statusStr(r->status));
            encontrou = 1;
        }
        atual = atual->proximo;
    }
    if (!encontrou)
        printf("Nenhuma reserva encontrada.\n");
}

/* ════════════════════════════════════════════════════════════════ */
/* Liberação de memória                                            */
/* ════════════════════════════════════════════════════════════════ */

void ReservaListaLiberar(ListaReserva *lista) {
    ListaReserva *atual = lista;
    while (atual != NULL) {
        ListaReserva *prox = atual->proximo;
        free(atual);
        atual = prox;
    }
}

/* ════════════════════════════════════════════════════════════════ */
/* Persistência — Arquivo Texto                                     */
/* ════════════════════════════════════════════════════════════════ */

int ReservaSalvarTxt(ListaReserva *lista) {
    FILE *fp = fopen("dados/reserva.txt", "w");
    if (!fp) { printf("Erro ao abrir reserva.txt.\n"); return 0; }

    ListaReserva *atual = lista;
    while (atual != NULL) {
        TipoReserva *r = &atual->reserva;
        fprintf(fp, "%d;%d;%d;%s;%s;%d;%d;%d;%d;%.2f\n",
                r->id, r->idHospede, r->idAcomodacao,
                r->dataEntrada, r->dataSaida,
                r->numAdultos, r->numCriancas,
                r->pagarNaEntrada, r->status, r->totalDiarias);
        atual = atual->proximo;
    }
    fclose(fp);
    return 1;
}

int ReservaLerTxt(ListaReserva **lista) {
    FILE *fp = fopen("dados/reserva.txt", "r");
    if (!fp) return 0;

    int lidas = 0;
    char linha[256];
    while (fgets(linha, sizeof(linha), fp)) {
        TipoReserva r;
        ReservaInit(&r);
        int campos = sscanf(linha,
            "%d;%d;%d;%12[^;];%12[^;];%d;%d;%d;%d;%f",
            &r.id, &r.idHospede, &r.idAcomodacao,
            r.dataEntrada, r.dataSaida,
            &r.numAdultos, &r.numCriancas,
            &r.pagarNaEntrada, &r.status, &r.totalDiarias);

        if (campos != 10) continue;

        ListaReserva *novo = (ListaReserva *)malloc(sizeof(ListaReserva));
        if (!novo) break;
        novo->reserva = r;
        novo->proximo = NULL;

        if (*lista == NULL) {
            *lista = novo;
        } else {
            ListaReserva *atual = *lista;
            while (atual->proximo) atual = atual->proximo;
            atual->proximo = novo;
        }
        lidas++;
    }
    fclose(fp);
    return lidas;
}

/* ════════════════════════════════════════════════════════════════ */
/* Persistência — Arquivo Binário                                   */
/* ════════════════════════════════════════════════════════════════ */

int ReservaSalvarBin(ListaReserva *lista) {
    FILE *fp = fopen("dados/reserva.bin", "wb");
    if (!fp) { printf("Erro ao abrir reserva.bin.\n"); return 0; }

    ListaReserva *atual = lista;
    while (atual != NULL) {
        fwrite(&atual->reserva, sizeof(TipoReserva), 1, fp);
        atual = atual->proximo;
    }
    fclose(fp);
    return 1;
}

int ReservaLerBin(ListaReserva **lista) {
    FILE *fp = fopen("dados/reserva.bin", "rb");
    if (!fp) return 0;

    int lidas = 0;
    TipoReserva r;
    while (fread(&r, sizeof(TipoReserva), 1, fp) == 1) {
        ListaReserva *novo = (ListaReserva *)malloc(sizeof(ListaReserva));
        if (!novo) break;
        novo->reserva = r;
        novo->proximo = NULL;

        if (*lista == NULL) {
            *lista = novo;
        } else {
            ListaReserva *atual = *lista;
            while (atual->proximo) atual = atual->proximo;
            atual->proximo = novo;
        }
        lidas++;
    }
    fclose(fp);
    return lidas;
}