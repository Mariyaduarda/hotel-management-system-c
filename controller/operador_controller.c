/* controller/operador_controller.c */
#include "../common.h"
#include "operador_controller.h"
#include <string.h>

void controllerOperadorCriar(void) {
    criarOperador();
}

// Autentica comparando a senha digitada com a senha armazenada
int controllerOperadorAutenticar(const char *usuario, const char *senha) {
    const Operador *op = obterOperador();

    if (strcmp(op->usuario, usuario) != 0) return 0;

    return strcmp(op->senha, senha) == 0;
}

const Operador *controllerOperadorObter(void) {
    return obterOperador();
}

int controllerOperadorTemPermissao(int permissao) {
    const Operador *op = obterOperador();
    return (op->permissoes & permissao) != 0;
}