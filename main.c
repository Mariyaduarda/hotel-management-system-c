#include "common.h"
#include "model/operador.h"
#include "model/hotel.h"
#include "model/hospede.h"
#include "model/reserva.h"
#include "model/acomodacao.h"
#include "model/categoria_acomodacao.h"
#include "model/produto.h"
#include "view/login_view.h"
#include "view/menu_principal.h"

int main() {
    /* ── Operador ─────────────────────────────────────────── */
    ListaOperador *ListaOperador = NULL;
    OperadorLerBin(&ListaOperador);
    OperadorLerTxt(&ListaOperador);

    if(ListaOperador == NULL) {
        if(!telaPrimeiroCadastro(&ListaOperador)) {
            printf("Erro ao cadastrar operador inicial.\n");
            OperadorListaLiberar(ListaOperador);
            return 1;
        }
        // persistencia ao inciar
        OperadorSalvarBin(ListaOperador);
        OperadorSalvarTxt(ListaOperador);
        printf("Operador inicial cadastrado com sucesso.\n");
        return 1;
    }

    /* ── Login ────────────────────────────────────────────── */
    Operador *logado = NULL;
    if (!telaLogin(&ListaOperador, &logado)) {
        printf("Falha no login. Sessao encerrada.\n");
        OperadorListaLiberar(ListaOperador);
        return 1; /* falha no login */
    }

    /* ── Hotel ────────────────────────────────────────────── */
    Hotel hotel;
    HotelInit(&hotel);
    
    int hotelConfigurado = HotelLerBin(&hotel) || HotelLerTxt(&hotel);
    if (!hotelConfigurado) {
        if(!hotelConfigurado){
            printf("Nenhuma configuração de hotel encontrada. Por favor, configure o hotel.\n");
            OperadorListaLiberar(ListaOperador);
            return 1;
        }
        HotelSalvarBin(&hotel);
        HotelSalvarTxt(&hotel);
    }

    /* ── Listas das Entidades ────────────────────────────────────── */
    ListaHospede    *listaHospede    = NULL;
    ListaReserva    *listaReserva    = NULL;
    ListaAcomodacao *listaAcomodacao = NULL;
    ListaCategoria  *listaCategoria  = NULL;
    ListaProduto    *listaProduto    = NULL;

    /* ── Carrega dados persistidos das Entidades ────────────────────────── */
    HospedeLerBin(&listaHospede);
    ReservaLerBin(&listaReserva);
    AcomodacaoLerBin(&listaAcomodacao);
    CategoriaLerBin(&listaCategoria);
    ProdutoLerBin(&listaProduto);

    HospedeLerTxt(&listaHospede);
    ReservaLerTxt(&listaReserva);
    AcomodacaoLerTxt(&listaAcomodacao);
    CategoriaLerTxt(&listaCategoria);
    ProdutoLerTxt(&listaProduto);

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

    HospedeSalvarTxt(listaHospede);
    ReservaSalvarTxt(listaReserva);
    AcomodacaoSalvarTxt(listaAcomodacao);
    CategoriaSalvarTxt(listaCategoria);
    ProdutoSalvarTxt(listaProduto);
    HotelSalvarTxt(&hotel);

    /* ── Libera memória ───────────────────────────────────── */
    HospedeListaLiberar(listaHospede);
    ReservaListaLiberar(listaReserva);
    AcomodacaoListaLiberar(listaAcomodacao);
    CategoriaListaLiberar(listaCategoria);
    ProdutoListaLiberar(listaProduto);

    return 0;
}