#include "common.h"
#include "model/operador.h"
#include "model/hotel.h"
#include "model/hospede.h"
#include "model/reserva.h"
#include "model/acomodacao.h"
#include "model/categoria_acomodacao.h"
#include "model/produto.h"
#include "model/nota_fiscal.h"
#include "model/venda.h"
#include "model/checkin.h"
#include "model/contas_pagar.h"
#include "model/contas_receber.h"
#include "view/login_view.h"
#include "view/menu_principal.h"

int main() {
    /* ── Operador ─────────────────────────────────────────── */
    ListaOperador *ListaOperador = NULL;
    
    if (!OperadorLerBin(&ListaOperador)) {
    OperadorLerTxt(&ListaOperador);
    }

    if(ListaOperador == NULL) {
        if(!telaPrimeiroCadastro(&ListaOperador)) {
            printf("Erro ao cadastrar operador inicial.\n");
            OperadorListaLiberar(ListaOperador);
            return 1;
        }
        int salvo = OperadorSalvarBin(ListaOperador);
        printf("DEBUG: SalvarBin retornou %d\n", salvo);
        printf("DEBUG: Lista tem operador: %s\n", 
           ListaOperador ? ListaOperador->operador.usuario : "NULA");
        int leuBin = OperadorLerBin(&ListaOperador);
            printf("DEBUG: LerBin retornou %d\n", leuBin);
            if (!leuBin) {
                int leuTxt = OperadorLerTxt(&ListaOperador);
                printf("DEBUG: LerTxt retornou %d\n", leuTxt);
            }
        // persistencia ao inciar
        OperadorSalvarBin(ListaOperador);
        OperadorSalvarTxt(ListaOperador);

        printf("Operador inicial cadastrado com sucesso.\n");
    }

    /* ── Login ────────────────────────────────────────────── */
    Operador *logado = NULL;
    if (!telaLogin(&ListaOperador, &logado)) {
        printf("Falha no login. Sessao encerrada.\n");
            printf("DEBUG: Operadores na lista:\n");
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
    ListaHospede        *listaHospede    = NULL;
    ListaReserva        *listaReserva    = NULL;
    ListaAcomodacao     *listaAcomodacao = NULL;
    ListaCategoria      *listaCategoria  = NULL;
    ListaProduto        *listaProduto    = NULL;
    ListaNotaFiscal     *listaNotaFiscal = NULL;
    ListaVenda          *listaVenda      = NULL;
    ListaCheckin        *listaCheckin    = NULL;
    ListaContaPagar     *listaContaPagar = NULL;
    ListaContaReceber   *listaContaReceber = NULL;

    /* ── Carrega dados persistidos das Entidades ────────────────────────── */
   if (!HospedeLerBin(&listaHospede))       HospedeLerTxt(&listaHospede);
   if (!ReservaLerBin(&listaReserva))       ReservaLerTxt(&listaReserva);
   if (!AcomodacaoLerBin(&listaAcomodacao)) AcomodacaoLerTxt(&listaAcomodacao);
   if (!CategoriaLerBin(&listaCategoria))   CategoriaLerTxt(&listaCategoria);
   if (!ProdutoLerBin(&listaProduto))       ProdutoLerTxt(&listaProduto);
   if (!NotaFiscalLerBin(&listaNotaFiscal)) NotaFiscalLerTxt(&listaNotaFiscal);
   if (!VendaLerBin(&listaVenda))           VendaLerTxt(&listaVenda);
   if (!CheckinLerBin(&listaCheckin))       CheckinLerTxt(&listaCheckin);
   if (!ContaPagarLerBin(&listaContaPagar)) ContaPagarLerTxt(&listaContaPagar);
   if (!ContaReceberLerBin(&listaContaReceber)) ContaReceberLerTxt(&listaContaReceber);

    /* ── Menu principal ───────────────────────────────────── */
    menuPrincipal(&listaHospede,
                  &listaReserva,
                  &listaAcomodacao,
                  &listaCategoria,
                  &listaProduto,
                  &hotel,
                  &listaNotaFiscal,
                  &listaVenda,
                  &listaCheckin,
                  &listaContaPagar,
                  &listaContaReceber);
    
    /* ── Salva ao sair ────────────────────────────────────── */
    HospedeSalvarBin(listaHospede);
    ReservaSalvarBin(listaReserva);
    AcomodacaoSalvarBin(listaAcomodacao);
    CategoriaSalvarBin(listaCategoria);
    ProdutoSalvarBin(listaProduto);
    HotelSalvarBin(&hotel);
    NotaFiscalSalvarBin(listaNotaFiscal);
    VendaSalvarBin(listaVenda);
    CheckinSalvarBin(listaCheckin);
    ContaPagarSalvarBin(listaContaPagar);
    ContaReceberSalvarBin(listaContaReceber);

    HospedeSalvarTxt(listaHospede);
    ReservaSalvarTxt(listaReserva);
    AcomodacaoSalvarTxt(listaAcomodacao);
    CategoriaSalvarTxt(listaCategoria);
    ProdutoSalvarTxt(listaProduto);
    HotelSalvarTxt(&hotel);
    NotaFiscalSalvarTxt(listaNotaFiscal);
    VendaSalvarTxt(listaVenda);
    CheckinSalvarTxt(listaCheckin);
    ContaPagarSalvarTxt(listaContaPagar);
    ContaReceberSalvarTxt(listaContaReceber);

    /* ── Libera memória ───────────────────────────────────── */
    HospedeListaLiberar(listaHospede);
    ReservaListaLiberar(listaReserva);
    AcomodacaoListaLiberar(listaAcomodacao);
    CategoriaListaLiberar(listaCategoria);
    ProdutoListaLiberar(listaProduto);
    NotaFiscalListaLiberar(listaNotaFiscal);
    VendaListaLiberar(listaVenda);
    CheckinListaLiberar(listaCheckin);
    ContaPagarListaLiberar(listaContaPagar);
    ContaReceberListaLiberar(listaContaReceber);

    return 0;
}