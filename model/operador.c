#include "operador.h"
#include <string.h>   // 👈 ADICIONA ISSO

#include "../common.h"
//#include <openssl/sha.h> // sha256

static Operador operador = {0}; // incializa com valor padrao

static void gerarSHA256(const char* senha, char* saida) {
    // hash fake só para teste
    snprintf(saida, 65, "hash_%s", senha);
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
