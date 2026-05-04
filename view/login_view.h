#ifndef LOGIN_VIEW_H
#define LOGIN_VIEW_H

#include "../model/operador.h"

/* Exibe tela de login. Retorna 1 em sucesso, 0 em falha. */
int telaLogin(ListaOperador **lista, Operador **logado);

/* Exibe tela de primeiro cadastro quando nao ha operadores. */
int telaPrimeiroCadastro(ListaOperador **lista);

#endif // LOGIN_VIEW_H