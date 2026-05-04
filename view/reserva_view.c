#include "../common.h"
#include "reserva_view.h"
#include <string.h>
#include <stdio.h>

/* ── Cores ANSI ─────────────────────────────────────────── */
#define RESET    "\033[0m"
#define NEGRITO  "\033[1m"
#define CIANO    "\033[1;36m"
#define AMARELO  "\033[1;33m"
#define VERDE    "\033[1;32m"
#define VERMELHO "\033[1;31m"
#define CINZA    "\033[0;90m"

#define TOPO  "╔══════════════════════════════════╗"
#define MEIO  "╠══════════════════════════════════╣"
#define FUNDO "╚══════════════════════════════════╝"
#define BORDA "║"

static void cabecalho(const char *titulo) {
    printf(CIANO "%s\n" RESET, TOPO);
    printf(CIANO "%s" RESET "  " NEGRITO "%-51s" RESET CIANO "%s\n" RESET,
           BORDA, titulo, BORDA);
    printf(CIANO "%s\n" RESET, MEIO);
}

static void opcao(const char *num, const char *desc) {
    printf(CIANO "%s" RESET "  " VERDE "[%s]" RESET " %-47s" CIANO "%s\n" RESET,
           BORDA, num, desc, BORDA);
}

static void rodape(void) {
    printf(CIANO "%s\n" RESET, FUNDO);
    printf(CINZA "  Opcao: " RESET);
}

static void separador(void) {
    printf(CIANO "%s\n" RESET, MEIO);
}

// ──────────────────────────────────────────────
// Helpers internos
// ──────────────────────────────────────────────

static void exibirDisponiveisPeriodo(ListaReserva    **listaReserva,
                                      ListaAcomodacao **listaAcomodacao,
                                      ListaCategoria  **listaCategoria,
                                      const char *entrada, const char *saida,
                                      int idCategoria,
                                      int adultos,
                                      int criancas,
                                      const char *facilidade)
{
    ListaAcomodacao *a = *listaAcomodacao;
    int achou = 0;

    printf(CIANO "\n%-5s %-30s %-20s %-10s %-6s %-6s\n" RESET,
           "ID", "Descricao", "Facilidades", "Categoria", "Adult", "Crian");
    printf(CINZA "%-5s %-30s %-20s %-10s %-6s %-6s\n" RESET,
           "---", "------------------------------",
           "--------------------", "----------", "------", "------");

    while (a != NULL) {
        TipoAcomodacao *ac = &a->acomodacao;
        if (!ac->ativo) { a = a->proximo; continue; }

        if (idCategoria != 0 && ac->idCategoria != idCategoria) {
            a = a->proximo; continue;
        }

        TipoCategoria *cat = CategoriaBuscar(listaCategoria, ac->idCategoria);
        if (cat != NULL) {
            if (adultos  > 0 && cat->maxAdultos  < adultos)  { a = a->proximo; continue; }
            if (criancas > 0 && cat->maxCriancas < criancas) { a = a->proximo; continue; }
        }

        if (facilidade != NULL && strlen(facilidade) > 0) {
            if (strstr(ac->facilidades, facilidade) == NULL) { a = a->proximo; continue; }
        }

        if (!ReservaVerificarDisponibilidade(listaReserva, ac->id, entrada, saida)) {
            a = a->proximo; continue;
        }

        char descCat[20] = "-";
        int maxAd = 0, maxCr = 0;
        if (cat != NULL) {
            snprintf(descCat, sizeof(descCat), "%s", cat->descricao);
            maxAd = cat->maxAdultos;
            maxCr = cat->maxCriancas;
        }

        printf("%-5d %-30s %-20s %-10s %-6d %-6d\n",
               ac->id, ac->descricao, ac->facilidades, descCat, maxAd, maxCr);
        achou = 1;
        a = a->proximo;
    }

    if (!achou)
        printf(AMARELO "Nenhuma acomodacao disponivel com os criterios informados.\n" RESET);
}

// ──────────────────────────────────────────────
// Menu principal de reservas
// ──────────────────────────────────────────────

void ReservaMenuExibir(void) {
    printf("\n");
    cabecalho("RESERVAS");
    opcao("1", "Nova reserva");
    opcao("2", "Cancelar reserva");
    opcao("3", "Consultar reserva por ID");
    opcao("4", "Buscar acomodacoes disponiveis");
    separador();
    opcao("0", "Voltar");
    rodape();
}

// ──────────────────────────────────────────────
// Nova reserva
// ──────────────────────────────────────────────

