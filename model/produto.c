#include "../common.h"
#include "produto.h"

#define ARQUIVO_BIN "dados/produtos.bin"
#define ARQUIVO_TXT "dados/produtos.txt"

/* ── Operador Globalmente ────────────────────────── */
void ProdutoInit(TipoProduto *produto) {
    if (!produto) return;
    produto->id           = 0;
    produto->descricao[0] = '\0';
    produto->estoque      = 0;
    produto->estoqueMinimo = 0;
    produto->precoCusto   = 0.0f;
    produto->precoVenda   = 0.0f;
    produto->ativo        = 1;
}

/* ── Inicializar Lista de Produtos ────────────────────────── */
void ProdutoListaInit(ListaProduto *lista) {
    if (!lista) return;
    lista->proximo = NULL;
    ProdutoInit(&lista->produto);
}

/* gerar proximo ID percorrendo a lista */
static int proximoId(ListaProduto *lista) {
    int maior = 0;
    ListaProduto *atual = lista;
    while (atual) {
        if (atual->produto.id > maior)
            maior = atual->produto.id;
        atual = atual->proximo;
    }
    return maior + 1;
}

/* ── Criar Produto ────────────────────────── */
int ProdutoCriar(ListaProduto **lista, TipoProduto produto) {
    if (!lista) return 0;

    ListaProduto *novo = (ListaProduto *)malloc(sizeof(ListaProduto));
    if (!novo) {
        printf("Erro: falha ao alocar memoria para produto.\n");
        return 0;
    }

    produto.id    = proximoId(*lista);
    produto.ativo = 1;
    novo->produto = produto;
    novo->proximo = NULL;

    /* insere no final da lista */
    if (*lista == NULL) {
        *lista = novo;
    } else {
        ListaProduto *atual = *lista;
        while (atual->proximo)
            atual = atual->proximo;
        atual->proximo = novo;
    }

    printf("Produto \"%s\" criado com ID %d.\n", produto.descricao, produto.id);
    return produto.id;
}

/* ── Listar Produtos ────────────────────────── */
void ProdutoListar(ListaProduto **lista, int id) {
    if (!lista || !*lista) {
        printf("Nenhum produto cadastrado.\n");
        return;
    }

    printf("\n%-5s %-30s %-8s %-10s %-12s %-12s %-6s\n",
           "ID", "Descricao", "Estoque", "Est.Min.", "Preco Custo", "Preco Venda", "Ativo");
    printf("%s\n", "----------------------------------------------------------------------"
                   "-------------------");

    ListaProduto *atual = *lista;
    while (atual) {
        TipoProduto *p = &atual->produto;
        /* Se id == 0 lista todos; caso contrario filtra pelo id */
        if (id == 0 || p->id == id) {
            printf("%-5d %-30s %-8d %-10d %-12.2f %-12.2f %-6s\n",
                   p->id, p->descricao, p->estoque, p->estoqueMinimo,
                   p->precoCusto, p->precoVenda,
                   p->ativo ? "Sim" : "Nao");
        }
        atual = atual->proximo;
    }
}

/* ── Buscar Produto ────────────────────────── */
TipoProduto *ProdutoBuscar(ListaProduto **lista, int id) {
    if (!lista) return NULL;
    ListaProduto *atual = *lista;
    while (atual) {
        if (atual->produto.id == id)
            return &atual->produto;
        atual = atual->proximo;
    }
    return NULL;
}

/* ── Excluir Produto ────────────────────────── */
int ProdutoExcluir(ListaProduto **lista, int id) {
    if (!lista || !*lista) return 0;

    ListaProduto *atual    = *lista;
    ListaProduto *anterior = NULL;

    while (atual) {
        if (atual->produto.id == id) {
            if (anterior)
                anterior->proximo = atual->proximo;
            else
                *lista = atual->proximo;
            free(atual);
            printf("Produto ID %d removido.\n", id);
            return 1;
        }
        anterior = atual;
        atual    = atual->proximo;
    }

    printf("Produto ID %d nao encontrado.\n", id);
    return 0;
}

/*
 * op — campo a atualizar:
 *   1 = descricao
 *   2 = estoque
 *   3 = estoque minimo
 *   4 = preco de custo
 *   5 = preco de venda
 *   6 = ativo (toggle)
 */

