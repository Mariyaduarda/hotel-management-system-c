// view/login_view.c
#include "../common.h"
#include "login_view.h"
#include <openssl/sha.h>
#include <string.h>

/* ── Cores ANSI ─────────────────────────────────────────── */
#define RESET    "\033[0m"
#define NEGRITO  "\033[1m"
#define CIANO    "\033[1;36m"
#define AMARELO  "\033[1;33m"
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

static void linha(const char *texto) {
    printf(CIANO "%s" RESET "  %-51s" CIANO "%s\n" RESET, BORDA, texto, BORDA);
}

/* ── Tela de login ──────────────────────────────────────── */
int telaLogin(ListaOperador **lista, Operador **logado) {
    char usuario[50], senha[100];
    int tentativas = 3;

    printf("\033[H\033[J"); /* limpa tela */

    cabecalho("  HOTEL SISTEMA  --  LOGIN");
    linha("");
    linha("  Bem-vindo! Faca login operador");
    linha("");
    printf(CIANO "%s\n" RESET, FUNDO);

    while (tentativas > 0) {
        printf("\n");
        printf(CINZA "  Usuario : " RESET);
        scanf("%49s", usuario);
        limparBuffer();

        printf(CINZA "  Senha   : " RESET);
        /* Leitura sem eco seria ideal mas requer termios;
           aqui usamos scanf simples para portabilidade */
        scanf("%99s", senha);
        limparBuffer();

        if (OperadorAutenticar(lista, usuario, senha, logado)) {
            printf(VERDE "\n  Login realizado com sucesso! Bem-vindo, %s.\n\n" RESET,
                   (*logado)->nome);
            memset(senha, 0, sizeof(senha));
            return 1; /* sucesso */
        }

        tentativas--;
        memset(senha, 0, sizeof(senha));

        if (tentativas > 0) {
            printf(VERMELHO "\n  Usuario ou senha incorretos. "
                   "Tentativas restantes: %d\n" RESET, tentativas);
        } else {
            printf(VERMELHO "\n  Numero de tentativas esgotado. Encerrando.\n\n" RESET);
        }
    }
    return 0; /* falha */
}

/* ── Tela de primeiro cadastro ──────────────────────────── */
int telaPrimeiroCadastro(ListaOperador **lista) {
    Operador op;
    OperadorInit(&op);
    char senha[100], confirma[100];

    printf("\033[H\033[J");

    cabecalho("  PRIMEIRO ACESSO  --  CADASTRO DE OPERADOR");
    linha("");
    linha("  Nenhum operador encontrado.");
    linha("  Cadastre o administrador do sistema.");
    linha("");
    printf(CIANO "%s\n\n" RESET, FUNDO);

    printf(CINZA "  Nome     : " RESET);
    lerString(op.nome, sizeof(op.nome));

    printf(CINZA "  Usuario  : " RESET);
    lerString(op.usuario, sizeof(op.usuario));

    do {
        printf(CINZA "  Senha    : " RESET);
        scanf("%99s", senha);     limparBuffer();
        printf(CINZA "  Confirme : " RESET);
        scanf("%99s", confirma);  limparBuffer();
        if (strcmp(senha, confirma) != 0)
            printf(VERMELHO "  Senhas nao coincidem. Tente novamente.\n" RESET);
    } while (strcmp(senha, confirma) != 0);

    /* gera hash SHA256 */
    unsigned char hash[SHA256_DIGEST_LENGTH];
    SHA256((unsigned char *)senha, strlen(senha), hash);
    for (int i = 0; i < SHA256_DIGEST_LENGTH; i++)
        sprintf(op.senha + (i * 2), "%02x", hash[i]);
    op.senha[64] = '\0';

    memset(senha,   0, sizeof(senha));
    memset(confirma, 0, sizeof(confirma));

    op.permissoes = PERM_ADMIN;
    op.ativo      = 1;

    if (OperadorCriar(lista, op)) {
        printf(VERDE "\n  Operador \"%s\" cadastrado com sucesso!\n\n" RESET, op.nome);
        return 1;
    }
    printf(VERMELHO "\n  Erro ao cadastrar operador.\n" RESET);
    return 0;
}