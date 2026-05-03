#include "common.h"
#include "model/operador.h"
#include "model/hotel.h"
#include "model/hospede.h"
#include "model/reserva.h"
#include "model/acomodacao.h"
#include "model/categoria_acomodacao.h"
#include "model/produto.h"
#include "view/menu_principal.h"

int main() {
    /* ── Operador ─────────────────────────────────────────── */
    criarOperador();
    const Operador *op = obterOperador();
    printf("\n=== Operador logado ===\n");
    printf("ID      : %d\n",  op->id);
    printf("Nome    : %s\n",  op->nome);
    printf("Usuario : %s\n",  op->usuario);
    printf("Senha (SHA256): %s\n", op->senha);

    /* ── Hotel ────────────────────────────────────────────── */
    Hotel hotel;
    HotelInit(&hotel);
    HotelLerBin(&hotel); // tenta carregar do arquivo; se nao existir usa os defaults
    printf("\n=== Hotel ===\n");
    printf("Nome Fantasia : %s\n", hotel.NomeFantasia);
    printf("Cidade        : %s\n", hotel.endereco.cidade);
    printf("Check-in      : %s\n", hotel.CheckIn);
    printf("Check-out     : %s\n", hotel.CheckOut);

    /* ── Listas ───────────────────────────────────────────── */
    ListaHospede    *listaHospede    = NULL;
    ListaReserva    *listaReserva    = NULL;
    ListaAcomodacao *listaAcomodacao = NULL;
    ListaCategoria  *listaCategoria  = NULL;
    ListaProduto    *listaProduto    = NULL;

    /* ── Carrega dados persistidos ────────────────────────── */
    HospedeLerBin(&listaHospede);
    ReservaLerBin(&listaReserva);
    AcomodacaoLerBin(&listaAcomodacao);
    CategoriaLerBin(&listaCategoria);
    ProdutoLerBin(&listaProduto);

    /* ── Menu principal ───────────────────────────────────── */
    menuPrincipal(&listaHospede,
                  &listaReserva,
                  &listaAcomodacao,
                  &listaCategoria,
                  &listaProduto,
                  &hotel);

    /* ── Salva ao sair ────────────────────────────────────── */
    HospedeSalvarBin(listaHospede);
    ReservaSalvarBin(listaReserva);
    AcomodacaoSalvarBin(listaAcomodacao);
    CategoriaSalvarBin(listaCategoria);
    ProdutoSalvarBin(listaProduto);
    HotelSalvarBin(&hotel);

    /* ── Libera memória ───────────────────────────────────── */
    HospedeListaLiberar(listaHospede);
    ReservaListaLiberar(listaReserva);
    AcomodacaoListaLiberar(listaAcomodacao);
    CategoriaListaLiberar(listaCategoria);
    ProdutoListaLiberar(listaProduto);

    return 0;
}