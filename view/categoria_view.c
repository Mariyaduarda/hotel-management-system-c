
#include "../common.h"
#include "../model/categoria_acomodacao.h"
#include "categoria_view.h"

void CategoriaMenuExibir(void) {
    printf("\n╔══════════════════════════════╗\n");
    printf(  "║       MENU DE CATEGORIAS     ║\n");
    printf(  "╠══════════════════════════════╣\n");
    printf(  "║ 1. Cadastrar categoria       ║\n");
    printf(  "║ 2. Listar todas as categorias║\n");
    printf(  "║ 3. Buscar categoria por ID   ║\n");
    printf(  "║ 4. Atualizar categoria       ║\n");
    printf(  "║ 5. Excluir categoria         ║\n");
    printf(  "║ 0. Voltar                    ║\n");
    printf(  "╚══════════════════════════════╝\n");
}
/* ══════════════════════════════════════
   Cadastrar nova categoria
   ══════════════════════════════════════ */
void CategoriaCadastrarView(ListaCategoria **lista) {
    TipoCategoria cat;
    CategoriasInit(&cat);

    printf("\n--- Cadastrar Categoria ---\n");

    printf("Descricao: ");
    lerString(cat.descricao, sizeof(cat.descricao));

    printf("Valor da diaria: R$ ");
    scanf("%f", &cat.valorDiaria);
    limparBuffer();

    printf("Max adultos: ");
    scanf("%d", &cat.maxAdultos);
    limparBuffer();

    printf("Max criancas: ");
    scanf("%d", &cat.maxCriancas);
    limparBuffer();

    if (CategoriaCriar(lista, cat))
        printf(VERDE "Categoria cadastrada com sucesso!\n" RESET);
    else
        printf(VERMELHO "Erro ao cadastrar categoria.\n" RESET);
}

/* ══════════════════════════════════════
   Listar todas as categorias ativas
   ══════════════════════════════════════ */
void CategoriaListarTodosView(ListaCategoria **lista) {
    if (!lista || !*lista) {
        printf(AMARELO "Nenhuma categoria cadastrada.\n" RESET);
        return;
    }

    printf("\n");
    printf(CIANO "%-5s %-30s %-12s %-8s %-8s\n" RESET,
           "ID", "Descricao", "Diaria(R$)", "Adultos", "Criancas");
    printf("--------------------------------------------------------------\n");

    ListaCategoria *atual = *lista;
    int encontrou = 0;

    while (atual != NULL) {
        TipoCategoria *c = &atual->categoria;
        if (c->ativo) {
            printf("%-5d %-30s %-12.2f %-8d %-8d\n",
                   c->id, c->descricao, c->valorDiaria,
                   c->maxAdultos, c->maxCriancas);
            encontrou = 1;
        }
        atual = atual->proximo;
    }

    if (!encontrou)
        printf(AMARELO "Nenhuma categoria ativa encontrada.\n" RESET);
}

/* ══════════════════════════════════════
   Buscar categoria por ID
   ══════════════════════════════════════ */
void CategoriaBuscarView(ListaCategoria **lista) {
    int id;
    printf("\nID da categoria: ");
    scanf("%d", &id);
    limparBuffer();

    CategoriaListar(lista, id);
}

/* ══════════════════════════════════════
   Atualizar campo de uma categoria
   ══════════════════════════════════════ */
void CategoriaAtualizarView(ListaCategoria **lista) {
    int id;
    printf("\nID da categoria a atualizar: ");
    scanf("%d", &id);
    limparBuffer();

    // Mostra estado atual antes de editar
    TipoCategoria *c = CategoriaBuscar(lista, id);
    if (!c) {
        printf(VERMELHO "Categoria nao encontrada.\n" RESET);
        return;
    }

    printf("\nCategoria atual:\n");
    CategoriaListar(lista, id);

    printf("\nO que deseja atualizar?\n");
    printf("1. Descricao\n");
    printf("2. Valor da diaria\n");
    printf("3. Max adultos\n");
    printf("4. Max criancas\n");
    printf("Opcao: ");

    int op;
    scanf("%d", &op);
    limparBuffer();

    if (CategoriaAtualizar(lista, id, op))
        printf(VERDE "Categoria atualizada com sucesso!\n" RESET);
    else
        printf(VERMELHO "Erro ao atualizar categoria.\n" RESET);
}

/* ══════════════════════════════════════
   Excluir (desativar) categoria
   ══════════════════════════════════════ */
void CategoriaExcluirView(ListaCategoria **lista) {
    int id;
    printf("\nID da categoria a excluir: ");
    scanf("%d", &id);
    limparBuffer();

    // Confirma antes de excluir
    TipoCategoria *c = CategoriaBuscar(lista, id);
    if (!c) {
        printf(VERMELHO "Categoria nao encontrada.\n" RESET);
        return;
    }

    printf("Confirma exclusao de \"%s\"? (S/N): ", c->descricao);
    char conf;
    scanf(" %c", &conf);
    limparBuffer();

    if (toupper(conf) != 'S') {
        printf(AMARELO "Operacao cancelada.\n" RESET);
        return;
    }

    if (CategoriaExcluir(lista, id))
        printf(VERDE "Categoria excluida com sucesso!\n" RESET);
    else
        printf(VERMELHO "Erro ao excluir categoria.\n" RESET);
}