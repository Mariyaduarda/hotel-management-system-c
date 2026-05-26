#include "../common.h"
#include "operador.h"

/* ── Operador Globalmente ────────────────────────── */
static Operador operadorAtual = {0};

/* ── Inicializar Operados ───────────────────────────────────────────────── */
void OperadorInit(Operador *op) {
    op->id         = 0;
    op->nome[0]    = '\0';
    op->usuario[0] = '\0';
    op->senha[0]   = '\0';
    op->permissoes = 0;
    op->ativo      = 1;
}

/* ── Lista ──────────────────────────────────────────────── */
void OperadorListaInit(ListaOperador *lista) {
    lista->proximo = NULL;
    OperadorInit(&lista->operador);
}

/* ── Criar Operados ──────────────────────────────────────────────── */
int OperadorCriar(ListaOperador **lista, Operador op) {
    ListaOperador *novo = (ListaOperador *)malloc(sizeof(ListaOperador));
    if (!novo) return 0;

    novo->operador = op;
    novo->proximo  = NULL;

    if (*lista == NULL) {
        novo->operador.id = 1;
        *lista = novo;
    } else {
        ListaOperador *atual = *lista;
        while (atual->proximo) atual = atual->proximo;
        novo->operador.id = atual->operador.id + 1;
        atual->proximo = novo;
    }
    return 1;
}

/* ── Listar Operadores ─────────────────────────────────────────────── */
void OperadorListar(ListaOperador **lista, int id) {
    ListaOperador *atual = *lista;
    while (atual) {
        if (id == 0 || atual->operador.id == id) {
            Operador *op = &atual->operador;
            printf("ID: %d | Usuario: %s | Nome: %s | Ativo: %s\n",
                   op->id, op->usuario, op->nome, op->ativo ? "Sim" : "Nao");
        }
        atual = atual->proximo;
    }
}

/* ── Buscar Operador ──────────────────────────────────────────────── */
Operador *OperadorBuscar(ListaOperador **lista, int id) {
    ListaOperador *atual = *lista;
    while (atual) {
        if (atual->operador.id == id) return &atual->operador;
        atual = atual->proximo;
    }
    return NULL;
}

/* ── Buscar Operador por Usuario ──────────────────────────────────────────────── */
Operador *OperadorBuscarPorUsuario(ListaOperador **lista, const char *usuario) {
    ListaOperador *atual = *lista;
    while (atual) {
        if (strcmp(atual->operador.usuario, usuario) == 0)
            return &atual->operador;
        atual = atual->proximo;
    }
    return NULL;
}

/* ── Excluir Operador ────────────────────────────────────────────── */
int OperadorExcluir(ListaOperador **lista, int id) {
    ListaOperador *atual = *lista, *anterior = NULL;
    while (atual) {
        if (atual->operador.id == id) {
            atual->operador.ativo = 0; /* exclusao logica: inativa */
            return 1;
        }
        anterior = atual;
        atual = atual->proximo;
    }
    (void)anterior;
    return 0;
}

/* ── Atualizar Operador ──────────────────────────────────────────── */
int OperadorAtualizar(ListaOperador **lista, int id, int op) {
    Operador *o = OperadorBuscar(lista, id);
    if (!o) return 0;
    char novaSenha[100], confirma[100];
    switch (op) {
        case 1: printf("Novo nome: ");    lerString(o->nome,    sizeof(o->nome));    break;
        case 2: printf("Novo usuario: "); lerString(o->usuario, sizeof(o->usuario)); break;
        case 3:
            do {
                printf("Nova senha: ");    scanf("%99s", novaSenha);  limparBuffer();
                printf("Confirme: ");      scanf("%99s", confirma);   limparBuffer();
                if (strcmp(novaSenha, confirma) != 0)
                    printf("Senhas nao coincidem.\n");
            } while (strcmp(novaSenha, confirma) != 0);
            strcpy(o->senha, novaSenha);
            memset(novaSenha, 0, sizeof(novaSenha));
            memset(confirma,  0, sizeof(confirma));
            break;
        default: return 0;
    }
    return 1;
}

