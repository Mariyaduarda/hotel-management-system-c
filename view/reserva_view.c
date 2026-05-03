#include "../common.h"
#include "reserva_view.h"
#include <string.h>
#include <stdio.h>

// ──────────────────────────────────────────────
// Helpers internos
// ──────────────────────────────────────────────

// Exibe todas as acomodacoes disponiveis no periodo informado
static void exibirDisponiveisPeriodo(ListaReserva    **listaReserva,
                                      ListaAcomodacao **listaAcomodacao,
                                      ListaCategoria  **listaCategoria,
                                      const char *entrada, const char *saida,
                                      int idCategoria,   // 0 = qualquer
                                      int adultos,       // 0 = qualquer
                                      int criancas,      // 0 = qualquer
                                      const char *facilidade) // "" = qualquer
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

        // Filtro categoria
        if (idCategoria != 0 && ac->idCategoria != idCategoria) {
            a = a->proximo; continue;
        }

        // Filtro capacidade
        TipoCategoria *cat = CategoriaBuscar(listaCategoria, ac->idCategoria);
        if (cat != NULL) {
            if (adultos  > 0 && cat->maxAdultos  < adultos)  { a = a->proximo; continue; }
            if (criancas > 0 && cat->maxCriancas < criancas) { a = a->proximo; continue; }
        }

        // Filtro facilidade
        if (facilidade != NULL && strlen(facilidade) > 0) {
            if (strstr(ac->facilidades, facilidade) == NULL) { a = a->proximo; continue; }
        }

        // Filtro disponibilidade no periodo
        if (!ReservaVerificarDisponibilidade(listaReserva, ac->id, entrada, saida)) {
            a = a->proximo; continue;
        }

        // Exibe linha
        char descCat[20] = "-";
        if (cat != NULL) snprintf(descCat, sizeof(descCat), "%s", cat->descricao);

        int maxAd = cat ? cat->maxAdultos  : 0;
        int maxCr = cat ? cat->maxCriancas : 0;

        printf("%-5d %-30s %-20s %-10s %-6d %-6d\n",
               ac->id, ac->descricao, ac->facilidades, descCat, maxAd, maxCr);
        achou = 1;
        a = a->proximo;
    }

    if (!achou) printf("  Nenhuma acomodacao disponivel com os criterios informados.\n");
}

// ──────────────────────────────────────────────
// Menu principal de reservas
// ──────────────────────────────────────────────

void ReservaMenuExibir() {
    printf("\n===== MODULO DE RESERVAS =====\n");
    printf("1. Nova reserva\n");
    printf("2. Cancelar reserva\n");
    printf("3. Consultar reserva por ID\n");
    printf("4. Buscar acomodacoes disponiveis\n");
    printf("0. Voltar\n");
    printf("Opcao: ");
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

    printf("\n--- NOVA RESERVA ---\n");

    // Hospede
    printf("ID do hospede: ");
    scanf("%d", &r.idHospede);
    limparBuffer();

    TipoHospede *h = HospedeBuscar(listaHospede, r.idHospede);
    if (h == NULL || !h->ativo) {
        printf("Hospede nao encontrado.\n");
        return;
    }
    printf("Hospede: %s\n", h->nome);

    // Periodo
    printf("Data de entrada (DD/MM/AAAA): ");
    lerString(r.dataEntrada, sizeof(r.dataEntrada));

    printf("Data de saida  (DD/MM/AAAA): ");
    lerString(r.dataSaida, sizeof(r.dataSaida));

    // Numero de pessoas
    printf("Numero de adultos : ");
    scanf("%d", &r.numAdultos);
    limparBuffer();

    printf("Numero de criancas: ");
    scanf("%d", &r.numCriancas);
    limparBuffer();

    // Filtros opcionais para ajudar na escolha
    printf("\n--- FILTROS (deixe 0 ou vazio para ignorar) ---\n");

    int idCategoria = 0;
    printf("ID da categoria desejada (0 = qualquer): ");
    scanf("%d", &idCategoria);
    limparBuffer();

    char facilidade[100] = "";
    printf("Facilidade desejada (ex: TV, Hidromassagem): ");
    lerString(facilidade, sizeof(facilidade));

    // Exibe disponiveis
    printf("\n--- ACOMODACOES DISPONIVEIS ---\n");
    exibirDisponiveisPeriodo(listaReserva, listaAcomodacao, listaCategoria,
                              r.dataEntrada, r.dataSaida,
                              idCategoria, r.numAdultos, r.numCriancas,
                              facilidade);

    // Escolha da acomodacao
    printf("\nID da acomodacao desejada (0 = cancelar): ");
    scanf("%d", &r.idAcomodacao);
    limparBuffer();
    if (r.idAcomodacao == 0) return;

    // Verifica capacidade
    TipoAcomodacao *ac = AcomodacaoBuscar(listaAcomodacao, r.idAcomodacao);
    if (ac == NULL || !ac->ativo) {
        printf("Acomodacao invalida.\n");
        return;
    }
    TipoCategoria *cat = CategoriaBuscar(listaCategoria, ac->idCategoria);
    if (cat != NULL) {
        if (r.numAdultos > cat->maxAdultos || r.numCriancas > cat->maxCriancas) {
            printf("Erro: acomodacao nao comporta o numero de pessoas informado.\n");
            printf("Capacidade: %d adultos e %d criancas.\n",
                   cat->maxAdultos, cat->maxCriancas);
            return;
        }
        // Calcula total de diarias
        int dias = ReservaCalcularDiarias(r.dataEntrada, r.dataSaida);
        r.totalDiarias = dias * cat->valorDiaria;
        printf("\nTotal de diarias: %d x R$ %.2f = R$ %.2f\n",
               dias, cat->valorDiaria, r.totalDiarias);
    }

    // Pagamento
    printf("Pagar diarias no check-in? (1=Sim / 0=Nao, paga no check-out): ");
    scanf("%d", &r.pagarNaEntrada);
    limparBuffer();

    // Confirma
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

// ──────────────────────────────────────────────
// Cancelar reserva
// ──────────────────────────────────────────────

void ReservaCancelarView(ListaReserva **lista) {
    printf("\n--- CANCELAR RESERVA ---\n");
    printf("ID da reserva: ");
    int id;
    scanf("%d", &id);
    limparBuffer();

    // Exibe antes de cancelar
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

// ──────────────────────────────────────────────
// Consultar reserva por ID
// ──────────────────────────────────────────────

void ReservaConsultarView(ListaReserva **lista) {
    printf("\n--- CONSULTAR RESERVA ---\n");
    printf("ID da reserva: ");
    int id;
    scanf("%d", &id);
    limparBuffer();
    ReservaListar(lista, id);
}

// ──────────────────────────────────────────────
// Buscar acomodacoes disponiveis (so consulta)
// ──────────────────────────────────────────────

void ReservaBuscarDisponiveisView(ListaReserva    **listaReserva,
                                   ListaAcomodacao **listaAcomodacao,
                                   ListaCategoria  **listaCategoria)
{
    printf("\n--- BUSCAR ACOMODACOES DISPONIVEIS ---\n");

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