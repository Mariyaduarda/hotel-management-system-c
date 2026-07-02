#include "acomodacao_view.h"
#include "../common.h"
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

void AcomodacaoMenuExecutar(ListaAcomodacao **lista,
                           ListaCategoria  **listaCat)
{
    int opcao;
    do {
        printf("\n");
        AcomodacaoMenuExibir();
        opcao = ler_int("");

        switch (opcao) {
            case 1: AcomodacaoCadastrarView(lista, listaCat); break;
            case 2: AcomodacaoListarView(lista, listaCat);    break;
            case 3: AcomodacaoBuscarView(lista, listaCat);    break;
            case 4: AcomodacaoAtualizarView(lista, listaCat); break;
            case 5: AcomodacaoExcluirView(lista);             break;
            case 0: break;
            default:
                printf("Opcao invalida.\n");
        }
    } while (opcao != 0);
}

void AcomodacaoCadastrarView(ListaAcomodacao **lista,
                                ListaCategoria  **listaCat)
{    (void)listaCat; /* parâmetro nao utilizado */    TipoAcomodacao a;
    AcomodacaoInit(&a);

    printf("\n-- Cadastro de Acomodacao --\n");

    ler_string("Descricao: ", a.descricao, sizeof(a.descricao));
    ler_string("Facilidades: ", a.facilidades, sizeof(a.facilidades));
    a.idCategoria = ler_int("ID da categoria: ");

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
    id = ler_int("ID da acomodacao (0 para listar todas): ");

    AcomodacaoListar(lista, id, listaCat);
}

void AcomodacaoAtualizarView(ListaAcomodacao **lista,
                                ListaCategoria  **listaCat)
{
    (void)listaCat; /* parâmetro nao utilizado */
    int id, op;
    printf("\n-- Atualizar Acomodacao --\n");
    id = ler_int("ID da acomodacao: ");

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
    op = ler_int("Opcao: ");

    if (AcomodacaoAtualizar(lista, id, op))
        printf("Acomodacao atualizada com sucesso!\n");
    else
        printf("Erro ao atualizar acomodacao.\n");
}

void AcomodacaoExcluirView(ListaAcomodacao **lista) {
    int id;
    printf("\n-- Excluir Acomodacao --\n");
    id = ler_int("ID da acomodacao: ");

    TipoAcomodacao *a = AcomodacaoBuscar(lista, id);
    if (!a) {
        printf("Acomodacao ID %d nao encontrada.\n", id);
        return;
    }

    printf("Confirma exclusao de \"%s\"? (1=Sim / 0=Nao): ", a->descricao);
    int confirma;
    confirma = ler_int("");

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
    id = ler_int("ID da acomodacao: ");

    TipoAcomodacao *a = AcomodacaoBuscar(lista, id);
    if (!a) {
        printf("Acomodacao ID %d nao encontrada.\n", id);
        return;
    }

    printf("Acomodacao encontrada:\n");
    AcomodacaoListar(lista, id, listaCat);
}