/* ── Liberar Lista ────────────────────────────────────────────── */
void OperadorListaLiberar(ListaOperador *lista) {
    ListaOperador *atual = lista;
    while (atual) {
        ListaOperador *prox = atual->proximo;
        free(atual);
        atual = prox;
    }
}

/* ── Autenticacao do Operados: Login───────────────────────────────────────── */
int OperadorAutenticar(ListaOperador **lista, const char *usuario,
                        const char *senha, Operador **logado) {
    Operador *op = OperadorBuscarPorUsuario(lista, usuario);
    //verifica se existe
    if (!op || !op->ativo) return 0;

    // Comparar senha digitada com a senha armazenada
    if (strcmp(op->senha, senha) != 0) return 0;

    // funcionou a autenticacao vem p ca
    *logado = op;
    operadorAtual = *op; /* salva globalmente */
    return 1;
}

int OperadorTemPermissao(Operador *op, int permissao) {
    return (op->permissoes & permissao) != 0;
}

/* ── Funções globais  ──────────────────── */
void criarOperador(void) {
    char senha[100], confirmacao[100];

    printf(" -- Cadastro de Operador -- \n");
    operadorAtual.id = 1;
    printf("Usuario: "); scanf("%49s", operadorAtual.usuario); limparBuffer();
    printf("Nome: ");    scanf("%99s", operadorAtual.nome);    limparBuffer();

    do {
        printf("Senha: ");         scanf("%99s", senha);        limparBuffer();
        printf("Confirme a senha: "); scanf("%99s", confirmacao); limparBuffer();
        if (strcmp(senha, confirmacao) != 0)
            printf("As senhas nao coincidem. Tente novamente.\n");
    } while (strcmp(senha, confirmacao) != 0);

    strcpy(operadorAtual.senha, senha);
    operadorAtual.permissoes = PERM_ADMIN;
    operadorAtual.ativo      = 1;

    memset(senha,        0, sizeof(senha));
    memset(confirmacao,  0, sizeof(confirmacao));

    printf("Operador %s criado com sucesso!\n", operadorAtual.nome);
}

const Operador *obterOperador(void) { return &operadorAtual; }

/* ── Arquivos .TXT/.BIN───────────────────────────────────────────── */
int OperadorSalvarBin(ListaOperador *lista) {
    FILE *fp = fopen("dados/operadores.bin", "wb");
    if (!fp) return 0;
    ListaOperador *atual = lista;
    while (atual) {
        fwrite(&atual->operador, sizeof(Operador), 1, fp);
        atual = atual->proximo;
    }
    fclose(fp);
    return 1;
}

int OperadorSalvarTxt(ListaOperador *lista) {
    FILE *fp = fopen("dados/operadores.txt", "w");
    if (!fp) return 0;
    ListaOperador *atual = lista;
    while (atual) {
        Operador *op = &atual->operador;
        fprintf(fp, "%d;%s;%s;%s;%d;%d\n",
                op->id, op->usuario, op->nome, op->senha,
                op->permissoes, op->ativo);
        atual = atual->proximo;
    }
    fclose(fp);
    return 1;
}

int OperadorLerBin(ListaOperador **lista) {
    FILE *fp = fopen("dados/operadores.bin", "rb");
    if (!fp) return 0;
    Operador op;
    while (fread(&op, sizeof(Operador), 1, fp) == 1)
        OperadorCriar(lista, op);
    fclose(fp);
    return 1;
}

int OperadorLerTxt(ListaOperador **lista) {
    FILE *fp = fopen("dados/operadores.txt", "r");
    if (!fp) return 0;
    char linha[300];
    while (fgets(linha, sizeof(linha), fp)) {
        Operador op;
        sscanf(linha, "%d;%49[^;];%99[^;];%64[^;];%d;%d",
               &op.id, op.usuario, op.nome, op.senha,
               &op.permissoes, &op.ativo);
        OperadorCriar(lista, op);
    }
    fclose(fp);
    return 1;
}