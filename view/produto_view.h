#ifndef PRODUTO_VIEW_H
#define PRODUTO_VIEW_H

#include "../model/produto.h"

void ProdutoMenuExibir(void);
void ProdutoCadastrarView(ListaProduto **lista);
void ProdutoListarView(ListaProduto **lista);
void ProdutoBuscarView(ListaProduto **lista);
void ProdutoExcluirView(ListaProduto **lista);
void ProdutoAtualizarView(ListaProduto **lista);

#endif // PRODUTO_VIEW_H