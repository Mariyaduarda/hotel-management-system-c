#include "../common.h"
#include "acomodacao.h"

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
    ListaAcomodacao *novo = malloc(sizeof(ListaAcomodacao));
    if (!novo) return 0;
    novo->acomodacao       = acom;
    novo->acomodacao.ativo = 1;
    novo->proximo          = NULL;
    if (*lista == NULL) {
        novo->acomodacao.id = 1;
        *lista = novo;
    } else {
        ListaAcomodacao *atual = *lista;
        while (atual->proximo) atual = atual->proximo;
        novo->acomodacao.id = atual->acomodacao.id + 1;
        atual->proximo = novo;
    }
    return 1;
}

TipoAcomodacao *AcomodacaoBuscar(ListaAcomodacao **lista, int id) {
    ListaAcomodacao *atual = *lista;
    while (atual) {
        if (atual->acomodacao.id == id && atual->acomodacao.ativo)
            return &atual->acomodacao;
        atual = atual->proximo;
    }
    return NULL;
}

void AcomodacaoListar(ListaAcomodacao **lista, int id,
                       ListaCategoria **listaCat) {
    TipoAcomodacao *a = AcomodacaoBuscar(lista, id);
    if (!a) { printf("Acomodação não encontrada.\n"); return; }

    printf("ID          : %d\n", a->id);
    printf("Descrição   : %s\n", a->descricao);
    printf("Facilidades : %s\n", a->facilidades);

    TipoCategoria *cat = CategoriaBuscar(listaCat, a->idCategoria);
    if (cat) {
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
    if (!a) return 0;
    a->ativo = 0;
    return 1;
}

int AcomodacaoAtualizar(ListaAcomodacao **lista, int id, int op) {
    TipoAcomodacao *a = AcomodacaoBuscar(lista, id);
    if (!a) { printf("Acomodação não encontrada.\n"); return 0; }
    switch (op) {
    case 1: printf("Nova descrição: ");   lerString(a->descricao,   sizeof(a->descricao));   break;
    case 2: printf("Facilidades: ");      lerString(a->facilidades, sizeof(a->facilidades)); break;
    case 3: printf("ID categoria: ");     scanf("%d", &a->idCategoria); limparBuffer();       break;
    default: printf("Opção inválida.\n"); return 0;
    }
    return 1;
}

void AcomodacaoListaLiberar(ListaAcomodacao *lista) {
    ListaAcomodacao *temp;
    while (lista) { temp = lista; lista = lista->proximo; free(temp); }
}

int AcomodacaoSalvarTxt(ListaAcomodacao *lista) {
    FILE *f = fopen("acomodacao.txt", "w");
    if (!f) return 0;
    for (ListaAcomodacao *a = lista; a; a = a->proximo)
        fprintf(f, "%d;%s;%s;%d;%d\n",
                a->acomodacao.id, a->acomodacao.descricao,
                a->acomodacao.facilidades, a->acomodacao.idCategoria,
                a->acomodacao.ativo);
    fclose(f); return 1;
}

int AcomodacaoSalvarBin(ListaAcomodacao *lista) {
    FILE *f = fopen("acomodacao.bin", "wb");
    if (!f) return 0;
    for (ListaAcomodacao *a = lista; a; a = a->proximo)
        fwrite(&a->acomodacao, sizeof(TipoAcomodacao), 1, f);
    fclose(f); return 1;
}

int AcomodacaoLerTxt(ListaAcomodacao **lista) {
    FILE *f = fopen("acomodacao.txt", "r");
    if (!f) return 0;
    char linha[400];
    while (fgets(linha, sizeof(linha), f)) {
        TipoAcomodacao a = {0};
        sscanf(linha, "%d;%99[^;];%199[^;];%d;%d",
               &a.id, a.descricao, a.facilidades, &a.idCategoria, &a.ativo);
        AcomodacaoCriar(lista, a);
    }
    fclose(f); return 1;
}

int AcomodacaoLerBin(ListaAcomodacao **lista) {
    FILE *f = fopen("acomodacao.bin", "rb");
    if (!f) return 0;
    TipoAcomodacao a;
    while (fread(&a, sizeof(TipoAcomodacao), 1, f))
        AcomodacaoCriar(lista, a);
    fclose(f); return 1;
}