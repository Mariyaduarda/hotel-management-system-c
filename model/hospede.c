/* ── Responsavel pelo Model do Hospede ────────────────────────────── */
#include "../common.h"
#include "hospede.h"

/* ── Inicializa campos ─────────────────────────────────────────────── */
void HospedeInit(TipoHospede *h) {
    h->id = 0;
    strcpy(h->nome,           "-");
    strcpy(h->cpf,            "-");
    strcpy(h->email,          "-");
    strcpy(h->telefone,       "-");
    strcpy(h->sexo,           "-");
    strcpy(h->dataNascimento, "00/00/0000");
    strcpy(h->estadoCivil,    "-");
    /* endereco (struct diferente) */
    strcpy(h->endereco.rua,        "-");
    strcpy(h->endereco.numero,     "-");
    strcpy(h->endereco.complemento,"-");
    strcpy(h->endereco.bairro,     "-");
    strcpy(h->endereco.cidade,     "-");
    strcpy(h->endereco.estado,     "-");
    strcpy(h->endereco.cep,        "-");
    h->ativo = 0;
}

/* ── Inicializa Lista de Hospedes ────────────────────────────────── */
void HospedeListaInit(ListaHospede *lista) {
    lista->proximo = NULL;
    HospedeInit(&lista->hospede);
}

/* ── Criar Hospede ─────────────────────────────────────────────── */
int HospedeCriar(ListaHospede **lista, TipoHospede hospede) {
    ListaHospede *novo = (ListaHospede *)malloc(sizeof(ListaHospede));
    if (novo == NULL) return 0;

    novo->hospede        = hospede;
    novo->hospede.ativo  = 1;
    novo->proximo        = NULL;

    if (*lista == NULL) {
        novo->hospede.id = 1;
        *lista = novo;
    } else {
        ListaHospede *atual = *lista;
        while (atual->proximo != NULL) atual = atual->proximo;
        novo->hospede.id = atual->hospede.id + 1;
        atual->proximo = novo;
    }
    return 1;
}

/* ── Listar Hospedes ─────────────────────────────────────────────── */
void HospedeListar(ListaHospede **lista, int id) {
    ListaHospede *atual = *lista;
    while (atual != NULL) {
        if (atual->hospede.id == id) {
            TipoHospede *h = &atual->hospede;
            printf("ID            : %d\n",  h->id);
            printf("Nome          : %s\n",  h->nome);
            printf("CPF           : %s\n",  h->cpf);
            printf("Email         : %s\n",  h->email);
            printf("Telefone      : %s\n",  h->telefone);
            printf("Sexo          : %s\n",  h->sexo);
            printf("Nascimento    : %s\n",  h->dataNascimento);
            printf("Estado Civil  : %s\n",  h->estadoCivil);
            printf("Rua           : %s\n",  h->endereco.rua);
            printf("Numero        : %s\n",  h->endereco.numero);
            printf("Complemento   : %s\n",  h->endereco.complemento);
            printf("Bairro        : %s\n",  h->endereco.bairro);
            printf("Cidade        : %s\n",  h->endereco.cidade);
            printf("Estado        : %s\n",  h->endereco.estado);
            printf("CEP           : %s\n",  h->endereco.cep);
            printf("Ativo         : %s\n",  h->ativo ? "Sim" : "Nao");
            return;
        }
        atual = atual->proximo;
    }
    printf("Hospede nao encontrado.\n");
}
/* ── Buscar Hospede ──────────────────────────────────────────────── */
TipoHospede *HospedeBuscar(ListaHospede **lista, int id) {
    ListaHospede *atual = *lista;
    while (atual != NULL) {
        if (atual->hospede.id == id) return &atual->hospede;
        atual = atual->proximo;
    }
    return NULL;
}

/* ── Excluir Hospede ─────────────────────────────────────────────── */
// Desativa o hospede, mantem a integridade dos dados
int HospedeExcluir(ListaHospede **lista, int id) {
    ListaHospede *atual = *lista;
    while (atual != NULL) {
        if (atual->hospede.id == id) {
            atual->hospede.ativo = 0;
            return 1;
        }
        atual = atual->proximo;
    }
    return 0;
}

