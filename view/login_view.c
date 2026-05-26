// view/login_view.c
#include "../common.h"
#include "login_view.h"
#include <string.h>

#define TOPO  "╔═══════════════════════════════════════════════════════╗"
#define MEIO  "╠═══════════════════════════════════════════════════════╣"
#define FUNDO "╚═══════════════════════════════════════════════════════╝"
#define BORDA "║"

static void cabecalho(const char *titulo) {
    printf("%s\n", TOPO);
    printf("%s  %-51s%s\n", BORDA, titulo, BORDA);
    printf("%s\n", MEIO);
}

static void linha(const char *texto) {
    printf("%s  %-51s%s\n", BORDA, texto, BORDA);
}

int telaLogin(ListaOperador **lista, Operador **logado) {
    char usuario[50], senha[100];
    int tentativas = 3;

    printf("\033[H\033[J");

    cabecalho("  HOTEL SISTEMA  --  LOGIN");
    linha("");
    linha("  Bem-vindo! Faca login operador");
    linha("");
    printf("%s\n", FUNDO);

    while (tentativas > 0) {
        printf("\n");
        printf("  Usuario : ");
        scanf("%49s", usuario);
        limparBuffer();

        printf("  Senha   : ");
        scanf("%99s", senha);
        limparBuffer();

        if (OperadorAutenticar(lista, usuario, senha, logado)) {
            printf("\n  Login realizado com sucesso! Bem-vindo, %s.\n\n",
                   (*logado)->nome);
            memset(senha, 0, sizeof(senha));
            return 1;
        }

        tentativas--;
        memset(senha, 0, sizeof(senha));

        if (tentativas > 0) {
            printf("\n  Usuario ou senha incorretos. Tentativas restantes: %d\n",
                   tentativas);
        } else {
            printf("\n  Numero de tentativas esgotado. Encerrando.\n\n");
        }
    }
    return 0;
}

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
    printf("%s\n\n", FUNDO);

    printf("  Nome     : ");
    lerString(op.nome, sizeof(op.nome));

    printf("  Usuario  : ");
    lerString(op.usuario, sizeof(op.usuario));

    do {
        printf("  Senha    : ");
        scanf("%99s", senha);    limparBuffer();
        printf("  Confirme : ");
        scanf("%99s", confirma); limparBuffer();
        if (strcmp(senha, confirma) != 0)
            printf("  Senhas nao coincidem. Tente novamente.\n");
    } while (strcmp(senha, confirma) != 0);

    // Armazenar senha em texto plano
    strcpy(op.senha, senha);

    memset(senha,    0, sizeof(senha));
    memset(confirma, 0, sizeof(confirma));

    op.permissoes = PERM_ADMIN;
    op.ativo      = 1;

    if (OperadorCriar(lista, op)) {
        printf("\n  Operador \"%s\" cadastrado com sucesso!\n\n", op.nome);
        return 1;
    }
    printf("\n  Erro ao cadastrar operador.\n");
    return 0;
}