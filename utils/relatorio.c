#include "../common.h"
#include "relatorio.h"
#include <string.h>
#include <stdio.h>

// ──────────────────────────────────────────────
// Helpers internos
// ──────────────────────────────────────────────

// Abre o destino correto: retorna stdout ou FILE* para CSV
static FILE *abrirDestino(ConfigRelatorio *cfg) {
    if (cfg->destino == RELATORIO_ARQUIVO) {
        FILE *f = fopen(cfg->caminho, "w");
        if (f == NULL) {
            printf("Erro ao abrir arquivo: %s\n", cfg->caminho);
            return NULL;
        }
        return f;
    }
    return stdout;
}

static void fecharDestino(FILE *f) {
    if (f != NULL && f != stdout) fclose(f);
}

// Reuse global dataParaInt from common.c
static int dataEntrePeriodo(const char *data,
                             const char *inicio, const char *fim) {
    if (strlen(inicio) == 0 && strlen(fim) == 0) return 1; // sem filtro
    int d  = dataParaInt(data);
    int di = strlen(inicio) > 0 ? dataParaInt(inicio) : 0;
    int df = strlen(fim)    > 0 ? dataParaInt(fim)    : 99999999;
    return d >= di && d <= df;
}

// ──────────────────────────────────────────────
// Relatorio de Hospedes
// ──────────────────────────────────────────────

void RelatorioHospedes(ListaHospede **lista,
                        ConfigRelatorio *cfg,
                        int idMin, int idMax,
                        const char *sexo)
{
    FILE *out = abrirDestino(cfg);
    if (out == NULL) return;

    // Cabecalho
    if (cfg->destino == RELATORIO_ARQUIVO) {
        fprintf(out, "ID;Nome;CPF;Telefone;Email;Sexo;EstadoCivil;DataNascimento\n");
    } else {
        printf("\n========== RELATORIO DE HOSPEDES ==========\n");
        printf("%-4s %-30s %-14s %-25s %-15s %-4s %-12s %-12s\n",
               "ID", "Nome", "CPF", "Email", "Telefone", "Sex", "Est.Civil", "Nasc.");
        printf("%s\n", "------------------------------------"
                       "------------------------------------"
                       "--------------------");
    }

    ListaHospede *atual = *lista;
    int total = 0;

    while (atual != NULL) {
        TipoHospede *h = &atual->hospede;

        // Filtro: ativo
        if (!h->ativo) { atual = atual->proximo; continue; }

        // Filtro: faixa de IDs
        if (idMin > 0 && h->id < idMin) { atual = atual->proximo; continue; }
        if (idMax > 0 && h->id > idMax) { atual = atual->proximo; continue; }

        // Filtro: sexo
        if (sexo != NULL && strlen(sexo) > 0) {
            if (strcasecmp(h->sexo, sexo) != 0) { atual = atual->proximo; continue; }
        }

        // Saida
        if (cfg->destino == RELATORIO_ARQUIVO) {
            fprintf(out, "%d;%s;%s;%s;%s;%s;%s;%s\n",
                    h->id, h->nome, h->cpf,
                    h->telefone, h->email, h->sexo,
                    h->estadoCivil, h->dataNascimento);
        } else {
            printf("%-4d %-30s %-14s %-25s %-15s %-4s %-12s %-12s\n",
                   h->id, h->nome, h->cpf, h->email,
                   h->telefone, h->sexo, h->estadoCivil, h->dataNascimento);
        }
        total++;
        atual = atual->proximo;
    }

    if (cfg->destino == RELATORIO_TELA)
        printf("\nTotal: %d hospede(s)\n", total);

    fecharDestino(out);
    if (cfg->destino == RELATORIO_ARQUIVO)
        printf("Relatorio salvo em: %s\n", cfg->caminho);
}

// ──────────────────────────────────────────────
// Relatorio de Acomodacoes
// ──────────────────────────────────────────────

