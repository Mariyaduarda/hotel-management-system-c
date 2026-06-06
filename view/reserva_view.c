
#include "../common.h"
#include "reserva_view.h"
#include <string.h>
#include <stdio.h>

#define TOPO  "╔══════════════════════════════════════════════════════════╗"
#define MEIO  "╠══════════════════════════════════════════════════════════╣"
#define FUNDO "╚══════════════════════════════════════════════════════════╝"
#define BORDA "║"

static void cabecalho(const char *titulo) {
    printf("%s\n", TOPO);
    printf("%s  %-54s%s\n", BORDA, titulo, BORDA);
    printf("%s\n", MEIO);
}

static void opcao(const char *num, const char *desc) {
    printf("%s  [%s] %-52s%s\n", BORDA, num, desc, BORDA);
}

static void rodape(void) {
    printf("%s\n", FUNDO);
    printf("  Opcao: ");
}

static void separador(void) {
    printf("%s\n", MEIO);
}

/* ── Helper: leitura de data com validacao ──────────────── */
static void lerData(char *dest, int tamanho, const char *label) {
    char buf[13];
    int valido = 0;

    do {
        printf("%s", label);
        fgets(buf, sizeof(buf), stdin);
        buf[strcspn(buf, "\n")] = '\0';

        if (strlen(buf) == 10 && buf[2] == '/' && buf[5] == '/')
            valido = 1;
        else if (strlen(buf) == 8) {
            int ok = 1;
            for (int i = 0; i < 8; i++)
                if (buf[i] < '0' || buf[i] > '9') { ok = 0; break; }
            if (ok) valido = 1;
        }

        if (!valido)
            printf("  Formato invalido. Use DD/MM/AAAA (ex: 20/05/2026)\n");

    } while (!valido);

    strncpy(dest, buf, tamanho - 1);
    dest[tamanho - 1] = '\0';
}

/* ── Exibe acomodacoes disponiveis no periodo ───────────── */
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

    printf("\n%-5s %-30s %-20s %-10s %-6s %-6s\n",
           "ID", "Descricao", "Facilidades", "Categoria", "Adult", "Crian");
    printf("%-5s %-30s %-20s %-10s %-6s %-6s\n",
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
            snprintf(descCat, sizeof(descCat), "%.19s", cat->descricao);
            maxAd = cat->maxAdultos;
            maxCr = cat->maxCriancas;
        }

        printf("%-5d %-30s %-20s %-10s %-6d %-6d\n",
               ac->id, ac->descricao, ac->facilidades, descCat, maxAd, maxCr);
        achou = 1;
        a = a->proximo;
    }

    if (!achou)
        printf("Nenhuma acomodacao disponivel com os criterios informados.\n");
}

/* ── Menu ───────────────────────────────────────────────── */
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

/* ── Nova reserva ───────────────────────────────────────── */
void ReservaCadastrarView(ListaReserva    **listaReserva,
                           ListaAcomodacao **listaAcomodacao,
                           ListaCategoria  **listaCategoria,
                           ListaHospede    **listaHospede)
{
    TipoReserva r;
    ReservaInit(&r);

    printf("\n");
    cabecalho("NOVA RESERVA");
    printf("%s\n", FUNDO);

    printf("ID do hospede: ");
    scanf("%d", &r.idHospede);
    limparBuffer();

    TipoHospede *h = HospedeBuscar(listaHospede, r.idHospede);
    if (h == NULL || !h->ativo) {
        printf("Hospede nao encontrado.\n");
        return;
    }
    printf("Hospede: %s\n", h->nome);

    lerData(r.dataEntrada, sizeof(r.dataEntrada), "Data de entrada (DD/MM/AAAA): ");
    lerData(r.dataSaida,   sizeof(r.dataSaida),   "Data de saida  (DD/MM/AAAA): ");

    printf("Numero de adultos : ");
    scanf("%d", &r.numAdultos);
    limparBuffer();
    printf("Numero de criancas: ");
    scanf("%d", &r.numCriancas);
    limparBuffer();

    printf("\n-- Filtros (0 ou vazio = ignorar) --\n");
    int idCategoria = 0;
    printf("ID da categoria desejada: ");
    scanf("%d", &idCategoria);
    limparBuffer();

    char facilidade[100] = "";
    printf("Facilidade desejada (ex: TV): ");
    lerString(facilidade, sizeof(facilidade));

    printf("\n-- Acomodacoes Disponiveis --\n");
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
        printf("Acomodacao invalida.\n");
        return;
    }

    TipoCategoria *cat = CategoriaBuscar(listaCategoria, ac->idCategoria);
    if (cat != NULL) {
        if (r.numAdultos > cat->maxAdultos || r.numCriancas > cat->maxCriancas) {
            printf("Acomodacao nao comporta o numero de pessoas.\n");
            printf("Capacidade: %d adultos e %d criancas.\n",
                   cat->maxAdultos, cat->maxCriancas);
            return;
        }
        int dias = ReservaCalcularDiarias(r.dataEntrada, r.dataSaida);
        r.totalDiarias = dias * cat->valorDiaria;
        printf("\nTotal: %d diarias x R$ %.2f = R$ %.2f\n",
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
        printf("Reserva criada com sucesso!\n");
    else
        printf("Erro ao criar reserva.\n");
}

/* ── Cancelar reserva ───────────────────────────────────── */
void ReservaCancelarView(ListaReserva **lista) {
    printf("\n");
    cabecalho("CANCELAR RESERVA");
    printf("%s\n", FUNDO);

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
        printf("Reserva cancelada com sucesso.\n");
}

/* ── Consultar por ID ───────────────────────────────────── */
void ReservaConsultarView(ListaReserva **lista) {
    printf("\n");
    cabecalho("CONSULTAR RESERVA");
    printf("%s\n", FUNDO);

    printf("ID da reserva: ");
    int id;
    scanf("%d", &id);
    limparBuffer();
    ReservaListar(lista, id);
}

/* ── Buscar disponiveis ─────────────────────────────────── */
void ReservaBuscarDisponiveisView(ListaReserva    **listaReserva,
                                   ListaAcomodacao **listaAcomodacao,
                                   ListaCategoria  **listaCategoria)
{
    printf("\n");
    cabecalho("ACOMODACOES DISPONIVEIS");
    printf("%s\n", FUNDO);

    char entrada[13], saida[13];
    lerData(entrada, sizeof(entrada), "Data de entrada (DD/MM/AAAA): ");
    lerData(saida,   sizeof(saida),   "Data de saida  (DD/MM/AAAA): ");

    int adultos = 0, criancas = 0, idCat = 0;
    printf("Adultos  (0 = qualquer): ");     scanf("%d", &adultos);  limparBuffer();
    printf("Criancas (0 = qualquer): ");     scanf("%d", &criancas); limparBuffer();
    printf("ID Categoria (0 = qualquer): "); scanf("%d", &idCat);    limparBuffer();

    char facilidade[100] = "";
    printf("Facilidade (vazio = qualquer): ");
    lerString(facilidade, sizeof(facilidade));

    exibirDisponiveisPeriodo(listaReserva, listaAcomodacao, listaCategoria,
                              entrada, saida, idCat, adultos, criancas, facilidade);
}

