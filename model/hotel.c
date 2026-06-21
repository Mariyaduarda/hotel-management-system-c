#include "hotel.h"
#include "../common.h"

/* ── Inicializa Hotel ─────────────────────────────────────────────── */
void HotelInit(Hotel *hotel){
    
    strcpy(hotel->NomeFantasia,      "-");
    strcpy(hotel->RazaoSocial,       "-");
    strcpy(hotel->InscricaoEstadual, "-");
    strcpy(hotel->CNPJ,              "-");
    strcpy(hotel->Email,             "-");
    strcpy(hotel->Telefone,          "-");
    strcpy(hotel->NomeResp,          "-");
    strcpy(hotel->CheckIn,           "00:00");
    strcpy(hotel->CheckOut,          "00:00");
    strcpy(hotel->TelefoneResp,      "-");

    hotel->ativo = 0; // Evita exclusao fisica

    // Inicializa endereco
    strcpy(hotel->endereco.rua,     "-");
    strcpy(hotel->endereco.numero,  "-");
    strcpy(hotel->endereco.complemento, "-");
    strcpy(hotel->endereco.bairro,  "-");
    strcpy(hotel->endereco.cidade,  "-");
    strcpy(hotel->endereco.estado,  "-"); 
    strcpy(hotel->endereco.cep,     "-");

    hotel->MargemLucro = 0.0f;
    hotel->TipoSalvamento = 0; // por padrao salva em txt
}

void ExcluirHotel(Hotel *hotel){
    HotelInit(hotel);    // Remove em mem
    
    remove("dados/hotel.txt"); //Remove em texto
    remove("dados/hotel.bin");  // Remove em bin

    printf("Sistema resetado. Todos os dados do hotel foram excluidos.\n");
}

int HotelSalvarBin(Hotel *hotel) {
    FILE *fp = fopen("dados/hotel.bin", "wb");
    if (!fp) return 0;
    fwrite(hotel, sizeof(Hotel), 1, fp);
    fclose(fp);
    return 1;
}

int HotelSalvarTxt(Hotel *hotel) {
    FILE *fp = fopen("dados/hotel.txt", "w");
    if (!fp) return 0;
    fprintf(fp, "Nome Fantasia: %s\n", hotel->NomeFantasia);
    fprintf(fp, "Razao Social: %s\n", hotel->RazaoSocial);
    fprintf(fp, "Inscricao Estadual: %s\n", hotel->InscricaoEstadual);
    fprintf(fp, "CNPJ: %s\n", hotel->CNPJ);
    fprintf(fp, "Email: %s\n", hotel->Email);
    fprintf(fp, "Telefone: %s\n", hotel->Telefone);
    fprintf(fp, "Nome do Responsavel: %s\n", hotel->NomeResp);
    fprintf(fp, "Telefone do Responsavel: %s\n", hotel->TelefoneResp);
    fprintf(fp, "Rua: %s\n", hotel->endereco.rua);
    fprintf(fp, "Numero: %s\n", hotel->endereco.numero);
    fprintf(fp, "Complemento: %s\n", hotel->endereco.complemento);
    fprintf(fp, "Bairro: %s\n", hotel->endereco.bairro);
    fprintf(fp, "Cidade: %s\n", hotel->endereco.cidade);
    fprintf(fp, "Estado: %s\n", hotel->endereco.estado);
    fprintf(fp, "CEP: %s\n", hotel->endereco.cep);
    fprintf(fp, "Check-in: %s\n", hotel->CheckIn);
    fprintf(fp, "Check-out: %s\n", hotel->CheckOut);
    fprintf(fp, "Margem de Lucro: %.2f\n", hotel->MargemLucro);
    fprintf(fp, "Tipo de Salvamento: %d\n", hotel->TipoSalvamento);
    fclose(fp);
    return 1;
}

int HotelLerTxt(Hotel *hotel) {
    FILE *fp = fopen("dados/hotel.txt", "r");
    if (!fp) return 0;

    int count = fscanf(fp,
        "Nome Fantasia: %99[^\n]\n"
        "Razao Social: %99[^\n]\n"
        "Inscricao Estadual: %19[^\n]\n"
        "CNPJ: %19[^\n]\n"
        "Email: %49[^\n]\n"
        "Telefone: %19[^\n]\n"
        "Nome do Responsavel: %49[^\n]\n"
        "Telefone do Responsavel: %19[^\n]\n"
        "Rua: %99[^\n]\n"
        "Numero: %9[^\n]\n"
        "Complemento: %49[^\n]\n"
        "Bairro: %49[^\n]\n"
        "Cidade: %49[^\n]\n"
        "Estado: %49[^\n]\n"
        "CEP: %19[^\n]\n"
        "Check-in: %5[^\n]\n"
        "Check-out: %5[^\n]\n"
        "Margem de Lucro: %lf\n"
        "Tipo de Salvamento: %d\n",
        hotel->NomeFantasia,
        hotel->RazaoSocial,
        hotel->InscricaoEstadual,
        hotel->CNPJ,
        hotel->Email,
        hotel->Telefone,
        hotel->NomeResp,
        hotel->TelefoneResp,
        hotel->endereco.rua,
        hotel->endereco.numero,
        hotel->endereco.complemento,
        hotel->endereco.bairro,
        hotel->endereco.cidade,
        hotel->endereco.estado,
        hotel->endereco.cep,
        hotel->CheckIn,
        hotel->CheckOut,
        &hotel->MargemLucro,
        &hotel->TipoSalvamento
    );

    fclose(fp);

    // confere se teve a qtd certa de parametros
    if (count != 19) return 0;
    else return 1;
}

int HotelLerBin(Hotel *hotel) {
    FILE *fp = fopen("dados/hotel.bin", "rb");
    if (!fp) return 0;
    fread(hotel, sizeof(Hotel), 1, fp);
    fclose(fp);
    return 1;
}

int HotelCarregar(Hotel *hotel) {
    // Pega o hotel do arquivo
    //  - Le primeiro o txt, se nao tiver le o bin

    // var auxiliar para ler o hotel
    Hotel temp;
    HotelInit(&temp);

    // Tenta ler do txt
    if (HotelLerTxt(&temp)) {
        *hotel = temp;
        return 1; // deu bom
    }

    // Tenta ler do bin
    if (HotelLerBin(&temp)) {
        *hotel = temp;
        return 1; // deu bom
    }

    // se n deu pra ler nenhum dos dois, retorna 0
    return 0;
}

int HotelSalvar(Hotel *hotel) {
    if (hotel->TipoSalvamento == 0) {
        return HotelSalvarTxt(hotel);
    }
    if (hotel->TipoSalvamento == 1) {
        return HotelSalvarBin(hotel);
    }
    return 1; // TipoSalvamento == 2 => não salva
}