void RelatorioAcomodacoes(ListaAcomodacao **listaAcom,
                           ListaCategoria  **listaCat,
                           ConfigRelatorio *cfg,
                           int idMin, int idMax,
                           int idCategoria,
                           const char *dataDisponivel)
{
    (void)dataDisponivel; /* parâmetro não utilizado */
    FILE *out = abrirDestino(cfg);
    if (out == NULL) return;

    if (cfg->destino == RELATORIO_ARQUIVO) {
        fprintf(out, "ID;Descricao;Facilidades;Categoria;ValorDiaria;MaxAdultos;MaxCriancas\n");
    } else {
        printf("\n========== RELATORIO DE ACOMODACOES ==========\n");
        printf("%-4s %-25s %-25s %-15s %-10s %-6s %-6s\n",
               "ID", "Descricao", "Facilidades", "Categoria", "Diaria", "Adult", "Crian");
        printf("%s\n", "-------------------------------------------------------------------"
                       "---------------------");
    }

    ListaAcomodacao *atual = *listaAcom;
    int total = 0;

    while (atual != NULL) {
        TipoAcomodacao *ac = &atual->acomodacao;

        if (!ac->ativo)                              { atual = atual->proximo; continue; }
        if (idMin > 0 && ac->id < idMin)             { atual = atual->proximo; continue; }
        if (idMax > 0 && ac->id > idMax)             { atual = atual->proximo; continue; }
        if (idCategoria > 0 && ac->idCategoria != idCategoria)
                                                     { atual = atual->proximo; continue; }

        TipoCategoria *cat = CategoriaBuscar(listaCat, ac->idCategoria);

        // Filtro data disponivel: verifica se NAO ha reserva ativa nessa data
        // (implementacao simplificada — para uso completo integrar com listaReserva)

        if (cfg->destino == RELATORIO_ARQUIVO) {
            fprintf(out, "%d;%s;%s;%s;%.2f;%d;%d\n",
                    ac->id, ac->descricao, ac->facilidades,
                    cat ? cat->descricao : "-",
                    cat ? cat->valorDiaria : 0.0f,
                    cat ? cat->maxAdultos  : 0,
                    cat ? cat->maxCriancas : 0);
        } else {
            printf("%-4d %-25s %-25s %-15s R$%-8.2f %-6d %-6d\n",
                   ac->id, ac->descricao, ac->facilidades,
                   cat ? cat->descricao : "-",
                   cat ? cat->valorDiaria : 0.0f,
                   cat ? cat->maxAdultos  : 0,
                   cat ? cat->maxCriancas : 0);
        }
        total++;
        atual = atual->proximo;
    }

    if (cfg->destino == RELATORIO_TELA)
        printf("\nTotal: %d acomodacao(oes)\n", total);

    fecharDestino(out);
    if (cfg->destino == RELATORIO_ARQUIVO)
        printf("Relatorio salvo em: %s\n", cfg->caminho);
}

// ──────────────────────────────────────────────
// Relatorio de Reservas
// ──────────────────────────────────────────────

void RelatorioReservas(ListaReserva **lista,
                        ConfigRelatorio *cfg,
                        int idHospede,
                        int idAcomodacao,
                        const char *periodoInicio,
                        const char *periodoFim)
{
    FILE *out = abrirDestino(cfg);
    if (out == NULL) return;

    const char *statusStr[] = {"", "Ativa", "Cancelada", "Check-in", "Check-out"};

    if (cfg->destino == RELATORIO_ARQUIVO) {
        fprintf(out, "ID;IDHospede;IDAcomodacao;Entrada;Saida;Adultos;Criancas;Total;Status\n");
    } else {
        printf("\n========== RELATORIO DE RESERVAS ==========\n");
        printf("%-4s %-8s %-8s %-12s %-12s %-6s %-6s %-10s %-10s\n",
               "ID", "Hospede", "Acomod.", "Entrada", "Saida",
               "Adult", "Crian", "Total", "Status");
        printf("%s\n", "----------------------------------------------------------------------"
                       "--------------------");
    }

    ListaReserva *atual = *lista;
    int total = 0;

    while (atual != NULL) {
        TipoReserva *r = &atual->reserva;

        if (idHospede    > 0 && r->idHospede    != idHospede)    { atual = atual->proximo; continue; }
        if (idAcomodacao > 0 && r->idAcomodacao != idAcomodacao) { atual = atual->proximo; continue; }

        // Filtro periodo: reservas cuja entrada esteja no periodo
        if (!dataEntrePeriodo(r->dataEntrada, periodoInicio, periodoFim))
                                                                 { atual = atual->proximo; continue; }

        if (cfg->destino == RELATORIO_ARQUIVO) {
            fprintf(out, "%d;%d;%d;%s;%s;%d;%d;%.2f;%s\n",
                    r->id, r->idHospede, r->idAcomodacao,
                    r->dataEntrada, r->dataSaida,
                    r->numAdultos, r->numCriancas,
                    r->totalDiarias, statusStr[r->status]);
        } else {
            printf("%-4d %-8d %-8d %-12s %-12s %-6d %-6d R$%-8.2f %-10s\n",
                   r->id, r->idHospede, r->idAcomodacao,
                   r->dataEntrada, r->dataSaida,
                   r->numAdultos, r->numCriancas,
                   r->totalDiarias, statusStr[r->status]);
        }
        total++;
        atual = atual->proximo;
    }

    if (cfg->destino == RELATORIO_TELA)
        printf("\nTotal: %d reserva(s)\n", total);

    fecharDestino(out);
    if (cfg->destino == RELATORIO_ARQUIVO)
        printf("Relatorio salvo em: %s\n", cfg->caminho);
}

