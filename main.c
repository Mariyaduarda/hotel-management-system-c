#include "common.h"
#include "model/operador.h"
int main(){

   criarOperador();

    // recupera e exibe os dados
    const Operador* op = obterOperador();

    printf("\n=== Dados do Operador ===\n");
    printf("ID: %d\n", op->id);
    printf("Usuario: %s\n", op->usuario);
    printf("Senha (SHA256): %s\n", op->senha);

    return 0;
}