// view/hospede_view.c
#include "../common.h"
#include "hospede_view.h"
#include "../controller/hospede_controller.h"

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
        opcao_num = ler_int("");

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
    ler_string("  Nome            : ", h.nome,           sizeof(h.nome));
    ler_string("  CPF             : ", h.cpf,            sizeof(h.cpf));
    ler_string("  Email           : ", h.email,          sizeof(h.email));
    ler_string("  Telefone        : ", h.telefone,       sizeof(h.telefone));
    ler_string("  Sexo            : ", h.sexo,           sizeof(h.sexo));
    ler_string("  Nascimento      : ", h.dataNascimento, sizeof(h.dataNascimento));
    ler_string("  Estado Civil    : ", h.estadoCivil,    sizeof(h.estadoCivil));

    printf(CINZA "\n  -- Endereco --\n" RESET);
    ler_string("  Rua             : ", h.endereco.rua,         sizeof(h.endereco.rua));
    ler_string("  Numero          : ", h.endereco.numero,      sizeof(h.endereco.numero));
    ler_string("  Complemento     : ", h.endereco.complemento, sizeof(h.endereco.complemento));
    ler_string("  Bairro          : ", h.endereco.bairro,      sizeof(h.endereco.bairro));
    ler_string("  Cidade          : ", h.endereco.cidade,      sizeof(h.endereco.cidade));
    ler_string("  Estado (UF)     : ", h.endereco.estado,      sizeof(h.endereco.estado));
    ler_string("  CEP             : ", h.endereco.cep,         sizeof(h.endereco.cep));

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
    id = ler_int("  ID: ");
    controllerHospedeListar(lista, id);
}

/* ── Atualizar ──────────────────────────────────────────── */
void HospedeAtualizarView(ListaHospede **lista) {
    int id, op;
    printf("\n");
    cabecalho("ATUALIZAR HOSPEDE");
    printf(CIANO BORDA RESET "\n" CIANO FUNDO "\n\n" RESET);

    id = ler_int("  ID do hospede: ");

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
    op = ler_int("  Opcao: ");

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

    id = ler_int("  ID do hospede: ");

    TipoHospede *h = controllerHospedeBuscar(lista, id);
    if (!h) { printf(VERMELHO "  Hospede ID %d nao encontrado.\n" RESET, id); return; }

    printf("  Confirma exclusao de \"%s\"? (1=Sim / 0=Nao): ", h->nome);
    int confirma;
    confirma = ler_int("");

    if (confirma == 1) {
        if (controllerHospedeExcluir(lista, id))
            printf(VERDE "  Hospede excluido com sucesso!\n" RESET);
        else
            printf(VERMELHO "  Erro ao excluir hospede.\n" RESET);
    } else {
        printf("  Exclusao cancelada.\n");
    }
}