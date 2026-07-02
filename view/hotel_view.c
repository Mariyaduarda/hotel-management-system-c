#include "hotel_view.h"
#include "../common.h"

void HotelMenuExibir(void) {
    printf("\n=== CONFIGURACAO DO HOTEL ===\n");
    printf("[1] Ver dados do hotel\n");
    printf("[2] Editar hotel\n");
    printf("[3] Excluir hotel\n");
    printf("[0] Voltar\n");
    printf("Opcao: ");
}

void HotelMenuExecutar(Hotel *hotel) {
    int opcao;
    do {
        HotelMenuExibir();
        opcao = ler_int("");

        switch (opcao) {
            case 1:
                HotelExibir(hotel);
                break;
            case 2:
                HotelEditarView(hotel);
                HotelSalvar(hotel);
                break;
            case 3:
                ExcluirHotel(hotel);
                break;
            case 0:
                break;
            default:
                printf("Opcao invalida.\n");
        }
    } while (opcao != 0);
}

int HotelPrimeiroCadastroView(Hotel *hotel) {
    printf("\n=== Cadastrar Hotel ===\n");

    ler_string(" Nome Fantasia: ",           hotel->NomeFantasia,         sizeof(hotel->NomeFantasia)         );
    ler_string(" Razao Social: ",            hotel->RazaoSocial,          sizeof(hotel->RazaoSocial)          );
    ler_string(" Inscricao Estadual: ",      hotel->InscricaoEstadual,    sizeof(hotel->InscricaoEstadual)    );
    ler_string(" CNPJ: ",                    hotel->CNPJ,                 sizeof(hotel->CNPJ)                 );
    ler_string(" Email: ",                   hotel->Email,                sizeof(hotel->Email)                );
    ler_string(" Telefone: ",                hotel->Telefone,             sizeof(hotel->Telefone)             );
    ler_string(" Nome do Responsavel: ",     hotel->NomeResp,             sizeof(hotel->NomeResp)             );
    ler_string(" Telefone do Responsavel: ", hotel->TelefoneResp,         sizeof(hotel->TelefoneResp)         );
    ler_string(" Rua: ",                     hotel->endereco.rua,         sizeof(hotel->endereco.rua)         );
    ler_string(" Numero: ",                  hotel->endereco.numero,      sizeof(hotel->endereco.numero)      );
    ler_string(" Complemento: ",             hotel->endereco.complemento, sizeof(hotel->endereco.complemento) );
    ler_string(" Bairro: ",                  hotel->endereco.bairro,      sizeof(hotel->endereco.bairro)      );
    ler_string(" Cidade: ",                  hotel->endereco.cidade,      sizeof(hotel->endereco.cidade)      );
    ler_string(" Estado: ",                  hotel->endereco.estado,      sizeof(hotel->endereco.estado)      );
    ler_string(" CEP: ",                     hotel->endereco.cep,         sizeof(hotel->endereco.cep)         );
    ler_string(" Check-in (HH:MM): ",        hotel->CheckIn,              sizeof(hotel->CheckIn)              );
    ler_string(" Check-out (HH:MM): ",       hotel->CheckOut,             sizeof(hotel->CheckOut)             );
    hotel->MargemLucro = ler_float(" Margem de Lucro (%%): ");
    hotel->TipoSalvamento = ler_int(" Tipo de Salvamento (0-TXT, 1-BIN, 2-Nao salvar): ");
    return HotelSalvar(hotel);
}

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
    printf(  "║  [13] Tipo de Salvamento                             ║\n");
    printf(  "║  [0]  Voltar                                         ║\n");
    printf(  "╚══════════════════════════════════════════════════════╝\n");
    opcao = ler_int("Opcao: ");

    switch (opcao) {
        case 1:  ler_string("Nome Fantasia: ",     hotel->NomeFantasia,      sizeof(hotel->NomeFantasia));      break;
        case 2:  ler_string("Razao Social: ",      hotel->RazaoSocial,       sizeof(hotel->RazaoSocial));       break;
        case 3:  ler_string("CNPJ: ",              hotel->CNPJ,              sizeof(hotel->CNPJ));              break;
        case 4:  ler_string("Insc. Estadual: ",    hotel->InscricaoEstadual, sizeof(hotel->InscricaoEstadual)); break;
        case 5:  ler_string("Email: ",             hotel->Email,             sizeof(hotel->Email));             break;
        case 6:  ler_string("Telefone: ",          hotel->Telefone,          sizeof(hotel->Telefone));          break;
        case 7:  ler_string("Nome Responsavel: ",  hotel->NomeResp,          sizeof(hotel->NomeResp));          break;
        case 8:  ler_string("Telefone Resp.: ",    hotel->TelefoneResp,      sizeof(hotel->TelefoneResp));      break;
        case 9:  ler_string("Check-in (HH:MM): ",  hotel->CheckIn,           sizeof(hotel->CheckIn));           break;
        case 10: ler_string("Check-out (HH:MM): ", hotel->CheckOut,          sizeof(hotel->CheckOut));          break;
        case 11: hotel->MargemLucro = ler_long("Margem de Lucro (%%): "); break;
        case 12:
            ler_string("Rua: ",         hotel->endereco.rua,         sizeof(hotel->endereco.rua));
            ler_string("Numero: ",      hotel->endereco.numero,      sizeof(hotel->endereco.numero));
            ler_string("Complemento: ", hotel->endereco.complemento, sizeof(hotel->endereco.complemento));
            ler_string("Bairro: ",      hotel->endereco.bairro,      sizeof(hotel->endereco.bairro));
            ler_string("Cidade: ",      hotel->endereco.cidade,      sizeof(hotel->endereco.cidade));
            ler_string("Estado: ",      hotel->endereco.estado,      sizeof(hotel->endereco.estado));
            ler_string("CEP: ",         hotel->endereco.cep,         sizeof(hotel->endereco.cep));
            break;
        case 13:
            hotel->TipoSalvamento = ler_int("Tipo de Salvamento (0-TXT, 1-BIN, 2-Nao salvar): ");
            break;
        case 0:
            return;
        default:
            printf("Opcao invalida.\n"); 
            break;
    }
    printf("Hotel atualizado com sucesso!\n");
}