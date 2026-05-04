#include "categoria_acomodacao.h"

void CategoriasInit(TipoCategoria *cat) {
    cat->id          = 0;
    cat->valorDiaria = 0.0f;
    cat->maxAdultos  = 0;
    cat->maxCriancas = 0;
    cat->ativo       = 0;
    strcpy(cat->descricao, "-");
}

void CategoriaListaInit(ListaCategoria *lista) {
    (void)lista;
}

int CategoriaCriar(ListaCategoria **lista, TipoCategoria cat) {
    ListaCategoria *novo = malloc(sizeof(ListaCategoria));
    if (!novo) return 0;

    novo->categoria       = cat;
    novo->categoria.ativo = 1;
    novo->proximo         = NULL;

    if (*lista == NULL) {
        novo->categoria.id = 1;
        *lista = novo;
    } else {
        ListaCategoria *atual = *lista;
        while (atual->proximo) atual = atual->proximo;
        novo->categoria.id = atual->categoria.id + 1;
        atual->proximo = novo;
    }
    return 1;
}

TipoCategoria *CategoriaBuscar(ListaCategoria **lista, int id) {
    ListaCategoria *atual = *lista;
    while (atual) {
        if (atual->categoria.id == id && atual->categoria.ativo)
            return &atual->categoria;
        atual = atual->proximo;
    }
    return NULL;
}

void CategoriaListar(ListaCategoria **lista, int id) {
    TipoCategoria *c = CategoriaBuscar(lista, id);
    if (!c) { printf("Categoria não encontrada.\n"); return; }

    printf("ID          : %d\n",      c->id);
    printf("Descrição   : %s\n",      c->descricao);
    printf("Diária      : R$ %.2f\n", c->valorDiaria);
    printf("Max adultos : %d\n",      c->maxAdultos);
    printf("Max crianças: %d\n",      c->maxCriancas);
}

int CategoriaExcluir(ListaCategoria **lista, int id) {
    TipoCategoria *c = CategoriaBuscar(lista, id);
    if (!c) return 0;
    c->ativo = 0;
    return 1;
}

int CategoriaAtualizar(ListaCategoria **lista, int id, int op) {
    TipoCategoria *c = CategoriaBuscar(lista, id);
    if (!c) { printf("Categoria não encontrada.\n"); return 0; }

    switch (op) {
    case 1:
        printf("Nova descrição: ");
        lerString(c->descricao, sizeof(c->descricao));
        break;
    case 2:
        printf("Novo valor de diária: R$ ");
        scanf("%f", &c->valorDiaria); limparBuffer();
        break;
    case 3:
        printf("Max adultos: ");
        scanf("%d", &c->maxAdultos); limparBuffer();
        break;
    case 4:
        printf("Max crianças: ");
        scanf("%d", &c->maxCriancas); limparBuffer();
        break;
    default:
        printf("Opção inválida.\n");
        return 0;
    }
    return 1;
}

void CategoriaListaLiberar(ListaCategoria *lista) {
    ListaCategoria *temp;
    while (lista) {
        temp  = lista;
        lista = lista->proximo;
        free(temp);
    }
}

int CategoriaSalvarTxt(ListaCategoria *lista) {
    FILE *f = fopen("dados/categoria.txt", "w");
    if (!f) return 0;
    for (ListaCategoria *a = lista; a; a = a->proximo) {
        TipoCategoria *c = &a->categoria;
        fprintf(f, "%d;%s;%.2f;%d;%d;%d\n",
                c->id, c->descricao, c->valorDiaria,
                c->maxAdultos, c->maxCriancas, c->ativo);
    }
    fclose(f);
    return 1;
}

int CategoriaSalvarBin(ListaCategoria *lista) {
    FILE *f = fopen("dados/categoria.bin", "wb");
    if (!f) return 0;
    for (ListaCategoria *a = lista; a; a = a->proximo)
        fwrite(&a->categoria, sizeof(TipoCategoria), 1, f);
    fclose(f);
    return 1;
}

int CategoriaLerTxt(ListaCategoria **lista) {
    FILE *f = fopen("dados/categoria.txt", "r");
    if (!f) return 0;
    char linha[256];
    while (fgets(linha, sizeof(linha), f)) {
        TipoCategoria c = {0};
        sscanf(linha, "%d;%99[^;];%f;%d;%d;%d",
               &c.id, c.descricao, &c.valorDiaria,
               &c.maxAdultos, &c.maxCriancas, &c.ativo);
        CategoriaCriar(lista, c);
    }
    fclose(f);
    return 1;
}

int CategoriaLerBin(ListaCategoria **lista) {
    FILE *f = fopen("dados/categoria.bin", "rb");
    if (!f) return 0;
    TipoCategoria c;
    while (fread(&c, sizeof(TipoCategoria), 1, f))
        CategoriaCriar(lista, c);
    fclose(f);
    return 1;
}