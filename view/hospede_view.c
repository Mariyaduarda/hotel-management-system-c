// view/hospede_view.c
#include "../common.h"
#include "hospede_view.h"
#include "../controller/hospede_controller.h"

/* ── Cores ANSI ─────────────────────────────────────────── */
#define RESET    "\033[0m"
#define NEGRITO  "\033[1m"
#define CIANO    "\033[1;36m"
#define VERDE    "\033[1;32m"
#define VERMELHO "\033[1;31m"
#define CINZA    "\033[0;90m"

#define TOPO  "╔═══════════════════════════════════════════════════════╗"
#define MEIO  "╠═══════════════════════════════════════════════════════╣"
#define FUNDO "╚═══════════════════════════════════════════════════════╝"
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

/* ── Menu ───────────────────────────────────────────────── */
void menuHospede(ListaHospede **lista) {
    int opcao_num;
    do {
        printf("\n");
        cabecalho("HOSPEDES");
        opcao("1", "Cadastrar hospede");
        opcao("2", "Listar todos");
        opcao("3", "Buscar por ID");
        opcao("4", "Atualizar hospede");
        opcao("5", "Excluir hospede");
        separador();
        opcao("0", "Voltar");
        rodape();
        scanf("%d", &opcao_num);
        limparBuffer();

        switch (opcao_num) {
            case 1: HospedeCadastrarView(lista);    break;
            case 2: HospedeListarTodosView(lista);  break;
            case 3: HospedeBuscarView(lista);       break;
            case 4: HospedeAtualizarView(lista);    break;
            case 5: HospedeExcluirView(lista);      break;
            case 0: break;
            default: printf(VERMELHO "  Opcao invalida.\n" RESET);
        }
    } while (opcao_num != 0);
}

/* ── Cadastrar ──────────────────────────────────────────── */
void HospedeCadastrarView(ListaHospede **lista) {
    TipoHospede h;
    HospedeInit(&h);

    printf("\n");
    cabecalho("CADASTRO DE HOSPEDE");
    printf(CIANO BORDA RESET "\n" CIANO FUNDO "\n\n" RESET);

    printf(CINZA "  -- Dados pessoais --\n" RESET);
    printf("  Nome            : "); lerString(h.nome,           sizeof(h.nome));
    printf("  CPF             : "); lerString(h.cpf,            sizeof(h.cpf));
    printf("  Email           : "); lerString(h.email,          sizeof(h.email));
    printf("  Telefone        : "); lerString(h.telefone,       sizeof(h.telefone));
    printf("  Sexo            : "); lerString(h.sexo,           sizeof(h.sexo));
    printf("  Nascimento      : "); lerString(h.dataNascimento, sizeof(h.dataNascimento));
    printf("  Estado Civil    : "); lerString(h.estadoCivil,    sizeof(h.estadoCivil));

    printf(CINZA "\n  -- Endereco --\n" RESET);
    printf("  Rua             : "); lerString(h.endereco.rua,         sizeof(h.endereco.rua));
    printf("  Numero          : "); lerString(h.endereco.numero,      sizeof(h.endereco.numero));
    printf("  Complemento     : "); lerString(h.endereco.complemento, sizeof(h.endereco.complemento));
    printf("  Bairro          : "); lerString(h.endereco.bairro,      sizeof(h.endereco.bairro));
    printf("  Cidade          : "); lerString(h.endereco.cidade,      sizeof(h.endereco.cidade));
    printf("  Estado (UF)     : "); lerString(h.endereco.estado,      sizeof(h.endereco.estado));
    printf("  CEP             : "); lerString(h.endereco.cep,         sizeof(h.endereco.cep));

    if (controllerHospedeCadastrar(lista, h))
        printf(VERDE "\n  Hospede cadastrado com sucesso!\n" RESET);
    else
        printf(VERMELHO "\n  Erro ao cadastrar hospede.\n" RESET);
}

