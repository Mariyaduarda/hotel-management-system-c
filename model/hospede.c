/* Este cadastro contém os dados dos clientes do hote*/
#include "../common.h"
#include "hospede.h"

void HospedeInit(TipoHospede *hospede){
    hospede->id = 0;
    
    strcpy(hospede->nome, "-");
    strcpy(hospede->cpf, "-");
    strcpy(hospede->email, "-");
    strcpy(hospede->telefone, "-");
    strcpy(hospede->sexo, "-");
    strcpy(hospede->dataNascimento, "00/00/0000");
    strcpy(hospede->estadoCivil, "-");

    hospede->ativo = 0; // Evita exclusao fisica
}

void HospedeListaInit(ListaHospede *lista){
    lista->proximo = NULL;
    HospedeInit(&lista->hospede);
}

/** *  = sem necessiddade de alterar o endereco de memoria
    ** = com necessidade de alterar o endereco de memoria **/
void HospedeCriar(ListaHospede **lista, TipoHospede hospede){
    ListaHospede *novo = (ListaHospede*)malloc(sizeof(ListaHospede));

    // aloca o espaço para um novo endereco
    if (novo == NULL) return 0;

    novo->hospede = hospede;
    novo->hospede.ativo = 0;
    novo->proximo = NULL;

    if (*lista == NULL){
        novo->hospede.id = 1;
        *lista = novo;
    } else{
        ListaHospede *atual = *lista;
        while(atual->proximo !=  NULL) atual = atual->proximo;
        
        novo->hospede.id = atual->hospede.id + 1;

        atual->proximo = novo;
    }
    return 1;
}

void HospedeListar(ListaHospede **lista, int id){
    ListaHospede *atual = *lista; // ponteiro para inciio da lista

    while(atual != NULL){
        if(atual->hospede.id == id){
            printf("ID: %d\n", atual->hospede.id);
            printf("Nome: %s\n", atual->hospede.nome);
            printf("CPF: %s\n", atual->hospede.cpf);
            printf("Email: %s\n", atual->hospede.email);
            printf("Telefone: %s\n", atual->hospede.telefone);
            printf("Sexo: %s\n", atual->hospede.sexo);
            printf("Data de Nascimento: %s\n", atual->hospede.dataNascimento);
            printf("Estado Civil: %s\n", atual->hospede.estadoCivil);
            return; // sucesso
        }
        atual = atual->proximo;
    }
    printf("Hospede nao encontrado.\n");
}

TipoHospede* HospedeBuscar(ListaHospede **lista, int id){
    ListaHospede *atual = *lista; // ponteiro para o inicio da lista

    while(atual != NULL){
        if(atual->hospede.id == id) return &atual->hospede; // sucesso
        atual = atual->proximo;
    }

    return 0; // falha
}

int HospedeExcluir(ListaHospede **lista, int id){
    ListaHospede *atual = *lista; // ponteiro para o inicio da lista
    while(atual != NULL){
        if(atual->hospede.id == id){
            atual->hospede.ativo = 0; // exclusao logica apenas, para evitar perda de dados
            return 1; // sucesso
        }
        atual = atual->proximo;
    }
    return 0; // falha
}