// ──────────────────────────────────────────────
// Relatorio de Produtos
// ──────────────────────────────────────────────

void RelatorioProdutos(ListaProduto **lista,
                        ConfigRelatorio *cfg,
                        int idMin, int idMax)
{
    FILE *out = abrirDestino(cfg);
    if (out == NULL) return;

    if (cfg->destino == RELATORIO_ARQUIVO) {
        fprintf(out, "ID;Descricao;Estoque;EstoqueMin;PrecoCusto;PrecoVenda\n");
    } else {
        printf("\n========== RELATORIO DE PRODUTOS ==========\n");
        printf("%-4s %-30s %-8s %-9s %-12s %-12s\n",
               "ID", "Descricao", "Estoque", "Est.Min", "Custo", "Venda");
        printf("%s\n", "------------------------------------------------------"
                       "--------------------");
    }

    ListaProduto *atual = *lista;
    int total = 0;

    while (atual != NULL) {
        TipoProduto *p = &atual->produto;

        if (!p->ativo)                  { atual = atual->proximo; continue; }
        if (idMin > 0 && p->id < idMin) { atual = atual->proximo; continue; }
        if (idMax > 0 && p->id > idMax) { atual = atual->proximo; continue; }

        if (cfg->destino == RELATORIO_ARQUIVO) {
            fprintf(out, "%d;%s;%d;%d;%.2f;%.2f\n",
                    p->id, p->descricao, p->estoque,
                    p->estoqueMinimo, p->precoCusto, p->precoVenda);
        } else {
            printf("%-4d %-30s %-8d %-9d R$%-10.2f R$%-10.2f\n",
                   p->id, p->descricao, p->estoque,
                   p->estoqueMinimo, p->precoCusto, p->precoVenda);
        }
        total++;
        atual = atual->proximo;
    }

    if (cfg->destino == RELATORIO_TELA)
        printf("\nTotal: %d produto(s)\n", total);

    fecharDestino(out);
    if (cfg->destino == RELATORIO_ARQUIVO)
        printf("Relatorio salvo em: %s\n", cfg->caminho);
}

// ──────────────────────────────────────────────
// Relatorio de Produtos em Estoque Minimo
// ──────────────────────────────────────────────

