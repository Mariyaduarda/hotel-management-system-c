/* controller/operador_controller.c */
#include "../common.h"
#include "operador_controller.h"
#include <string.h>
#include <openssl/sha.h>

void controllerOperadorCriar(void) {
    criarOperador();
}

// Autentica comparando SHA256 da senha digitada com o hash salvo
int controllerOperadorAutenticar(const char *usuario, const char *senha) {
    const Operador *op = obterOperador();

    if (strcmp(op->usuario, usuario) != 0) return 0;

    // Gera hash da senha digitada
    char hash[65];
    unsigned char digest[SHA256_DIGEST_LENGTH];
    SHA256((unsigned char *)senha, strlen(senha), digest);
    for (int i = 0; i < SHA256_DIGEST_LENGTH; i++)
        sprintf(hash + (i * 2), "%02x", digest[i]);
    hash[64] = '\0';

    return strcmp(op->senha, hash) == 0;
}

const Operador *controllerOperadorObter(void) {
    return obterOperador();
}

int controllerOperadorTemPermissao(int permissao) {
    const Operador *op = obterOperador();
    return (op->permissoes & permissao) != 0;
}