int HospedeAtualizar(ListaHospede **lista, int id, int op){
        TipoHospede *h = HospedeBuscar(lista, id); // ponteiro para o hospede encontrado
    
    // se nao encontrou encerra a funcao
    if(h == NULL){
        printf("Hospede nao encontrado.\n");
        return 0; // falha
    }
    // caso tenha-se o endereco h alteramos o campo escolhido
    switch (op){
    case 1:
        printf("Novo nome: "); 
        lerString(h->nome, sizeof(h->nome)); // Lê a nova string, incluindo espaços e remove o caractere de nova linha

        printf("Novo CPF: "); 
        lerString(h->cpf, sizeof(h->cpf)); // Lê a nova string, incluindo espaços e remove o caractere de nova linha

        printf("Novo email: "); 
        lerString(h->email, sizeof(h->email)); // Lê a nova string, incluindo espaços e remove o caractere de nova linha

        printf("Novo telefone: "); 
        lerString(h->telefone, sizeof(h->telefone)); // Lê a nova string, incluindo espaços e remove o caractere de nova linha

        printf("Novo sexo: ");
        lerString(h->sexo, sizeof(h->sexo)); // Lê a nova string, incluindo espaços e remove o caractere de nova linha

        printf("Nova data de nascimento: ");
        lerString(h->dataNascimento, sizeof(h->dataNascimento)); // Lê a nova string, incluindo espaços e remove o caractere de nova linha
        
        printf("Novo estado civil: ");
        lerString(h->estadoCivil, sizeof(h->estadoCivil)); // Lê a nova string, incluindo espaços e remove o caractere de nova linha
        
        break;
    case 2:
        printf("Novo nome: "); 
        lerString(h->nome, sizeof(h->nome)); // Lê a nova string, incluindo espaços e remove o caractere de nova linha
        break;
    case 3:
        printf("Novo CPF: "); 
        lerString(h->cpf, sizeof(h->cpf)); // Lê a nova string, incluindo espaços e remove o caractere de nova linha
        break;
    case 4:
        printf("Novo email: "); 
        lerString(h->email, sizeof(h->email)); // Lê a nova string, incluindo espaços e remove o caractere de nova linha
        break;
    case 5:
        printf("Novo telefone: "); 
        lerString(h->telefone, sizeof(h->telefone)); // Lê a nova string, incluindo espaços e remove o caractere de nova linha
        break;
    case 6:
        printf("Novo sexo: "); 
        lerString(h->sexo, sizeof(h->sexo)); // Lê a nova string, incluindo espaços e remove o caractere de nova linha
        break;
    case 7:
        printf("Nova data de nascimento: "); 
        lerString(h->dataNascimento, sizeof(h->dataNascimento)); // Lê a nova string, incluindo espaços e remove o caractere de nova linha
        break;
    case 8:
        printf("Novo estado civil: "); 
        lerString(h->estadoCivil, sizeof(h->estadoCivil)); // Lê a nova string, incluindo espaços e remove o caractere de nova linha
        break;
    default:
        printf("Opcao invalida.\n");
        break;
    }
    return 1; // sucesso
}

void HospedeListaLiberar(ListaHospede *lista){
    // Libera espaco entregue a lista
    ListaHospede* temp;

    // Libera espaco alocado, temp = var auxiliar para liberar o espaco alocado
    while(lista != NULL){
        temp = lista;

        lista = lista->proximo; // tentaria mudar o enderenco se fosse **lista ali no parametro
        free(temp);
    }
}

// FUNCOES DE ARQUIVO
// Leitura de arquivo gera espaço na memoria
int HospedeSalvarTxt(ListaHospede *lista){
    FILE *arquivo = fopen("hospede.txt", "w");
    // Confere se tudo ocorreu bem na abertura do arquivo
    if (arquivo == NULL) return 0; // falha

    ListaHospede *atual = lista;
    while(atual != NULL){
        fprintf(arquivo, "%d;%s;%s;%s;%s;%s;%s;%s;%d\n", 
            atual->hospede.id, 
            atual->hospede.nome, 
            atual->hospede.cpf, 
            atual->hospede.email, 
            atual->hospede.telefone, 
            atual->hospede.sexo, 
            atual->hospede.dataNascimento, 
            atual->hospede.estadoCivil, 
            atual->hospede.ativo);

        atual = atual->proximo;
    }
    fclose(arquivo);
    return 1; // sucesso
}
int HospedeSalvarBin(ListaHospede *lista){
    FILE *arquivo = fopen("hospede.bin", "wb");
    if(arquivo == NULL) return 1;
    
    if(lista == NULL) {
        fclose(arquivo); // fecha o arquivo caso a lista esteja vazia
        return 1;
    }
    ListaHospede *atual = lista;

    while(atual != NULL){
        fwrite(&atual->hospede, sizeof(TipoHospede), 1, arquivo);
        // Tem que continuar
        atual = atual->proximo;
    }
    fclose(arquivo);
    return 1; // sucesso
}
int HospedeLerTxt(ListaHospede **lista){
    FILE *arquivo = fopen("hospede.txt", "r");
    if (arquivo == NULL) return 1; // falha

    char linha[300];
    while(fgets(linha, sizeof(linha), arquivo)){
        TipoHospede h;
        sscanf(linha, "%d;%[^;];%[^;];%[^;];%[^;];%[^;];%[^;];%[^;];%d", 
            &h.id, 
            h.nome, 
            h.cpf, 
            h.email, 
            h.telefone, 
            h.sexo, 
            h.dataNascimento, 
            h.estadoCivil, 
            &h.ativo);

        HospedeCriar(lista, h);
    }
    fclose(arquivo);
    return 1;
}

int HospedeLerBin(ListaHospede **lista){
    // ler rb para ler o arquivo binario
    FILE *arquivo = fopen("hospede.bin", "rb");
        if(arquivo == NULL) return 0; // encerra a funcao caso haja falha na abertura do arquivo

        TipoHospede h;

        while(fread(&h, sizeof(TipoHospede), 1, arquivo)){
            HospedeCriar(lista, h);
        }
        fclose(arquivo);
        return 1; // sucesso
}