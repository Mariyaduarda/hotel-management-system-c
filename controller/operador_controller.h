#ifndef OPERADOR_CONTROLLER_H
#define OPERADOR_CONTROLLER_H

#include "../model/operador.h"

// Cadastro e autenticacao
void            controllerOperadorCriar(void);
int             controllerOperadorAutenticar(const char *usuario, const char *senha);
const Operador *controllerOperadorObter(void);

// Permissoes
int  controllerOperadorTemPermissao(int permissao);

#endif // OPERADOR_CONTROLLER_H