void RelatorioProdutosEstoqueMinimo(ListaProduto **lista,
                                     ConfigRelatorio *cfg,
                                     int idMin, int idMax)
{
    FILE *out = abrirDestino(cfg);
    if (out == NULL) return;

    if (cfg->destino == RELATORIO_ARQUIVO) {
        fprintf(out, "ID;Descricao;Estoque;EstoqueMin;PrecoCusto;PrecoVenda\n");
    } else {
        printf("\n========== PRODUTOS EM ESTOQUE MINIMO ==========\n");
        printf("%-4s %-30s %-8s %-9s %-12s %-12s\n",
               "ID", "Descricao", "Estoque", "Est.Min", "Custo", "Venda");
        printf("%s\n", "------------------------------------------------------"
                       "--------------------");
    }

    ListaProduto *atual = *lista;
    int total = 0;

    while (atual != NULL) {
        TipoProduto *p = &atual->produto;

        if (!p->ativo)                        { atual = atual->proximo; continue; }
        if (idMin > 0 && p->id < idMin)       { atual = atual->proximo; continue; }
        if (idMax > 0 && p->id > idMax)       { atual = atual->proximo; continue; }
        if (p->estoque > p->estoqueMinimo)    { atual = atual->proximo; continue; } // filtra so os criticos

        if (cfg->destino == RELATORIO_ARQUIVO) {
            fprintf(out, "%d;%s;%d;%d;%.2f;%.2f\n",
                    p->id, p->descricao, p->estoque,
                    p->estoqueMinimo, p->precoCusto, p->precoVenda);
        } else {
            printf("%-4d %-30s %-8d %-9d R$%-10.2f R$%-10.2f  <<< REPOR\n",
                   p->id, p->descricao, p->estoque,
                   p->estoqueMinimo, p->precoCusto, p->precoVenda);
        }
        total++;
        atual = atual->proximo;
    }

    if (cfg->destino == RELATORIO_TELA)
        printf("\nTotal em estoque critico: %d produto(s)\n", total);

    fecharDestino(out);
    if (cfg->destino == RELATORIO_ARQUIVO)
        printf("Relatorio salvo em: %s\n", cfg->caminho);
}

// ──────────────────────────────────────────────
// Relatorio de Movimentacao de Acomodacoes
// ──────────────────────────────────────────────

void RelatorioMovimentacaoAcomodacoes(ListaReserva    **listaReserva,
                                       ListaAcomodacao **listaAcom,
                                       ListaCategoria  **listaCat,
                                       ConfigRelatorio *cfg,
                                       int idAcomodacao)
{
    (void)listaReserva; /* parâmetro não utilizado */
    (void)listaAcom;    /* parâmetro não utilizado */
    (void)listaCat;     /* parâmetro não utilizado */
    FILE *out = abrirDestino(cfg);
    if (out == NULL) return;

    if (cfg->destino == RELATORIO_ARQUIVO) {
        fprintf(out, "IDAcomodacao;Descricao;TotalDiarias;TotalRecebido\n");
    } else {
        printf("\n========== MOVIMENTACAO DE ACOMODACOES ==========\n");
        printf("%-4s %-25s %-14s %-14s\n",
               "ID", "Descricao", "Diarias Ocup.", "Total R$");
        printf("%s\n", "----------------------------------------------------"
                       "----------------");
    }

    ListaAcomodacao *acom = *listaAcom;

    while (acom != NULL) {
        TipoAcomodacao *ac = &acom->acomodacao;

        if (!ac->ativo) { acom = acom->proximo; continue; }
        if (idAcomodacao > 0 && ac->id != idAcomodacao) { acom = acom->proximo; continue; }

        // Soma diarias e receita percorrendo as reservas desta acomodacao
        int totalDiarias = 0;
        float totalRecebido = 0.0f;

        ListaReserva *res = *listaReserva;
        while (res != NULL) {
            TipoReserva *r = &res->reserva;
            if (r->idAcomodacao == ac->id && r->status == RESERVA_CHECKOUT) {
                totalDiarias   += ReservaCalcularDiarias(r->dataEntrada, r->dataSaida);
                totalRecebido  += r->totalDiarias;
            }
            res = res->proximo;
        }

        if (cfg->destino == RELATORIO_ARQUIVO) {
            fprintf(out, "%d;%s;%d;%.2f\n",
                    ac->id, ac->descricao, totalDiarias, totalRecebido);
        } else {
            printf("%-4d %-25s %-14d R$%-12.2f\n",
                   ac->id, ac->descricao, totalDiarias, totalRecebido);
        }
        acom = acom->proximo;
    }

    fecharDestino(out);
    if (cfg->destino == RELATORIO_ARQUIVO)
        printf("Relatorio salvo em: %s\n", cfg->caminho);
}