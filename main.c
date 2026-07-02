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
#include "model/caixa.h"
#include "model/fornecedor.h"
#include "view/login_view.h"
#include "view/menu_principal.h"
#include "controller/hotel_controller.h"

int main() {
    // ==================================================
    // HOTEL
    // Ler o hotel primeiro, pra decidir se vai pegar o resto do txt ou do bin
    Hotel hotel;
    HotelInit(&hotel);

    // tenta ler e decide o tipo de salvamento
    if (!HotelCarregar(&hotel)) {
        // se nao conseguiu ler nd, realiza o primeiro cadastro do hotel
        if (!controllerHotelPrimeiroCadastro(&hotel)) {
            // se nem assim deu, deu erro e retorna
            printf("Erro ao cadastrar hotel inicial.\n");
            return 1;
        }
    }

    // ==================================================
    // OPERADOR
    // Carrega os operadores pra poder fzr o login daqui a pouco
    ListaOperador *ListaOperador = NULL;
    if (hotel.TipoSalvamento == 0) {
        OperadorLerTxt(&ListaOperador);
    } else if (hotel.TipoSalvamento == 1) {
        OperadorLerBin(&ListaOperador);
    }

    // Se nao tiver nenhum operador cadastrado, faz o primeiro cadastro de operador
    if (ListaOperador == NULL) {
        if (!telaPrimeiroCadastro(&ListaOperador)) {
            // Se n conseguir nem cadastrar um operador, retorna erro e fecha o programa
            printf("Erro ao cadastrar operador inicial.\n");
            OperadorListaLiberar(ListaOperador);
            return 1;
        }
        
        printf("Operador inicial cadastrado com sucesso.\n");
    }

    // ==================================================
    // LOGIN

    Operador *logado = NULL;
    if (!telaLogin(&ListaOperador, &logado)) {
        // se n conseguiu logar, libera a lista de operadores e fecha o programa
        printf("Falha no login. Sessao encerrada.\n");
        printf("DEBUG: Operadores na lista:\n");
        OperadorListaLiberar(ListaOperador);
        return 1; /* falha no login */
    }

    // ==================================================
    // CARREGAR O RESTO DOS DADOS


    // Declaracao das listas
    ListaHospede        *listaHospede      = NULL;
    ListaReserva        *listaReserva      = NULL;
    ListaAcomodacao     *listaAcomodacao   = NULL;
    ListaCategoria      *listaCategoria    = NULL;
    ListaProduto        *listaProduto      = NULL;
    ListaNotaFiscal     *listaNotaFiscal   = NULL;
    ListaVenda          *listaVenda        = NULL;
    ListaCheckin        *listaCheckin      = NULL;
    ListaContaPagar     *listaContaPagar   = NULL;
    ListaContaReceber   *listaContaReceber = NULL;
    ListaCaixa          *listaCaixa        = NULL;
    ListaFornecedor     *listaFornecedor   = NULL;

    // Le realmente os dados
    if (hotel.TipoSalvamento == 0) {
        HospedeLerTxt(&listaHospede);
        ReservaLerTxt(&listaReserva);
        AcomodacaoLerTxt(&listaAcomodacao);
        CategoriaLerTxt(&listaCategoria);
        ProdutoLerTxt(&listaProduto);
        NotaFiscalLerTxt(&listaNotaFiscal);
        VendaLerTxt(&listaVenda);
        CheckinLerTxt(&listaCheckin);
        ContaPagarLerTxt(&listaContaPagar);
        ContaReceberLerTxt(&listaContaReceber);
        CaixaLerTxt(&listaCaixa);
        FornecedorLerTxt(&listaFornecedor);
    } else if (hotel.TipoSalvamento == 1) {
        HospedeLerBin(&listaHospede);
        ReservaLerBin(&listaReserva);
        AcomodacaoLerBin(&listaAcomodacao);
        CategoriaLerBin(&listaCategoria);
        ProdutoLerBin(&listaProduto);
        NotaFiscalLerBin(&listaNotaFiscal);
        VendaLerBin(&listaVenda);
        CheckinLerBin(&listaCheckin);
        ContaPagarLerBin(&listaContaPagar);
        ContaReceberLerBin(&listaContaReceber);
        CaixaLerBin(&listaCaixa);
        FornecedorLerBin(&listaFornecedor);
    }

    // ==================================================
    // RODA O PROGRAMA
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
                  &listaContaReceber,
                  &ListaOperador,
                  &listaCaixa,
                  &listaFornecedor);
    
    // ==================================================
    // FINALIZACAO

    // Salva os dados
    if (hotel.TipoSalvamento == 0) {
        // caso for txt
        HotelSalvar(&hotel);

        HospedeSalvarTxt(listaHospede);
        ReservaSalvarTxt(listaReserva);
        AcomodacaoSalvarTxt(listaAcomodacao);
        CategoriaSalvarTxt(listaCategoria);
        ProdutoSalvarTxt(listaProduto);
        OperadorSalvarTxt(ListaOperador);
        NotaFiscalSalvarTxt(listaNotaFiscal);
        VendaSalvarTxt(listaVenda);
        CheckinSalvarTxt(listaCheckin);
        ContaPagarSalvarTxt(listaContaPagar);
        ContaReceberSalvarTxt(listaContaReceber);
        CaixaSalvarTxt(listaCaixa);
        FornecedorSalvarTxt(listaFornecedor);
    } else if (hotel.TipoSalvamento == 1) {
        // caso for bin 
        HotelSalvar(&hotel);
        
        HospedeSalvarBin(listaHospede);
        ReservaSalvarBin(listaReserva);
        AcomodacaoSalvarBin(listaAcomodacao);
        CategoriaSalvarBin(listaCategoria);
        ProdutoSalvarBin(listaProduto);
        OperadorSalvarBin(ListaOperador);
        NotaFiscalSalvarBin(listaNotaFiscal);
        VendaSalvarBin(listaVenda);
        CheckinSalvarBin(listaCheckin);
        ContaPagarSalvarBin(listaContaPagar);
        ContaReceberSalvarBin(listaContaReceber);
        CaixaSalvarBin(listaCaixa);
        FornecedorSalvarBin(listaFornecedor);
    }

    // Apagar os arquivos q n estao de acordo
    if (hotel.TipoSalvamento == 0) {
        // Tipo TXT - Remover todos os arquivos BIN
        remove("dados/*.bin");
    } else if (hotel.TipoSalvamento == 1) {
        // Tipo BIN - Remover todos os arquivos TXT
        remove("dados/*.txt");
    } else {
        // Tipo MEM - Remover todos os arquivos TXT e BIN
        remove("dados/*.txt");
        remove("dados/*.bin");
    }


    // Libera as listas da memoria
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
    CaixaListaLiberar(listaCaixa);
    FornecedorListaLiberar(listaFornecedor);

    return 0;
}