/* model/acomodacao.c
   Gerencia Categorias e Acomodações do hotel */

#include "../common.h"
#include "acomodacao.h"

/* ════════════════════════════════════════════════════════════
   CATEGORIA
   ════════════════════════════════════════════════════════════ */

void CategoriaInit(TipoAcomodacao *cat) {
    cat->id          = 0;
    cat->valorDiaria = 0.0f;
    cat->maxAdultos  = 0;
    cat->maxCriancas = 0;
    cat->ativo       = 0;
    strcpy(cat->descricao, "-");
}

int CategoriaCriar(ListaCategoria **lista, TipoAcomodacao cat) {
    ListaCategoria *novo = (ListaCategoria *)malloc(sizeof(ListaCategoria));
    if (novo == NULL) return 0;

    novo->categoria      = cat;
    novo->categoria.ativo = 1;
    novo->proximo        = NULL;

    if (*lista == NULL) {
        novo->categoria.id = 1;
        *lista = novo;
    } else {
        ListaCategoria *atual = *lista;
        while (atual->proximo != NULL) atual = atual->proximo;
        novo->categoria.id = atual->categoria.id + 1;
        atual->proximo = novo;
    }
    return 1;
}

TipoAcomodacao *CategoriaBuscar(ListaCategoria **lista, int id) {
    ListaCategoria *atual = *lista;
    while (atual != NULL) {
        if (atual->categoria.id == id && atual->categoria.ativo)
            return &atual->categoria;
        atual = atual->proximo;
    }
    return NULL;
}

void CategoriaListar(ListaCategoria **lista, int id) {
    TipoAcomodacao *c = CategoriaBuscar(lista, id);
    if (c == NULL) { printf("Categoria não encontrada.\n"); return; }

    printf("ID          : %d\n",   c->id);
    printf("Descrição   : %s\n",   c->descricao);
    printf("Diária      : R$ %.2f\n", c->valorDiaria);
    printf("Max adultos : %d\n",   c->maxAdultos);
    printf("Max crianças: %d\n",   c->maxCriancas);
}

int CategoriaExcluir(ListaCategoria **lista, int id) {
    TipoAcomodacao *c = CategoriaBuscar(lista, id);
    if (c == NULL) return 0;
    c->ativo = 0;
    return 1;
}

