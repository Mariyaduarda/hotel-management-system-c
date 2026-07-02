
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

void CategoriaMenuExecutar(ListaCategoria **lista) {
    int opcao;
    do {
        CategoriaMenuExibir();
        printf("Opcao: ");
        opcao = ler_int("");

        switch (opcao) {
            case 1: CategoriaCadastrarView(lista);  break;
            case 2: CategoriaListarTodosView(lista); break;
            case 3: CategoriaBuscarView(lista);     break;
            case 4: CategoriaAtualizarView(lista);  break;
            case 5: CategoriaExcluirView(lista);    break;
            case 0: break;
            default: printf("Opcao invalida.\n");
        }
    } while (opcao != 0);
}
/* ══════════════════════════════════════
   Cadastrar nova categoria
   ══════════════════════════════════════ */
void CategoriaCadastrarView(ListaCategoria **lista) {
    TipoCategoria cat;
    CategoriasInit(&cat);

    printf("\n--- Cadastrar Categoria ---\n");

    ler_string(" Descricao: ", cat.descricao, sizeof(cat.descricao));
    cat.valorDiaria = ler_float(" Valor da diaria: R$ ");
    cat.maxAdultos  = ler_int(" Max adultos:  ");
    cat.maxCriancas = ler_int(" Max criancas: ");

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
    id = ler_int("\nID da categoria: ");

    CategoriaListar(lista, id);
}

/* ══════════════════════════════════════
   Atualizar campo de uma categoria
   ══════════════════════════════════════ */
void CategoriaAtualizarView(ListaCategoria **lista) {
    int id;
    id = ler_int("\nID da categoria a atualizar: ");

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

    int op;
    op = ler_int("Opcao: ");

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
    id = ler_int("\nID da categoria a excluir: ");

    // Confirma antes de excluir
    TipoCategoria *c = CategoriaBuscar(lista, id);
    if (!c) {
        printf(VERMELHO "Categoria nao encontrada.\n" RESET);
        return;
    }

    printf("Confirma exclusao de \"%s\"? (S/N): ", c->descricao);
    char conf;
    conf = ler_char("");

    if (toupper(conf) != 'S') {
        printf(AMARELO "Operacao cancelada.\n" RESET);
        return;
    }

    if (CategoriaExcluir(lista, id))
        printf(VERDE "Categoria excluida com sucesso!\n" RESET);
    else
        printf(VERMELHO "Erro ao excluir categoria.\n" RESET);
}