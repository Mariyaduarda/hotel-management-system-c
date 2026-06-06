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
}

void ExcluirHotel(Hotel *hotel){
    HotelInit(hotel);    // Remove em mem
    
    remove("hotel.txt"); //Remove em texto
    remove("hotel.bin");  // Remove em bin

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
    fprintf(fp, "Check-in: %s\n", hotel->CheckIn);
    fprintf(fp, "Check-out: %s\n", hotel->CheckOut);
    fprintf(fp, "Telefone do Responsavel: %s\n", hotel->TelefoneResp);
    fclose(fp);
    return 1;
}

int HotelLerTxt(Hotel *hotel) {
    (void)hotel; /* parâmetro não utilizado */
    FILE *fp = fopen("dados/hotel.txt", "r");
    if (!fp) return 0;
    char line[256];
    while (fgets(line, sizeof(line), fp)) {
        printf("%s", line);
    }
    fclose(fp);
    return 1;
}

int HotelLerBin(Hotel *hotel) {
    FILE *fp = fopen("dados/hotel.bin", "rb");
    if (!fp) return 0;
    fread(hotel, sizeof(Hotel), 1, fp);
    fclose(fp);
    return 1;
}
