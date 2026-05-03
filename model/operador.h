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
    char senha[50];      // armazenar hash em producao; aqui texto simples p/ fins didaticos
    int  permissoes;     // bitmask com PERM_*
    int  ativo;
} TipoOperador;

typedef struct ListaOperador {
    struct ListaOperador *proximo;
    TipoOperador operador;
} ListaOperador;

// Funcoes base
void OperadorInit(TipoOperador *operador);
void OperadorListaInit(ListaOperador *lista);

int  OperadorCriar(ListaOperador **lista, TipoOperador operador);
void OperadorListar(ListaOperador **lista, int id);
TipoOperador* OperadorBuscar(ListaOperador **lista, int id);
TipoOperador* OperadorBuscarPorUsuario(ListaOperador **lista, const char *usuario);
int  OperadorExcluir(ListaOperador **lista, int id);
int  OperadorAtualizar(ListaOperador **lista, int id, int op);
void OperadorListaLiberar(ListaOperador *lista);

// Autenticacao
int  OperadorAutenticar(ListaOperador **lista, const char *usuario, const char *senha, TipoOperador **logado);
int  OperadorTemPermissao(TipoOperador *operador, int permissao);

// Funcoes de arquivo
int OperadorSalvarTxt(ListaOperador *lista);
int OperadorSalvarBin(ListaOperador *lista);
int OperadorLerTxt(ListaOperador **lista);
int OperadorLerBin(ListaOperador **lista);

#endif // OPERADOR_H