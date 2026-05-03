#include "operador.h"
#include <string.h>   // 👈 ADICIONA ISSO
#include <openssl/sha.h>
#include "../common.h"
//#include <openssl/sha.h> // sha256

static Operador operador = {0}; // incializa com valor padrao

static void gerarSHA256(const char* senha, char* saida) {
    unsigned char hash[SHA256_DIGEST_LENGTH];
    SHA256((unsigned char*)senha, strlen(senha), hash);

    for(int i = 0; i < SHA256_DIGEST_LENGTH; i++) {
        sprintf(saida + (i * 2), "%02x", hash[i]);
    }

    saida[64] = '\0';
}

void criarOperador(){
   char senha[100];
   char confirmacao[100];

   printf(" -- Cadastro de Operador -- \n");

   operador.id = 1; // unico operador, id fixo

   printf("Usuario: ");
   scanf("%99s", operador.usuario);

   printf("Nome: ");
   scanf("%99s", operador.nome);

   do {
         printf("Senha: ");
         scanf("%99s", senha);

         printf("Confirme a senha: ");
         scanf("%99s", confirmacao);

         if (strcmp(senha, confirmacao) != 0) {
             printf("As senhas nao coincidem. Tente novamente.\n");
         }

   } while (strcmp(senha, confirmacao) != 0);

   gerarSHA256(senha, operador.senha);

   //limpar as senhas em texto plano da memoria
   memset(senha, 0, sizeof(senha));
   memset(confirmacao, 0, sizeof(confirmacao));

   printf("Operador %s usando o usuario %s criado com sucesso!\n", operador.nome ,operador.usuario);
}

// retorna um ponteiro constante para o operador, garantindo que nao possa ser modificado externamente
const Operador* obterOperador(void){ return &operador; }
