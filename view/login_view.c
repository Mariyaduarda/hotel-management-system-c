// view/login_view.c
#include "../common.h"
#include "login_view.h"
#include <openssl/sha.h>
#include <string.h>

#define LARGURA 55

#define TOPO  "+-------------------------------------------------------+"
#define MEIO  "+-------------------------------------------------------+"
#define FUNDO "+-------------------------------------------------------+"
#define BORDA "|"

/* ── Helpers ───────────────────────────────────────────── */

static void cabecalho(const char *titulo) {
    printf("%s\n", TOPO);
    printf("%s %-*s %s\n", BORDA, LARGURA, titulo, BORDA);
    printf("%s\n", MEIO);
}

static void linha(const char *texto) {
    printf("%s %-*s %s\n", BORDA, LARGURA, texto, BORDA);
}

static void rodape(void) {
    printf("%s\n", FUNDO);
}

/* ── Tela de login ─────────────────────────────────────── */

int telaLogin(ListaOperador **lista, Operador **logado) {
    char usuario[50], senha[100];
    int tentativas = 3;

    printf("\033[H\033[J");

    cabecalho("HOTEL SISTEMA -- LOGIN");
    linha("");
    linha("Bem-vindo! Faca login do operador.");
    linha("");
    rodape();

    while (tentativas > 0) {

        printf("\n  Usuario : ");
        scanf("%49s", usuario);
        limparBuffer();

        printf("  Senha   : ");
        scanf("%99s", senha);
        limparBuffer();

        if (OperadorAutenticar(lista, usuario, senha, logado)) {

            printf("\n");
            printf(VERDE "  Login realizado com sucesso!\n" RESET);
            printf("  Bem-vindo, %s.\n\n", (*logado)->nome);

            memset(senha, 0, sizeof(senha));
            return 1;
        }

        tentativas--;
        memset(senha, 0, sizeof(senha));

        if (tentativas > 0) {
            printf(VERMELHO
                   "\n  Usuario ou senha incorretos.\n"
                   "  Tentativas restantes: %d\n\n"
                   RESET,
                   tentativas);
        } else {
            printf(VERMELHO
                   "\n  Numero de tentativas esgotado.\n"
                   "  Encerrando sistema.\n\n"
                   RESET);
        }
    }

    return 0;
}

/* ── Primeiro cadastro ─────────────────────────────────── */

int telaPrimeiroCadastro(ListaOperador **lista) {

    Operador op;
    OperadorInit(&op);

    char senha[100], confirma[100];

    printf("\033[H\033[J");

    cabecalho("PRIMEIRO ACESSO -- CADASTRO");
    linha("");
    linha("Nenhum operador encontrado.");
    linha("Cadastre o administrador do sistema.");
    linha("");
    rodape();

    printf("\n");

    printf("  Nome     : ");
    lerString(op.nome, sizeof(op.nome));

    printf("  Usuario  : ");
    lerString(op.usuario, sizeof(op.usuario));

    do {

        printf("  Senha    : ");
        scanf("%99s", senha);
        limparBuffer();

        printf("  Confirme : ");
        scanf("%99s", confirma);
        limparBuffer();

        if (strcmp(senha, confirma) != 0) {
            printf(VERMELHO
                   "  Senhas nao coincidem. Tente novamente.\n"
                   RESET);
        }

    } while (strcmp(senha, confirma) != 0);

    unsigned char hash[SHA256_DIGEST_LENGTH];

    SHA256((unsigned char *)senha, strlen(senha), hash);

    for (int i = 0; i < SHA256_DIGEST_LENGTH; i++) {
        sprintf(op.senha + (i * 2), "%02x", hash[i]);
    }

    op.senha[64] = '\0';

    memset(senha, 0, sizeof(senha));
    memset(confirma, 0, sizeof(confirma));

    op.permissoes = PERM_ADMIN;
    op.ativo = 1;

    if (OperadorCriar(lista, op)) {

        printf(VERDE
               "\n  Operador \"%s\" cadastrado com sucesso!\n\n"
               RESET,
               op.nome);

        return 1;
    }

    printf(VERMELHO
           "\n  Erro ao cadastrar operador.\n\n"
           RESET);

    return 0;
}