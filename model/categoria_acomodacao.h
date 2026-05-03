#ifndef CATEGORIA_H
#define CATEGORIA_H

typedef struct {
    int   id;
    char  descricao[100];   // ex: Standard, Luxo, Presidencial
    float valorDiaria;
    int   maxAdultos;
    int   maxCriancas;
    int   ativo;
} TipoCategoria;

typedef struct ListaCategoria {
    struct ListaCategoria *proximo;
    TipoCategoria categoria;
} ListaCategoria;

// Funcoes base
void CategoriasInit(TipoCategoria *categoria);
void CategoriaListaInit(ListaCategoria *lista);

int  CategoriarCriar(ListaCategoria **lista, TipoCategoria categoria);
void CategoriaListar(ListaCategoria **lista, int id);
TipoCategoria* CategoriaBuscar(ListaCategoria **lista, int id);
int  CategoriaExcluir(ListaCategoria **lista, int id);
int  CategoriaAtualizar(ListaCategoria **lista, int id, int op);
void CategoriaListaLiberar(ListaCategoria *lista);

// Funcoes de arquivo
int CategoriaSalvarTxt(ListaCategoria *lista);
int CategoriaSalvarBin(ListaCategoria *lista);
int CategoriaLerTxt(ListaCategoria **lista);
int CategoriaLerBin(ListaCategoria **lista);

#endif // CATEGORIA_H