/* ── Atualiza o Hospede ─────────────────────────────────────────────── */
int HospedeAtualizar(ListaHospede **lista, int id, int op) {
    TipoHospede *h = HospedeBuscar(lista, id);
    if (h == NULL) { printf("Hospede nao encontrado.\n"); return 0; }

    switch (op) {
    case 1: /* todos */
        ler_string("Nome: ",         h->nome,                 sizeof(h->nome)                 );
        ler_string("CPF: ",          h->cpf,                  sizeof(h->cpf)                  );
        ler_string("Email: ",        h->email,                sizeof(h->email)                );
        ler_string("Telefone: ",     h->telefone,             sizeof(h->telefone)             );
        ler_string("Sexo: ",         h->sexo,                 sizeof(h->sexo)                 );
        ler_string("Nascimento: ",   h->dataNascimento,       sizeof(h->dataNascimento)       );
        ler_string("Estado Civil: ", h->estadoCivil,          sizeof(h->estadoCivil)          );
        ler_string("Rua: ",          h->endereco.rua,         sizeof(h->endereco.rua)         );
        ler_string("Numero: ",       h->endereco.numero,      sizeof(h->endereco.numero)      );
        ler_string("Complemento: ",  h->endereco.complemento, sizeof(h->endereco.complemento) );
        ler_string("Bairro: ",       h->endereco.bairro,      sizeof(h->endereco.bairro)      );
        ler_string("Cidade: ",       h->endereco.cidade,      sizeof(h->endereco.cidade)      );
        ler_string("Estado (UF): ",  h->endereco.estado,      sizeof(h->endereco.estado)      );
        ler_string("CEP: ",          h->endereco.cep,         sizeof(h->endereco.cep)         );
        break;
    /* um de cada vez */
    case 2:  ler_string("Nome: ",         h->nome,                 sizeof(h->nome)                 ); break;
    case 3:  ler_string("CPF: ",          h->cpf,                  sizeof(h->cpf)                  ); break;
    case 4:  ler_string("Email: ",        h->email,                sizeof(h->email)                ); break;
    case 5:  ler_string("Telefone: ",     h->telefone,             sizeof(h->telefone)             ); break;
    case 6:  ler_string("Sexo: ",         h->sexo,                 sizeof(h->sexo)                 ); break;
    case 7:  ler_string("Nascimento: ",   h->dataNascimento,       sizeof(h->dataNascimento)       ); break;
    case 8:  ler_string("Estado Civil: ", h->estadoCivil,          sizeof(h->estadoCivil)          ); break;
    case 9:  ler_string("Rua: ",          h->endereco.rua,         sizeof(h->endereco.rua)         ); break;
    case 10: ler_string("Numero: ",       h->endereco.numero,      sizeof(h->endereco.numero)      ); break;
    case 11: ler_string("Complemento: ",  h->endereco.complemento, sizeof(h->endereco.complemento) ); break;
    case 12: ler_string("Bairro: ",       h->endereco.bairro,      sizeof(h->endereco.bairro)      ); break;
    case 13: ler_string("Cidade: ",       h->endereco.cidade,      sizeof(h->endereco.cidade)      ); break;
    case 14: ler_string("Estado (UF): ",  h->endereco.estado,      sizeof(h->endereco.estado)      ); break;
    case 15: ler_string("CEP: ",          h->endereco.cep,         sizeof(h->endereco.cep)         ); break;
    default: printf("Opcao invalida.\n"); return 0;
    }
    return 1;
}

/* ── Libera Memoria da Lista ─────────────────────────────────────────────── */
void HospedeListaLiberar(ListaHospede *lista) {
    ListaHospede *temp;
    while (lista != NULL) {
        temp  = lista;
        lista = lista->proximo;
        free(temp);
    }
}

/* ── Arquivos .TXT/.BIN───────────────────────────────────────────── */
int HospedeSalvarTxt(ListaHospede *lista) {
    FILE *f = fopen("dados/hospede.txt", "w");
    if (!f) return 0;
    ListaHospede *atual = lista;
    while (atual) {
        TipoHospede *h = &atual->hospede;
        fprintf(f, "%d;%s;%s;%s;%s;%s;%s;%s;%s;%s;%s;%s;%s;%s;%s;%d\n",
                h->id, h->nome, h->cpf, h->email, h->telefone,
                h->sexo, h->dataNascimento, h->estadoCivil,
                h->endereco.rua, h->endereco.numero, h->endereco.complemento,
                h->endereco.bairro, h->endereco.cidade, h->endereco.estado,
                h->endereco.cep, h->ativo);
        atual = atual->proximo;
    }
    fclose(f);
    return 1;
}

int HospedeSalvarBin(ListaHospede *lista) {
    FILE *f = fopen("dados/hospede.bin", "wb");
    if (!f) return 0;
    ListaHospede *atual = lista;
    while (atual) {
        fwrite(&atual->hospede, sizeof(TipoHospede), 1, f);
        atual = atual->proximo;
    }
    fclose(f);
    return 1;
}

int HospedeLerTxt(ListaHospede **lista) {
    FILE *f = fopen("dados/hospede.txt", "r");
    if (!f) return 0;
    char linha[500];
    while (fgets(linha, sizeof(linha), f)) {
        TipoHospede h;
        sscanf(linha,
               "%d;%99[^;];%19[^;];%49[^;];%19[^;];%49[^;];%10[^;];%49[^;];"
               "%99[^;];%9[^;];%49[^;];%49[^;];%49[^;];%49[^;];%19[^;];%d",
               &h.id, h.nome, h.cpf, h.email, h.telefone,
               h.sexo, h.dataNascimento, h.estadoCivil,
               h.endereco.rua, h.endereco.numero, h.endereco.complemento,
               h.endereco.bairro, h.endereco.cidade, h.endereco.estado,
               h.endereco.cep, &h.ativo);
        HospedeCriar(lista, h);
    }
    fclose(f);
    return 1;
}

int HospedeLerBin(ListaHospede **lista) {
    FILE *f = fopen("dados/hospede.bin", "rb");
    if (!f) return 0;
    TipoHospede h;
    while (fread(&h, sizeof(TipoHospede), 1, f))
        HospedeCriar(lista, h);
    fclose(f);
    return 1;
}