#ifndef CATEGORIA_VIEW_H
#define CATEGORIA_VIEW_H

#include "../model/categoria_acomodacao.h"

void CategoriaMenuExibir(void);
void CategoriaCadastrarView  (ListaCategoria **lista);
void CategoriaListarTodosView(ListaCategoria **lista);
void CategoriaBuscarView     (ListaCategoria **lista);
void CategoriaAtualizarView  (ListaCategoria **lista);
void CategoriaExcluirView    (ListaCategoria **lista);

#endif