/* ── Listar todos ───────────────────────────────────────── */
void HospedeListarTodosView(ListaHospede **lista) {
    if (!lista || !*lista) {
        printf(VERMELHO "\n  Nenhum hospede cadastrado.\n" RESET);
        return;
    }

    printf("\n");
    cabecalho("LISTA DE HOSPEDES");

    ListaHospede *atual = *lista;
    while (atual) {
        TipoHospede *h = &atual->hospede;
        printf(CIANO "%s\n" RESET, MEIO);
        printf(CIANO BORDA RESET "  " NEGRITO "ID %-3d  %s" RESET "\n", h->id, h->nome);
        printf(CIANO "%s\n" RESET, MEIO);
        printf(CIANO BORDA RESET "  CPF       : %-47s" CIANO BORDA "\n" RESET, h->cpf);
        printf(CIANO BORDA RESET "  Email     : %-47s" CIANO BORDA "\n" RESET, h->email);
        printf(CIANO BORDA RESET "  Telefone  : %-47s" CIANO BORDA "\n" RESET, h->telefone);
        printf(CIANO BORDA RESET "  Sexo      : %-47s" CIANO BORDA "\n" RESET, h->sexo);
        printf(CIANO BORDA RESET "  Nasc.     : %-47s" CIANO BORDA "\n" RESET, h->dataNascimento);
        printf(CIANO BORDA RESET "  Est.Civil : %-47s" CIANO BORDA "\n" RESET, h->estadoCivil);
        printf(CIANO BORDA RESET "  Endereco  : %s, %s - %s" "\n" RESET,
               h->endereco.rua, h->endereco.numero, h->endereco.cidade);
        printf(CIANO BORDA RESET "  Ativo     : %-47s" CIANO BORDA "\n" RESET,
               h->ativo ? "Sim" : "Nao");
        atual = atual->proximo;
    }
    printf(CIANO "%s\n" RESET, FUNDO);
}

/* ── Buscar ─────────────────────────────────────────────── */
void HospedeBuscarView(ListaHospede **lista) {
    int id;
    printf("\n");
    cabecalho("BUSCAR HOSPEDE");
    printf(CIANO BORDA RESET "\n" CIANO FUNDO "\n\n" RESET);
    printf("  ID: ");
    scanf("%d", &id);
    limparBuffer();
    controllerHospedeListar(lista, id);
}

/* ── Atualizar ──────────────────────────────────────────── */
void HospedeAtualizarView(ListaHospede **lista) {
    int id, op;
    printf("\n");
    cabecalho("ATUALIZAR HOSPEDE");
    printf(CIANO BORDA RESET "\n" CIANO FUNDO "\n\n" RESET);

    printf("  ID do hospede: ");
    scanf("%d", &id);
    limparBuffer();

    TipoHospede *h = controllerHospedeBuscar(lista, id);
    if (!h) { printf(VERMELHO "  Hospede ID %d nao encontrado.\n" RESET, id); return; }

    printf(VERDE "  Hospede: %s\n\n" RESET, h->nome);
    printf(CINZA "  -- Dados pessoais --\n" RESET);
    printf("   1. Todos os campos\n");
    printf("   2. Nome          9.  Rua\n");
    printf("   3. CPF          10.  Numero\n");
    printf("   4. Email        11.  Complemento\n");
    printf("   5. Telefone     12.  Bairro\n");
    printf("   6. Sexo         13.  Cidade\n");
    printf("   7. Nascimento   14.  Estado\n");
    printf("   8. Est. Civil   15.  CEP\n");
    printf("  Opcao: ");
    scanf("%d", &op);
    limparBuffer();

    if (controllerHospedeAtualizar(lista, id, op))
        printf(VERDE "  Hospede atualizado com sucesso!\n" RESET);
    else
        printf(VERMELHO "  Erro ao atualizar hospede.\n" RESET);
}

/* ── Excluir ────────────────────────────────────────────── */
void HospedeExcluirView(ListaHospede **lista) {
    int id;
    printf("\n");
    cabecalho("EXCLUIR HOSPEDE");
    printf(CIANO BORDA RESET "\n" CIANO FUNDO "\n\n" RESET);

    printf("  ID do hospede: ");
    scanf("%d", &id);
    limparBuffer();

    TipoHospede *h = controllerHospedeBuscar(lista, id);
    if (!h) { printf(VERMELHO "  Hospede ID %d nao encontrado.\n" RESET, id); return; }

    printf("  Confirma exclusao de \"%s\"? (1=Sim / 0=Nao): ", h->nome);
    int confirma;
    scanf("%d", &confirma);
    limparBuffer();

    if (confirma == 1) {
        if (controllerHospedeExcluir(lista, id))
            printf(VERDE "  Hospede excluido com sucesso!\n" RESET);
        else
            printf(VERMELHO "  Erro ao excluir hospede.\n" RESET);
    } else {
        printf("  Exclusao cancelada.\n");
    }
}