#include "hotel_view.h"
#include "../common.h"

void HotelExibir(Hotel *hotel) {
    printf("\n╔══════════════════════════════════════════════════════╗\n");
    printf(  "║              DADOS DO HOTEL                          ║\n");
    printf(  "╠══════════════════════════════════════════════════════╣\n");
    printf(  "║  Nome Fantasia    : %-33s║\n", hotel->NomeFantasia);
    printf(  "║  Razao Social     : %-33s║\n", hotel->RazaoSocial);
    printf(  "║  CNPJ             : %-33s║\n", hotel->CNPJ);
    printf(  "║  Insc. Estadual   : %-33s║\n", hotel->InscricaoEstadual);
    printf(  "║  Email            : %-33s║\n", hotel->Email);
    printf(  "║  Telefone         : %-33s║\n", hotel->Telefone);
    printf(  "╠══════════════════════════════════════════════════════╣\n");
    printf(  "║              RESPONSAVEL                             ║\n");
    printf(  "╠══════════════════════════════════════════════════════╣\n");
    printf(  "║  Nome             : %-33s║\n", hotel->NomeResp);
    printf(  "║  Telefone         : %-33s║\n", hotel->TelefoneResp);
    printf(  "╠══════════════════════════════════════════════════════╣\n");
    printf(  "║              ENDERECO                                ║\n");
    printf(  "╠══════════════════════════════════════════════════════╣\n");
    printf(  "║  Rua              : %-33s║\n", hotel->endereco.rua);
    printf(  "║  Numero           : %-33s║\n", hotel->endereco.numero);
    printf(  "║  Complemento      : %-33s║\n", hotel->endereco.complemento);
    printf(  "║  Bairro           : %-33s║\n", hotel->endereco.bairro);
    printf(  "║  Cidade           : %-33s║\n", hotel->endereco.cidade);
    printf(  "║  Estado           : %-33s║\n", hotel->endereco.estado);
    printf(  "║  CEP              : %-33s║\n", hotel->endereco.cep);
    printf(  "╠══════════════════════════════════════════════════════╣\n");
    printf(  "║  Check-in         : %-33s║\n", hotel->CheckIn);
    printf(  "║  Check-out        : %-33s║\n", hotel->CheckOut);
    printf(  "║  Margem de Lucro  : %-32.1f%%║\n", hotel->MargemLucro);
    printf(  "╚══════════════════════════════════════════════════════╝\n");
}

void HotelEditarView(Hotel *hotel) {
    int opcao;
    printf("\n╔══════════════════════════════════════════════════════╗\n");
    printf(  "║              EDITAR HOTEL                            ║\n");
    printf(  "╠══════════════════════════════════════════════════════╣\n");
    printf(  "║  [1]  Nome Fantasia                                  ║\n");
    printf(  "║  [2]  Razao Social                                   ║\n");
    printf(  "║  [3]  CNPJ                                           ║\n");
    printf(  "║  [4]  Inscricao Estadual                             ║\n");
    printf(  "║  [5]  Email                                          ║\n");
    printf(  "║  [6]  Telefone                                       ║\n");
    printf(  "║  [7]  Nome do Responsavel                            ║\n");
    printf(  "║  [8]  Telefone do Responsavel                        ║\n");
    printf(  "║  [9]  Check-in                                       ║\n");
    printf(  "║  [10] Check-out                                      ║\n");
    printf(  "║  [11] Margem de Lucro                                ║\n");
    printf(  "║  [12] Endereco completo                              ║\n");
    printf(  "║  [0]  Voltar                                         ║\n");
    printf(  "╚══════════════════════════════════════════════════════╝\n");
    printf("Opcao: ");
    scanf("%d", &opcao);
    limparBuffer();

    switch (opcao) {
        case 1:  printf("Nome Fantasia: ");       lerString(hotel->NomeFantasia,      sizeof(hotel->NomeFantasia));      break;
        case 2:  printf("Razao Social: ");        lerString(hotel->RazaoSocial,       sizeof(hotel->RazaoSocial));       break;
        case 3:  printf("CNPJ: ");                lerString(hotel->CNPJ,              sizeof(hotel->CNPJ));              break;
        case 4:  printf("Insc. Estadual: ");      lerString(hotel->InscricaoEstadual, sizeof(hotel->InscricaoEstadual)); break;
        case 5:  printf("Email: ");               lerString(hotel->Email,             sizeof(hotel->Email));             break;
        case 6:  printf("Telefone: ");            lerString(hotel->Telefone,          sizeof(hotel->Telefone));          break;
        case 7:  printf("Nome Responsavel: ");    lerString(hotel->NomeResp,          sizeof(hotel->NomeResp));          break;
        case 8:  printf("Telefone Resp.: ");      lerString(hotel->TelefoneResp,      sizeof(hotel->TelefoneResp));      break;
        case 9:  printf("Check-in (HH:MM): ");    lerString(hotel->CheckIn,           sizeof(hotel->CheckIn));           break;
        case 10: printf("Check-out (HH:MM): ");   lerString(hotel->CheckOut,          sizeof(hotel->CheckOut));          break;
        case 11: printf("Margem de Lucro (%%): "); scanf("%lf", &hotel->MargemLucro);  limparBuffer();                    break;
        case 12:
            printf("Rua: ");          lerString(hotel->endereco.rua,         sizeof(hotel->endereco.rua));
            printf("Numero: ");       lerString(hotel->endereco.numero,      sizeof(hotel->endereco.numero));
            printf("Complemento: ");  lerString(hotel->endereco.complemento, sizeof(hotel->endereco.complemento));
            printf("Bairro: ");       lerString(hotel->endereco.bairro,      sizeof(hotel->endereco.bairro));
            printf("Cidade: ");       lerString(hotel->endereco.cidade,      sizeof(hotel->endereco.cidade));
            printf("Estado: ");       lerString(hotel->endereco.estado,      sizeof(hotel->endereco.estado));
            printf("CEP: ");          lerString(hotel->endereco.cep,         sizeof(hotel->endereco.cep));
            break;
        case 0: return;
        default: printf("Opcao invalida.\n"); return;
    }
    printf("Hotel atualizado com sucesso!\n");
}