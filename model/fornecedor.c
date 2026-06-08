/* model/fornecedor.c */
#include "../common.h"
#include "fornecedor.h"
#include <stdlib.h>
#include <string.h>
#include <stdio.h>

void FornecedorInit(TipoFornecedor *f) {
    f->id     = 0;
    f->ativo  = 0;
    strcpy(f->nomeFantasia,      "-");
    strcpy(f->razaoSocial,       "-");
    strcpy(f->inscricaoEstadual, "-");
    strcpy(f->cnpj,              "-");
    strcpy(f->endereco,          "-");
    strcpy(f->telefone,          "-");
    strcpy(f->email,             "-");
}

void FornecedorListaInit(ListaFornecedor *lista) {
    lista->proximo = NULL;
    FornecedorInit(&lista->fornecedor);
}

int FornecedorCriar(ListaFornecedor **lista, TipoFornecedor fornecedor) {
    ListaFornecedor *novo = (ListaFornecedor *)malloc(sizeof(ListaFornecedor));
    if (novo == NULL) return 0;

    novo->fornecedor       = fornecedor;
    novo->fornecedor.ativo = 1;
    novo->proximo          = NULL;

    if (*lista == NULL) {
        novo->fornecedor.id = 1;
        *lista = novo;
    } else {
        ListaFornecedor *atual = *lista;
        while (atual->proximo != NULL) atual = atual->proximo;
        novo->fornecedor.id = atual->fornecedor.id + 1;
        atual->proximo = novo;
    }
    return 1;
}

void FornecedorListar(ListaFornecedor **lista, int id) {
    ListaFornecedor *atual = *lista;
    while (atual != NULL) {
        TipoFornecedor *f = &atual->fornecedor;
        if (f->id == id && f->ativo) {
            printf("ID                : %d\n",  f->id);
            printf("Nome Fantasia     : %s\n",  f->nomeFantasia);
            printf("Razao Social      : %s\n",  f->razaoSocial);
            printf("Inscricao Estadual: %s\n",  f->inscricaoEstadual);
            printf("CNPJ              : %s\n",  f->cnpj);
            printf("Endereco          : %s\n",  f->endereco);
            printf("Telefone          : %s\n",  f->telefone);
            printf("E-mail            : %s\n",  f->email);
            return;
        }
        atual = atual->proximo;
    }
    printf("Fornecedor nao encontrado.\n");
}

TipoFornecedor *FornecedorBuscar(ListaFornecedor **lista, int id) {
    ListaFornecedor *atual = *lista;
    while (atual != NULL) {
        if (atual->fornecedor.id == id && atual->fornecedor.ativo)
            return &atual->fornecedor;
        atual = atual->proximo;
    }
    return NULL;
}

int FornecedorExcluir(ListaFornecedor **lista, int id) {
    TipoFornecedor *f = FornecedorBuscar(lista, id);
    if (f == NULL) return 0;
    f->ativo = 0;
    return 1;
}

int FornecedorAtualizar(ListaFornecedor **lista, int id, int op) {
    TipoFornecedor *f = FornecedorBuscar(lista, id);
    if (f == NULL) { printf("Fornecedor nao encontrado.\n"); return 0; }

    switch (op) {
    case 1: printf("Nome Fantasia     : "); lerString(f->nomeFantasia,      sizeof(f->nomeFantasia));      break;
    case 2: printf("Razao Social      : "); lerString(f->razaoSocial,       sizeof(f->razaoSocial));       break;
    case 3: printf("Inscricao Estadual: "); lerString(f->inscricaoEstadual, sizeof(f->inscricaoEstadual)); break;
    case 4: printf("CNPJ              : "); lerString(f->cnpj,              sizeof(f->cnpj));              break;
    case 5: printf("Endereco          : "); lerString(f->endereco,          sizeof(f->endereco));          break;
    case 6: printf("Telefone          : "); lerString(f->telefone,          sizeof(f->telefone));          break;
    case 7: printf("E-mail            : "); lerString(f->email,             sizeof(f->email));             break;
    default: printf("Opcao invalida.\n"); return 0;
    }
    return 1;
}

void FornecedorListaLiberar(ListaFornecedor *lista) {
    ListaFornecedor *temp;
    while (lista != NULL) {
        temp  = lista;
        lista = lista->proximo;
        free(temp);
    }
}

/* ── Persistencia ───────────────────────────────────────── */

int FornecedorSalvarTxt(ListaFornecedor *lista) {
    FILE *f = fopen("dados/fornecedor.txt", "w");
    if (f == NULL) return 0;
    ListaFornecedor *atual = lista;
    while (atual != NULL) {
        TipoFornecedor *fo = &atual->fornecedor;
        fprintf(f, "%d;%s;%s;%s;%s;%s;%s;%s;%d\n",
                fo->id, fo->nomeFantasia, fo->razaoSocial,
                fo->inscricaoEstadual, fo->cnpj,
                fo->endereco, fo->telefone, fo->email, fo->ativo);
        atual = atual->proximo;
    }
    fclose(f);
    return 1;
}

int FornecedorSalvarBin(ListaFornecedor *lista) {
    FILE *f = fopen("dados/fornecedor.bin", "wb");
    if (f == NULL) return 0;
    ListaFornecedor *atual = lista;
    while (atual != NULL) {
        fwrite(&atual->fornecedor, sizeof(TipoFornecedor), 1, f);
        atual = atual->proximo;
    }
    fclose(f);
    return 1;
}

int FornecedorLerTxt(ListaFornecedor **lista) {
    FILE *f = fopen("dados/fornecedor.txt", "r");
    if (f == NULL) return 0;
    char linha[400];
    while (fgets(linha, sizeof(linha), f)) {
        TipoFornecedor fo;
        sscanf(linha, "%d;%[^;];%[^;];%[^;];%[^;];%[^;];%[^;];%[^;];%d",
               &fo.id, fo.nomeFantasia, fo.razaoSocial,
               fo.inscricaoEstadual, fo.cnpj,
               fo.endereco, fo.telefone, fo.email, &fo.ativo);
        FornecedorCriar(lista, fo);
    }
    fclose(f);
    return 1;
}

int FornecedorLerBin(ListaFornecedor **lista) {
    FILE *f = fopen("dados/fornecedor.bin", "rb");
    if (f == NULL) return 0;
    TipoFornecedor fo;
    while (fread(&fo, sizeof(TipoFornecedor), 1, f))
        FornecedorCriar(lista, fo);
    fclose(f);
    return 1;
}
