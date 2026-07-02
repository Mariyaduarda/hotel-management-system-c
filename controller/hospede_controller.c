// controller/hospede_controller.c
#include "../common.h"
#include "../model/hospede.h"
#include "hospede_controller.h"

/* ──────────────────────────────────────────────────────────
   Cadastrar novo hóspede
   Retorna 1 em sucesso, 0 em falha
   ────────────────────────────────────────────────────────── */
int controllerHospedeCadastrar(ListaHospede **lista, TipoHospede h) {
    ler_string("Nome: ", h.nome, sizeof(h.nome));
    ler_string("CPF: ", h.cpf, sizeof(h.cpf));
    ler_string("Email: ", h.email, sizeof(h.email));
    ler_string("Telefone: ", h.telefone, sizeof(h.telefone));
    ler_string("Sexo: ", h.sexo, sizeof(h.sexo));
    ler_string("Data de Nascimento (dd/mm/aaaa): ", h.dataNascimento, sizeof(h.dataNascimento));
    ler_string("Estado Civil: ", h.estadoCivil, sizeof(h.estadoCivil));
    ler_string("Endereço: ", h.endereco.rua, sizeof(h.endereco.rua));
    ler_string("Número: ", h.endereco.numero, sizeof(h.endereco.numero));
    ler_string("Complemento: ", h.endereco.complemento, sizeof(h.endereco.complemento));
    ler_string("Bairro: ", h.endereco.bairro, sizeof(h.endereco.bairro));
    ler_string("Cidade: ", h.endereco.cidade, sizeof(h.endereco.cidade));
    ler_string("Estado: ", h.endereco.estado, sizeof(h.endereco.estado));
    ler_string("CEP: ", h.endereco.cep, sizeof(h.endereco.cep));
    return HospedeCriar(lista, h);
}

/* ──────────────────────────────────────────────────────────
   Listar hóspede por ID
   ────────────────────────────────────────────────────────── */
void controllerHospedeListar(ListaHospede **lista, int id) {
    HospedeListar(lista, id);
}

/* ──────────────────────────────────────────────────────────
   Buscar hóspede por ID
   Retorna ponteiro para TipoHospede ou NULL se não encontrado
   ────────────────────────────────────────────────────────── */
TipoHospede *controllerHospedeBuscar(ListaHospede **lista, int id) {
    return HospedeBuscar(lista, id);
}

/* ──────────────────────────────────────────────────────────
   Atualizar campo(s) do hóspede
   op: 1=todos 2=nome 3=cpf 4=email 5=tel 6=sexo 7=nasc 8=est.civil
   Retorna 1 em sucesso, 0 em falha
   ────────────────────────────────────────────────────────── */
int controllerHospedeAtualizar(ListaHospede **lista, int id, int op) {
    return HospedeAtualizar(lista, id, op);
}

/* ──────────────────────────────────────────────────────────
   Exclusão lógica do hóspede (ativo = 0)
   Retorna 1 em sucesso, 0 se não encontrado
   ────────────────────────────────────────────────────────── */
int controllerHospedeExcluir(ListaHospede **lista, int id) {
    return HospedeExcluir(lista, id);
}

/* ──────────────────────────────────────────────────────────
   Persistência — salvar
   ────────────────────────────────────────────────────────── */
int controllerHospedeSalvar(ListaHospede *lista) {
    if (!HospedeSalvarTxt(lista)) return 0;
    if (!HospedeSalvarBin(lista)) return 0;
    return 1;
}

/* ──────────────────────────────────────────────────────────
   Persistência — carregar (tenta .bin, cai em .txt)
   ────────────────────────────────────────────────────────── */
int controllerHospedeCarregar(ListaHospede **lista) {
    if (HospedeLerBin(lista)) return 1;
    return HospedeLerTxt(lista);
}

/* ──────────────────────────────────────────────────────────
   Liberar lista da memória
   ────────────────────────────────────────────────────────── */
void controllerHospedeLiberar(ListaHospede *lista) {
    HospedeListaLiberar(lista);
}

/* Adicione isso no FINAL do seu hospede_controller.c
   e declare no hospede_controller.h também               */

void HospedeControllerExecutar(ListaHospede **lista) {
    int opcao;
    do {
        printf("\n╔══════════════════════════════╗\n");
        printf(  "║       MENU DE HÓSPEDES       ║\n");
        printf(  "╠══════════════════════════════╣\n");
        printf(  "║ 1. Cadastrar hóspede         ║\n");
        printf(  "║ 2. Listar todos              ║\n");
        printf(  "║ 3. Buscar por ID             ║\n");
        printf(  "║ 4. Atualizar hóspede         ║\n");
        printf(  "║ 5. Excluir hóspede           ║\n");
        printf(  "║ 0. Voltar                    ║\n");
        printf(  "╚══════════════════════════════╝\n");
        opcao = ler_int("Opcao: ");

        switch (opcao) {
            case 1:
                TipoHospede h;
                controllerHospedeCadastrar(lista, h);
                break;
            case 2:
                controllerHospedeListar(lista, 0);
                break;
            case 3: {
                int id;
                id = ler_int("ID: ");
                controllerHospedeListar(lista, id);
                break;
            }
            case 4: {
                int id, op;
                id = ler_int("ID: ");
                op = ler_int("Campo (1=nome 2=cpf 3=email 4=tel 5=sexo 6=nasc 7=est.civil): ");
                controllerHospedeAtualizar(lista, id, op);
                break;
            }
            case 5: {
                int id;
                id = ler_int("ID: ");
                controllerHospedeExcluir(lista, id);
                break;
            }
            case 0: break;
            default: printf("Opcao invalida.\n");
        }
    } while (opcao != 0);
}