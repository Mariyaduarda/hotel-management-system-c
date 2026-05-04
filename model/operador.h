#ifndef OPERADOR_H
#define OPERADOR_H

// Flags de permissao (bitmask) — combinar com OR bit a bit
#define PERM_CADASTRO    (1 << 0)  // 1
#define PERM_RESERVAS    (1 << 1)  // 2
#define PERM_TRANSACOES  (1 << 2)  // 4
#define PERM_FEEDBACK    (1 << 3)  // 8
#define PERM_IMPORTEXPORT (1 << 4) // 16
#define PERM_ADMIN       0xFF      // todas as permissoes

typedef struct {
    int  id;
    char nome[100];
    char usuario[50];
    char senha[65];      // SHA256 gera 64 caracteres hex + null terminator
    int  permissoes;     // bitmask com PERM_*
    int  ativo;
} Operador;

typedef struct ListaOperador {
    struct ListaOperador *proximo;
    Operador operador;
} ListaOperador;

// Funcoes base
void OperadorInit(Operador *operador);
void OperadorListaInit(ListaOperador *lista);

int  OperadorCriar(ListaOperador **lista, Operador operador);
void OperadorListar(ListaOperador **lista, int id);
Operador* OperadorBuscar(ListaOperador **lista, int id);
Operador* OperadorBuscarPorUsuario(ListaOperador **lista, const char *usuario);
int  OperadorExcluir(ListaOperador **lista, int id);
int  OperadorAtualizar(ListaOperador **lista, int id, int op);
void OperadorListaLiberar(ListaOperador *lista);

// Autenticacao
int  OperadorAutenticar(ListaOperador **lista, const char *usuario, const char *senha, Operador **logado);
int  OperadorTemPermissao(Operador *operador, int permissao);

// Funcoes globais para o operador atual
void criarOperador(void);
const Operador* obterOperador(void);

// Funcoes de arquivo
int OperadorSalvarTxt(ListaOperador *lista);
int OperadorSalvarBin(ListaOperador *lista);
int OperadorLerTxt(ListaOperador **lista);
int OperadorLerBin(ListaOperador **lista);

#endif // OPERADOR_H