/* ── Atualizar Produto ────────────────────────── */
int ProdutoAtualizar(ListaProduto **lista, int id, int op) {
    TipoProduto *p = ProdutoBuscar(lista, id);
    if (!p) {
        printf("Produto ID %d nao encontrado.\n", id);
        return 0;
    }

    switch (op) {
        case 1:
            ler_string("Nova descricao: ", p->descricao, sizeof(p->descricao));
            break;
        case 2:
            p->estoque = ler_int("Novo estoque: ");
            break;
        case 3:
            p->estoqueMinimo = ler_int("Novo estoque minimo: ");
            break;
        case 4:
            p->precoCusto = ler_float("Novo preco de custo: ");
            break;
        case 5:
            p->precoVenda = ler_float("Novo preco de venda: ");
            break;
        case 6:
            p->ativo = !p->ativo;
            printf("Produto ID %d agora esta %s.\n", id, p->ativo ? "ativo" : "inativo");
            break;
        default:
            printf("Opcao invalida.\n");
            return 0;
    }

    printf("Produto ID %d atualizado com sucesso.\n", id);
    return 1;
}

/* ── Liberar Lista de Produtos ────────────────────────── */
void ProdutoListaLiberar(ListaProduto *lista) {
    ListaProduto *atual = lista;
    while (atual) {
        ListaProduto *prox = atual->proximo;
        free(atual);
        atual = prox;
    }
}

/* ── Arquivos .TXT/.BIN ────────────────────────── */
int ProdutoSalvarTxt(ListaProduto *lista) {
    FILE *fp = fopen(ARQUIVO_TXT, "w");
    if (!fp) {
        printf("Erro ao abrir %s para escrita.\n", ARQUIVO_TXT);
        return 0;
    }

    ListaProduto *atual = lista;
    while (atual) {
        TipoProduto *p = &atual->produto;
        fprintf(fp, "%d|%s|%d|%d|%.2f|%.2f|%d\n",
                p->id, p->descricao, p->estoque, p->estoqueMinimo,
                p->precoCusto, p->precoVenda, p->ativo);
        atual = atual->proximo;
    }

    fclose(fp);
    return 1;
}

int ProdutoLerTxt(ListaProduto **lista) {
    FILE *fp = fopen(ARQUIVO_TXT, "r");
    if (!fp) return 0; /* arquivo ainda nao existe */

    TipoProduto p;
    char linha[256];

    while (fgets(linha, sizeof(linha), fp)) {
        if (sscanf(linha, "%d|%99[^|]|%d|%d|%f|%f|%d",
                   &p.id, p.descricao, &p.estoque, &p.estoqueMinimo,
                   &p.precoCusto, &p.precoVenda, &p.ativo) == 7) {

            ListaProduto *novo = (ListaProduto *)malloc(sizeof(ListaProduto));
            if (!novo) { fclose(fp); return 0; }
            novo->produto = p;
            novo->proximo = NULL;

            if (!*lista) {
                *lista = novo;
            } else {
                ListaProduto *atual = *lista;
                while (atual->proximo) atual = atual->proximo;
                atual->proximo = novo;
            }
        }
    }

    fclose(fp);
    return 1;
}

int ProdutoSalvarBin(ListaProduto *lista) {
    FILE *fp = fopen(ARQUIVO_BIN, "wb");
    if (!fp) {
        printf("Erro ao abrir %s para escrita.\n", ARQUIVO_BIN);
        return 0;
    }

    ListaProduto *atual = lista;
    while (atual) {
        fwrite(&atual->produto, sizeof(TipoProduto), 1, fp);
        atual = atual->proximo;
    }

    fclose(fp);
    return 1;
}

int ProdutoLerBin(ListaProduto **lista) {
    FILE *fp = fopen(ARQUIVO_BIN, "rb");
    if (!fp) return 0; /* arquivo ainda nao existe */

    TipoProduto p;
    while (fread(&p, sizeof(TipoProduto), 1, fp) == 1) {
        ListaProduto *novo = (ListaProduto *)malloc(sizeof(ListaProduto));
        if (!novo) { fclose(fp); return 0; }
        novo->produto = p;
        novo->proximo = NULL;

        if (!*lista) {
            *lista = novo;
        } else {
            ListaProduto *atual = *lista;
            while (atual->proximo) atual = atual->proximo;
            atual->proximo = novo;
        }
    }

    fclose(fp);
    return 1;
}