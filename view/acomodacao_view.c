#include "acomodacao_view.h"
#include "../common.h"
#include "../controller/acomodacao_controller.h"
#include "../model/acomodacao.h"
#include "../model/categoria_acomodacao.h"

void AcomodacaoMenuExibir(void) {
    printf("\n╔══════════════════════════════╗\n");
    printf(  "║       MENU DE ACOMODACAO     ║\n");
    printf(  "╠══════════════════════════════╣\n");
    printf(  "║ 1. Cadastrar acomodacao      ║\n");
    printf(  "║ 2. Listar acomodacoes        ║\n");
    printf(  "║ 3. Buscar acomodacao por ID  ║\n");
    printf(  "║ 4. Atualizar acomodacao      ║\n");
    printf(  "║ 5. Excluir acomodacao        ║\n");
    printf(  "║ 0. Voltar                    ║\n");
    printf(  "╚══════════════════════════════╝\n");
    printf("Opcao: ");
}

void AcomodacaoCadastrarView(ListaAcomodacao **lista,
                                ListaCategoria  **listaCat)
{
    TipoAcomodacao a;
    AcomodacaoInit(&a);

    printf("\n-- Cadastro de Acomodacao --\n");

    printf("Descricao: ");
    scanf(" %99[^\n]", a.descricao);

    printf("Facilidades: ");
    scanf(" %199[^\n]", a.facilidades);

    printf("ID da categoria: ");
    scanf("%d", &a.idCategoria);
    limparBuffer();

    if (AcomodacaoCriar(lista, a))
        printf("Acomodacao cadastrada com sucesso!\n");
    else
        printf("Erro ao cadastrar acomodacao.\n");
}

void AcomodacaoListarView(ListaAcomodacao **lista,
                            ListaCategoria  **listaCat)
{
    int id;
    printf("\n-- Listar Acomodacao --\n");
    printf("ID da acomodacao (0 para listar todas): ");
    scanf("%d", &id);
    limparBuffer();

    AcomodacaoListar(lista, id, listaCat);
}

void AcomodacaoAtualizarView(ListaAcomodacao **lista,
                                ListaCategoria  **listaCat)
{
    int id, op;
    printf("\n-- Atualizar Acomodacao --\n");
    printf("ID da acomodacao: ");
    scanf("%d", &id);
    limparBuffer();

    TipoAcomodacao *a = AcomodacaoBuscar(lista, id);
    if (!a) {
        printf("Acomodacao ID %d nao encontrada.\n", id);
        return;
    }

    printf("Acomodacao encontrada: %s\n", a->descricao);
    printf("\nO que deseja atualizar?\n");
    printf("1. Descricao\n");
    printf("2. Facilidades\n");
    printf("3. ID categoria\n");
    printf("Opcao: ");
    scanf("%d", &op);
    limparBuffer();

    if (AcomodacaoAtualizar(lista, id, op))
        printf("Acomodacao atualizada com sucesso!\n");
    else
        printf("Erro ao atualizar acomodacao.\n");
}

void AcomodacaoExcluirView(ListaAcomodacao **lista) {
    int id;
    printf("\n-- Excluir Acomodacao --\n");
    printf("ID da acomodacao: ");
    scanf("%d", &id);
    limparBuffer();

    TipoAcomodacao *a = AcomodacaoBuscar(lista, id);
    if (!a) {
        printf("Acomodacao ID %d nao encontrada.\n", id);
        return;
    }

    printf("Confirma exclusao de \"%s\"? (1=Sim / 0=Nao): ", a->descricao);
    int confirma;
    scanf("%d", &confirma);
    limparBuffer();

    if (confirma) {
        if (AcomodacaoExcluir(lista, id))
            printf("Acomodacao excluida com sucesso!\n");
        else
            printf("Erro ao excluir acomodacao.\n");
    } else {
        printf("Exclusao cancelada.\n");
    }
}

void AcomodacaoBuscarView(ListaAcomodacao **lista,
                                ListaCategoria  **listaCat)
{
    int id;
    printf("\n-- Buscar Acomodacao por ID --\n");
    printf("ID da acomodacao: ");
    scanf("%d", &id);
    limparBuffer();

    TipoAcomodacao *a = AcomodacaoBuscar(lista, id);
    if (!a) {
        printf("Acomodacao ID %d nao encontrada.\n", id);
        return;
    }

    printf("Acomodacao encontrada:\n");
    AcomodacaoListar(lista, id, listaCat);
}