int CategoriaAtualizar(ListaCategoria **lista, int id, int op) {
    TipoAcomodacao *c = CategoriaBuscar(lista, id);
    if (c == NULL) { printf("Categoria não encontrada.\n"); return 0; }

    switch (op) {
    case 1:
        printf("Nova descrição: ");
        lerString(c->descricao, sizeof(c->descricao));
        break;
    case 2:
        printf("Novo valor de diária: ");
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
    while (lista != NULL) {
        temp  = lista;
        lista = lista->proximo;
        free(temp);
    }
}

/* ── Persistência Categoria ─────────────────────────────── */

int CategoriaSalvarTxt(ListaCategoria *lista) {
    FILE *f = fopen("categoria.txt", "w");
    if (f == NULL) return 0;
    ListaCategoria *atual = lista;
    while (atual != NULL) {
        TipoAcomodacao *c = &atual->categoria;
        fprintf(f, "%d;%s;%.2f;%d;%d;%d\n",
                c->id, c->descricao, c->valorDiaria,
                c->maxAdultos, c->maxCriancas, c->ativo);
        atual = atual->proximo;
    }
    fclose(f);
    return 1;
}

int CategoriaSalvarBin(ListaCategoria *lista) {
    FILE *f = fopen("categoria.bin", "wb");
    if (f == NULL) return 0;
    ListaCategoria *atual = lista;
    while (atual != NULL) {
        fwrite(&atual->categoria, sizeof(TipoAcomodacao), 1, f);
        atual = atual->proximo;
    }
    fclose(f);
    return 1;
}

int CategoriaLerTxt(ListaCategoria **lista) {
    FILE *f = fopen("categoria.txt", "r");
    if (f == NULL) return 0;
    char linha[200];
    while (fgets(linha, sizeof(linha), f)) {
        TipoAcomodacao c;
        sscanf(linha, "%d;%[^;];%f;%d;%d;%d",
               &c.id, c.descricao, &c.valorDiaria,
               &c.maxAdultos, &c.maxCriancas, &c.ativo);
        CategoriaCriar(lista, c);
    }
    fclose(f);
    return 1;
}

int CategoriaLerBin(ListaCategoria **lista) {
    FILE *f = fopen("categoria.bin", "rb");
    if (f == NULL) return 0;
    TipoAcomodacao c;
    while (fread(&c, sizeof(TipoAcomodacao), 1, f))
        CategoriaCriar(lista, c);
    fclose(f);
    return 1;
}

/* ════════════════════════════════════════════════════════════
   ACOMODAÇÃO
   ════════════════════════════════════════════════════════════ */

void AcomodacaoInit(TipoAcomodacao *acom) {
    acom->id          = 0;
    acom->idCategoria = 0;
    acom->ativo       = 0;
    strcpy(acom->descricao,   "-");
    strcpy(acom->facilidades, "-");
}

int AcomodacaoCriar(ListaAcomodacao **lista, TipoAcomodacao acom) {
    ListaAcomodacao *novo = (ListaAcomodacao *)malloc(sizeof(ListaAcomodacao));
    if (novo == NULL) return 0;

    novo->acomodacao      = acom;
    novo->acomodacao.ativo = 1;
    novo->proximo         = NULL;

    if (*lista == NULL) {
        novo->acomodacao.id = 1;
        *lista = novo;
    } else {
        ListaAcomodacao *atual = *lista;
        while (atual->proximo != NULL) atual = atual->proximo;
        novo->acomodacao.id = atual->acomodacao.id + 1;
        atual->proximo = novo;
    }
    return 1;
}

TipoAcomodacao *AcomodacaoBuscar(ListaAcomodacao **lista, int id) {
    ListaAcomodacao *atual = *lista;
    while (atual != NULL) {
        if (atual->acomodacao.id == id && atual->acomodacao.ativo)
            return &atual->acomodacao;
        atual = atual->proximo;
    }
    return NULL;
}

void AcomodacaoListar(ListaAcomodacao **lista, int id,
                       ListaCategoria **listaCat) {
    TipoAcomodacao *a = AcomodacaoBuscar(lista, id);
    if (a == NULL) { printf("Acomodação não encontrada.\n"); return; }

    printf("ID          : %d\n",  a->id);
    printf("Descrição   : %s\n",  a->descricao);
    printf("Facilidades : %s\n",  a->facilidades);

    // Exibe dados da categoria junto
    TipoAcomodacao *cat = CategoriaBuscar(listaCat, a->idCategoria);
    if (cat != NULL) {
        printf("Categoria   : %s\n",      cat->descricao);
        printf("Diária      : R$ %.2f\n", cat->valorDiaria);
        printf("Capacidade  : %d adultos, %d crianças\n",
               cat->maxAdultos, cat->maxCriancas);
    } else {
        printf("Categoria   : (não encontrada, id=%d)\n", a->idCategoria);
    }
}

int AcomodacaoExcluir(ListaAcomodacao **lista, int id) {
    TipoAcomodacao *a = AcomodacaoBuscar(lista, id);
    if (a == NULL) return 0;
    a->ativo = 0;
    return 1;
}

int AcomodacaoAtualizar(ListaAcomodacao **lista, int id, int op) {
    TipoAcomodacao *a = AcomodacaoBuscar(lista, id);
    if (a == NULL) { printf("Acomodação não encontrada.\n"); return 0; }

    switch (op) {
    case 1:
        printf("Nova descrição: ");
        lerString(a->descricao, sizeof(a->descricao));
        break;
    case 2:
        printf("Novas facilidades: ");
        lerString(a->facilidades, sizeof(a->facilidades));
        break;
    case 3:
        printf("Novo ID de categoria: ");
        scanf("%d", &a->idCategoria); limparBuffer();
        break;
    default:
        printf("Opção inválida.\n");
        return 0;
    }
    return 1;
}

void AcomodacaoListaLiberar(ListaAcomodacao *lista) {
    ListaAcomodacao *temp;
    while (lista != NULL) {
        temp  = lista;
        lista = lista->proximo;
        free(temp);
    }
}

/* ── Persistência Acomodação ────────────────────────────── */

int AcomodacaoSalvarTxt(ListaAcomodacao *lista) {
    FILE *f = fopen("acomodacao.txt", "w");
    if (f == NULL) return 0;
    ListaAcomodacao *atual = lista;
    while (atual != NULL) {
        TipoAcomodacao *a = &atual->acomodacao;
        fprintf(f, "%d;%s;%s;%d;%d\n",
                a->id, a->descricao, a->facilidades,
                a->idCategoria, a->ativo);
        atual = atual->proximo;
    }
    fclose(f);
    return 1;
}

int AcomodacaoSalvarBin(ListaAcomodacao *lista) {
    FILE *f = fopen("acomodacao.bin", "wb");
    if (f == NULL) return 0;
    ListaAcomodacao *atual = lista;
    while (atual != NULL) {
        fwrite(&atual->acomodacao, sizeof(TipoAcomodacao), 1, f);
        atual = atual->proximo;
    }
    fclose(f);
    return 1;
}

int AcomodacaoLerTxt(ListaAcomodacao **lista) {
    FILE *f = fopen("acomodacao.txt", "r");
    if (f == NULL) return 0;
    char linha[400];
    while (fgets(linha, sizeof(linha), f)) {
        TipoAcomodacao a;
        sscanf(linha, "%d;%[^;];%[^;];%d;%d",
               &a.id, a.descricao, a.facilidades,
               &a.idCategoria, &a.ativo);
        AcomodacaoCriar(lista, a);
    }
    fclose(f);
    return 1;
}

int AcomodacaoLerBin(ListaAcomodacao **lista) {
    FILE *f = fopen("acomodacao.bin", "rb");
    if (f == NULL) return 0;
    TipoAcomodacao a;
    while (fread(&a, sizeof(TipoAcomodacao), 1, f))
        AcomodacaoCriar(lista, a);
    fclose(f);
    return 1;
}