void ReservaCadastrarView(ListaReserva    **listaReserva,
                           ListaAcomodacao **listaAcomodacao,
                           ListaCategoria  **listaCategoria,
                           ListaHospede    **listaHospede)
{
    TipoReserva r;
    ReservaInit(&r);

    printf("\n");
    cabecalho("NOVA RESERVA");
    printf(CIANO BORDA RESET "\n" CIANO FUNDO "\n" RESET);

    printf("ID do hospede: ");
    scanf("%d", &r.idHospede);
    limparBuffer();

    TipoHospede *h = HospedeBuscar(listaHospede, r.idHospede);
    if (h == NULL || !h->ativo) {
        printf(VERMELHO "Hospede nao encontrado.\n" RESET);
        return;
    }
    printf(VERDE "Hospede: %s\n" RESET, h->nome);

    printf("Data de entrada (DD/MM/AAAA): ");
    lerString(r.dataEntrada, sizeof(r.dataEntrada));
    printf("Data de saida  (DD/MM/AAAA): ");
    lerString(r.dataSaida, sizeof(r.dataSaida));

    printf("Numero de adultos : ");
    scanf("%d", &r.numAdultos);
    limparBuffer();
    printf("Numero de criancas: ");
    scanf("%d", &r.numCriancas);
    limparBuffer();

    printf(CIANO "\n-- Filtros (0 ou vazio = ignorar) --\n" RESET);
    int idCategoria = 0;
    printf("ID da categoria desejada: ");
    scanf("%d", &idCategoria);
    limparBuffer();

    char facilidade[100] = "";
    printf("Facilidade desejada (ex: TV): ");
    lerString(facilidade, sizeof(facilidade));

    printf(CIANO "\n-- Acomodacoes Disponiveis --\n" RESET);
    exibirDisponiveisPeriodo(listaReserva, listaAcomodacao, listaCategoria,
                              r.dataEntrada, r.dataSaida,
                              idCategoria, r.numAdultos, r.numCriancas,
                              facilidade);

    printf("\nID da acomodacao (0 = cancelar): ");
    scanf("%d", &r.idAcomodacao);
    limparBuffer();
    if (r.idAcomodacao == 0) return;

    TipoAcomodacao *ac = AcomodacaoBuscar(listaAcomodacao, r.idAcomodacao);
    if (ac == NULL || !ac->ativo) {
        printf(VERMELHO "  ✘ Acomodacao invalida.\n" RESET);
        return;
    }

    TipoCategoria *cat = CategoriaBuscar(listaCategoria, ac->idCategoria);
    if (cat != NULL) {
        if (r.numAdultos > cat->maxAdultos || r.numCriancas > cat->maxCriancas) {
            printf(VERMELHO "  ✘ Acomodacao nao comporta o numero de pessoas.\n" RESET);
            printf("  Capacidade: %d adultos e %d criancas.\n",
                   cat->maxAdultos, cat->maxCriancas);
            return;
        }
        int dias = ReservaCalcularDiarias(r.dataEntrada, r.dataSaida);
        r.totalDiarias = dias * cat->valorDiaria;
        printf(VERDE "\n  Total: %d diarias x R$ %.2f = R$ %.2f\n" RESET,
               dias, cat->valorDiaria, r.totalDiarias);
    }

    printf("Pagar no check-in? (1=Sim / 0=Nao): ");
    scanf("%d", &r.pagarNaEntrada);
    limparBuffer();

    printf("\nConfirmar reserva? (1=Sim / 0=Nao): ");
    int confirm;
    scanf("%d", &confirm);
    limparBuffer();
    if (!confirm) return;

    if (ReservaCriar(listaReserva, r))
        printf(VERDE "Reserva criada com sucesso!\n" RESET);
    else
        printf(VERMELHO "Erro ao criar reserva.\n" RESET);
}

// ──────────────────────────────────────────────
// Cancelar reserva
// ──────────────────────────────────────────────

void ReservaCancelarView(ListaReserva **lista) {
    printf("\n");
    cabecalho("CANCELAR RESERVA");
    printf(CIANO BORDA RESET "\n" CIANO FUNDO "\n" RESET);

    printf("ID da reserva: ");
    int id;
    scanf("%d", &id);
    limparBuffer();

    ReservaListar(lista, id);

    TipoReserva *r = ReservaBuscar(lista, id);
    if (r == NULL) return;

    printf("\nConfirmar cancelamento? (1=Sim / 0=Nao): ");
    int confirm;
    scanf("%d", &confirm);
    limparBuffer();
    if (!confirm) return;

    if (ReservaCancelar(lista, id))
        printf(VERDE "Reserva cancelada com sucesso.\n" RESET);
}

// ──────────────────────────────────────────────
// Consultar reserva por ID
// ──────────────────────────────────────────────

void ReservaConsultarView(ListaReserva **lista) {
    printf("\n");
    cabecalho("CONSULTAR RESERVA");
    printf(CIANO BORDA RESET "\n" CIANO FUNDO "\n" RESET);

    printf("ID da reserva: ");
    int id;
    scanf("%d", &id);
    limparBuffer();
    ReservaListar(lista, id);
}

// ──────────────────────────────────────────────
// Buscar acomodacoes disponiveis
// ──────────────────────────────────────────────

void ReservaBuscarDisponiveisView(ListaReserva    **listaReserva,
                                   ListaAcomodacao **listaAcomodacao,
                                   ListaCategoria  **listaCategoria)
{
    printf("\n");
    cabecalho("ACOMODACOES DISPONIVEIS");
    printf(CIANO BORDA RESET "\n" CIANO FUNDO "\n" RESET);

    char entrada[11], saida[11];
    printf("Data de entrada (DD/MM/AAAA): ");
    lerString(entrada, sizeof(entrada));
    printf("Data de saida  (DD/MM/AAAA): ");
    lerString(saida, sizeof(saida));

    int adultos = 0, criancas = 0, idCat = 0;
    printf("Adultos  (0 = qualquer): "); scanf("%d", &adultos);  limparBuffer();
    printf("Criancas (0 = qualquer): "); scanf("%d", &criancas); limparBuffer();
    printf("ID Categoria (0 = qualquer): "); scanf("%d", &idCat); limparBuffer();

    char facilidade[100] = "";
    printf("Facilidade (vazio = qualquer): ");
    lerString(facilidade, sizeof(facilidade));

    exibirDisponiveisPeriodo(listaReserva, listaAcomodacao, listaCategoria,
                              entrada, saida, idCat, adultos, criancas, facilidade);
}