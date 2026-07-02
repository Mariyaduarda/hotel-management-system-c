#include "../common.h"
#include "import_export_controller.h"
#include "../model/operador.h"
#include "../model/caixa.h"
#include "../model/checkin.h"
#include "../model/contas_pagar.h"
#include "../model/contas_receber.h"
#include "../model/fornecedor.h"
#include "../model/nota_fiscal.h"
#include "../model/venda.h"
#include "../model/hotel.h"
#include <stdarg.h>

#define ARQUIVO_XML_PADRAO "dados_hotel.xml"

// ============================================================
// FUNCOES AUXILIARES

void mostrarMenuXML(void) {
    // mostra o menu

    printf("\n=== IMPORTACAO / EXPORTACAO XML ===\n");
    printf("[01] Hotel\n");
    printf("[02] Operadores\n");
    printf("[03] Hospedes\n");
    printf("[04] Categorias\n");
    printf("[05] Acomodacoes\n");;
    printf("[06] Reservas\n");
    printf("[07] Produtos\n");
    printf("[08] Fornecedores\n");
    printf("[09] Caixa\n");
    printf("[10] Check-ins\n");
    printf("[11] Contas a pagar\n");
    printf("[12] Contas a receber\n");
    printf("[13] Vendas\n");
    printf("[14] Notas fiscais\n");
    printf("[15] Exportar Tudo\n");
    printf("[00] Voltar\n");
}

void pedirCaminhoXml(char *caminho, int tamanho) {
    // pede ao usuario o caminho do arquivo xml

    char entrada[300];

    ler_string("Caminho do arquivo XML (padrao ex.xml): ", entrada, sizeof(entrada));

    // se n escrever nd, usa o padrao
    if (entrada[0] == '\0')  snprintf(caminho, tamanho, "%s", ARQUIVO_XML_PADRAO);
    else                     snprintf(caminho, tamanho, "%s", entrada);
}

void lerTagTexto(char *linha, char *tag, char *destino, int tamanho) {
    // le qual e' o valor de uma certa tag e salva ela como str no destino
    // quando ta tipo: <tag>valor</tag>

    // ====================
    // Declaracao de variaveis
    char marcador[100]; // nome da tag
    char *inicio;       // ptr pro inicio do valor
    char *fim;          // ptr pro final  do valor
    int tamanhoValor;   // tamanho do valor da tag (qts chars)

    // ====================
    // confere se a linha sequer tem essa tag
    snprintf(marcador, sizeof(marcador), "<%s>", tag);
    inicio = strstr(linha, marcador);

    // se o inicio for NULL -> n tem essa tag na nessa linha -> faz nada
    if (inicio == NULL) {
        return;
    }

    // ajusta inicio e fim para ser as posicoes do valor e nao da tag
    inicio += strlen(marcador);
    fim = strstr(inicio, "</");

    // se n tem tag de fechamento n faz nd
    if (fim == NULL) {
        return;
    }

    // ====================
    // copia o valor para o destino
    tamanhoValor = fim - inicio;
    if (tamanhoValor >= tamanho) {
        // so pra n estourar o tamanho do destino
        tamanhoValor = tamanho - 1;
    }
    memcpy(destino, inicio, tamanhoValor);
    destino[tamanhoValor] = '\0'; // finaliza a str com \0 pra n dar problema
}

void lerTagInteiro(char *linha, char *tag, int *valor) {
    // le qual e' o valor de uma certa tag e salva ela como int no valor
    char texto[100];

    // le a tag como texto e converte pra numero
    lerTagTexto(linha, tag, texto, sizeof(texto));
    if (texto[0] != '\0') {
        *valor = atoi(texto);
    }
}

void lerTagFloat(char *linha, char *tag, float *valor) {
    // le qual e' o valor de uma certa tag e salva ela como float no valor
    char texto[100];

    // le a tag como texto e converte pra numero
    lerTagTexto(linha, tag, texto, sizeof(texto));
    if (texto[0] != '\0') {
        // Por algum motivo, atof retorna double, ent tem q converter pra float normal
        *valor = (float) atof(texto);
    }
}

void lerTagDouble(char *linha, char *tag, double *valor) {
    // le qual e' o valor de uma certa tag e salva ela como double no valor
    char texto[100];

    // le a tag como texto e converte pra numero
    lerTagTexto(linha, tag, texto, sizeof(texto));
    if (texto[0] != '\0') {
        *valor = atof(texto);
    }
}

char* lerArquivoTexto(char *caminho) {
    // Retorna o arquivo inteiro como str
    
    // ====================
    // abre o arquivo em modo leitura
    FILE *arquivo = fopen(caminho, "r");
    char *buffer = NULL; // buffer q vai guardar o arquivo td como str
    long tamanho;        // tamanho do arquivo em bytes(ou chars ne)

    // se n deu pra abrir o arquivo, retorna erro
    if (arquivo == NULL) {
        return NULL;
    }

    // ====================
    // vai pro final do arquivo
    if (fseek(arquivo, 0, SEEK_END) != 0) {
        fclose(arquivo);
        return NULL;
    }

    // pega o tamanho do arquivo
    tamanho = ftell(arquivo);
    // confere se ftell retornou erro
    if (tamanho < 0) {
        fclose(arquivo);
        return NULL;
    }

    // ====================
    // salva o arquivo temporario todo como string num buffer temp 
    rewind(arquivo);
    buffer = (char *) malloc((size_t) tamanho + 1);

    // se n conseuiu alocar memoria, retorna erro
    if (buffer == NULL) {
        fclose(arquivo);
        return NULL;
    }

    // le o arquivo todo e salva no buffer, confere se leu td certinho
    if (fread(buffer, 1, (size_t) tamanho, arquivo) != (size_t) tamanho) {
        // se deu erro, libera a memoria e fecha o arquivo pra n ter vazamento de memoria
        free(buffer);
        fclose(arquivo);
        return NULL;
    }

    // coloca o final no buffer
    buffer[tamanho] = '\0';

    fclose(arquivo);
    return buffer;
}

int escreverArquivoTexto(char *caminho, char *conteudo) {
    // Escreve a str 'conteudo' no arquivo 'caminho'
    // - sobrescreve td la

    FILE *arquivo = fopen(caminho, "w");
    // se n deu pra abrir o arquivo, retorna erro
    if (arquivo == NULL) {
        return 0;
    }

    // escreve o conteudo no arquivo, confere se deu erro
    if (fputs(conteudo, arquivo) == EOF) {
        fclose(arquivo);
        return 0;
    }
    fclose(arquivo);
    return 1;
}

char* criarXmlBase(void) {
    // Cria um xml base com as tags de dados e retorna isso como str

    char *base = "<dados>\n</dados>\n";
    char *base2 = (char *) malloc(strlen(base) + 1);
    if (base2 != NULL) {
        strcpy(base2, base);
    }
    return base2;
}

char *extrairTabelaDoXml(char *xml, char *nomeTabela) {
    // Extrai a tabela do xml e retorna ela como str
    char tagAbertura[128]; // nome da tag de abertura da tabela
    char *inicio;          // ponteiro para o início da tabela
    char *fim;             // ponteiro para o final da tabela
    size_t tamanho;        // tamanho da tabela extraída
    
    // antes tem q formatar a tag do jeito q ela aparace no codigo
    snprintf(tagAbertura, sizeof(tagAbertura), "<tabela nome=\"%s\">", nomeTabela);

    // ====================
    // procura no xml pela tabela com esse nome
    
    // procura o inicio e o fim da tabela no xml
    inicio = strstr(xml, tagAbertura);
    if (inicio == NULL) {
        // se n achou retorna nulo
        return NULL;
    }

    fim = strstr(inicio, "</tabela>");
    if (fim == NULL) {
        // se n achou retorna nulo
        return NULL;
    }
    // adiciona o tag de fechadura
    fim += strlen("</tabela>");

    // ====================
    // aloca a memoria do tamanho q a tabela tem
    tamanho = (size_t)(fim - inicio);
    char *saida = (char *) malloc(tamanho + 1);
    if (saida == NULL) {
        return NULL;
    }

    // copia a tabela para a memoria alocada
    memcpy(saida, inicio, tamanho);
    saida[tamanho] = '\0';
    return saida;
}

char *atualizarTabelaDoXML(char *xml, char *nomeTabela, char *novaTabelaXml) {
    // Substitui a tabela no xml, se n existir, insere ela antes do </dados>


    // ====================
    // Declaracao de variaveis
    char *xmlOrig = xml;   // xml original sem a nova atualizacao
    char *xmlNovo = NULL;  // xml novo com a nova atualizacao
    char tagAbertura[128]; // nome da tag de abertura da tabela
    char *inicioTabela;    // ptr pro inicio da tabela
    char *fimTabela;       // ptr pro final da tabela
    char *fimDados;        // ptr pro final dos dados
    size_t tamAntes;       // tamanho do conteúdo antes da tabela
    size_t tamDepois;      // tamanho do conteúdo depois da tabela
    size_t tamNovo;        // tamanho novo da tabela

    if (xmlOrig == NULL) {
        // se n tem um xml original, cria um xml base
        xmlOrig = criarXmlBase();
        if (xmlOrig == NULL) {
            // se n deu pra criar, retorna nulo
            return NULL;
        }
    }

    // ====================
    // procura a tabela no xml original
    snprintf(tagAbertura, sizeof(tagAbertura), "<tabela nome=\"%s\">", nomeTabela);
    inicioTabela = strstr(xmlOrig, tagAbertura);


    // ====================
    // Se achou um inicio de tabela
    if (inicioTabela != NULL) {
        fimTabela = strstr(inicioTabela, "</tabela>");
        if (fimTabela != NULL) {
            // se achou o fim da tabela, substitui ela

            // Calcula o tamanho do novo xml
            fimTabela += strlen("</tabela>");                           // adiciona a fechadura da tag
            tamAntes = (size_t)(inicioTabela - xmlOrig);                // calcula quantos chars tem antes da tabela
            tamDepois = strlen(fimTabela);                              // calcula quantos chars tem depois da tabela
            tamNovo = tamAntes + strlen(novaTabelaXml) + tamDepois + 1; // calcula o tamanho do novo xml
            
            // aloca ele na maemoria
            xmlNovo = (char *) malloc(tamNovo);
            if (xmlNovo == NULL) {
                // se n deu pra alocar, retorna nulo
                return NULL;
            }

            // se alocou, copia o conteudo do xml antigo e insere a nova tabela
            if (xmlNovo != NULL) {
                memcpy(xmlNovo, xmlOrig, tamAntes);
                memcpy(xmlNovo + tamAntes, novaTabelaXml, strlen(novaTabelaXml));
                memcpy(xmlNovo + tamAntes + strlen(novaTabelaXml), fimTabela, tamDepois + 1);
            }
            
            // se o xml foi criado aqui e n veio de fora, libera a memoria dele
            if (xml != xmlOrig) {
                free((void *) xmlOrig);
            }

            // retorna o novo xml com a tabela substituida
            return xmlNovo;
        }
    }

    // ====================
    // se n achou a tabela, ai tem q inserir ela
    
    // vai ate' o final pra poder inserir a nova tabela antes do </dados>
    fimDados = strstr(xmlOrig, "</dados>"); 
    
    // se n achou o final dos dados, retorna nulo
    if (fimDados == NULL) {
        return NULL;
    }

    // Calcula o tamanho do novo xml
    tamAntes = (size_t)(fimDados - xmlOrig);                    // tamanho antes da tabela
    tamDepois = strlen(fimDados);                               // tamanho dps   da tabela
    tamNovo = tamAntes + strlen(novaTabelaXml) + tamDepois + 1; // tamanho do novo xml com a nova tabela

    // aloca espaco pro novo xml
    xmlNovo = (char *) malloc(tamNovo);
    if (xmlNovo == NULL) {
        // se n deu pra alocar, retorna nulo
        return NULL;
    }

    // copia o conteudo do xml antigo e insere a nova tabela
    if (xmlNovo != NULL) {
        memcpy(xmlNovo, xmlOrig, tamAntes);                                          // copia o conteudo antes da tabela
        memcpy(xmlNovo + tamAntes, novaTabelaXml, strlen(novaTabelaXml));            // copia a nova tabela
        memcpy(xmlNovo + tamAntes + strlen(novaTabelaXml), fimDados, tamDepois + 1); // copia o conteudo dps da tabela
    }

    // se o xml foi criado aqui e n veio de fora, libera a memoria dele
    if (xml != xmlOrig) {
        free((void *) xmlOrig);
    }
    return xmlNovo;
}

void atualizarTabelaNoArquivo(char *caminho, char *nomeTabela, char *conteudoXml) {
    // atualiza a tabela no arquivo xml, se n existir, cria

    // ====================
    // converte a tabela do xml em string
    char *tabela = extrairTabelaDoXml(conteudoXml, nomeTabela);
    if (tabela == NULL) {
        printf("\n [ERRO] \n Não foi possivel alocar memoria para a tabela \n");
        return;
    }

    // ====================
    // ler o arquivo inteiro, substitui a tabela e escreve de volta
    char *xmlAtual = lerArquivoTexto(caminho);
    char *xmlNovo = atualizarTabelaDoXML(xmlAtual, nomeTabela, tabela);
    free(xmlAtual);
    free(tabela);

    // se n deu pra alocar memoria pro xml novo, retorna erro
    if (xmlNovo == NULL) {
        printf("\n [ERRO] \n Não foi possivel alocar memoria para o xml novo \n");
        return;
    }

    // escreve a str inteira do novo xml no arquivo
    escreverArquivoTexto(caminho, xmlNovo);
    free(xmlNovo);
}

int verificarLinhaTabela(char *linha, char *nomeTabela, int *dentroTabela) {
    // so' confere se a linha atual do arquivo xml ta dentro da tabela q eu quero, se ta fora ou se ja acabou a tabela
    // -1 = acabou a tabela
    //  0 = ta fora da tabela
    //  1 = ta dentro da tabela
    
    // nome da tag de abertura da tabela
    char tagAbertura[128]; 
    // formata ela do jeito q ela aparece no xml
    snprintf(tagAbertura, sizeof(tagAbertura), "<tabela nome=\"%s\">", nomeTabela);

    // se n ta dentro da tabela, pd ser q a linha atual e' a abertura da tabela
    if (!*dentroTabela) {
        if (strstr(linha, tagAbertura) != NULL) {
            *dentroTabela = 1;
        }
        return 0;
    }

    // se ta dentro da tabela, confere se a linha atual eh o fechamento da tabela
    if (strstr(linha, "</tabela>") != NULL) {
        *dentroTabela = 0;
        return -1;
    } else {
        // se ta dentro e n e' o fechamento, so' ta dentro
        return 1;
    }
}

void salvarTabelaTempNoArquivo(char *caminho, char *nomeTabela, FILE *arquivoTemp) {
    // salva a tabela q ta no arquivo temporario no arquivo final

    char *buffer = NULL; // buffer temp pra guardar a tabela
    long tamanho;        // tamanho do arq temp

    // se n deu pra abrir o arquivo, retorna erro
    if (arquivoTemp == NULL) {
        printf("\n [ERRO] \n Não foi possivel abrir o arquivo \n");
        exit(1);
    }

    // fflush pra ter ctz q n ficou nd no buffer 
    fflush(arquivoTemp);

    // vai pro final do arquivo
    if (fseek(arquivoTemp, 0, SEEK_END) == 0) {
        // pega o tamanho do arquivo temporario
        tamanho = ftell(arquivoTemp);

        // se o tamanho for valido
        if (tamanho >= 0) {
            // coloca o arquivo td em formato de str no buffer
            rewind(arquivoTemp);
            buffer = (char *) malloc((size_t) tamanho + 1);

            // confere se alocou certinho
            if(buffer == NULL){
                printf("\n [ERRO] \n Não foi possivel alocar memoria para o buffer \n");
                exit(1);
            }

            // confere se o tamanho ta certo
            if (fread(buffer, 1, (size_t) tamanho, arquivoTemp) == (size_t) tamanho) {
                // se estiver, manda atualizar a tabela no arquivo realmente
                buffer[tamanho] = '\0';
                atualizarTabelaNoArquivo(caminho, nomeTabela, buffer);
            }
        }
    }

    free(buffer);
}


// ============================================================
// ESPORTACAO E IMPORTACAO

// Hotel

void ExportarHotelXml(Hotel *hotel, char *caminho) {
    // Declaracaro de variaveis
    FILE *arquivo = tmpfile();

    // se n deu pra abrir o arquivo, retorna erro
    if (arquivo == NULL) {
        printf("Erro ao abrir o arquivo temporario para exportacao.\n");
        return;
    }

    // cria o arquivo temporario com os dados certos
    fprintf(arquivo, "  <tabela nome=\"hotel\">\n");
    fprintf(arquivo, "    <registro>\n");
    fprintf(arquivo, "      <nome_fantasia>%s</nome_fantasia>\n", hotel->NomeFantasia);
    fprintf(arquivo, "      <razao_social>%s</razao_social>\n", hotel->RazaoSocial);
    fprintf(arquivo, "      <inscricao_estadual>%s</inscricao_estadual>\n", hotel->InscricaoEstadual);
    fprintf(arquivo, "      <cnpj>%s</cnpj>\n", hotel->CNPJ);
    fprintf(arquivo, "      <email>%s</email>\n", hotel->Email);
    fprintf(arquivo, "      <nome_responsavel>%s</nome_responsavel>\n", hotel->NomeResp);
    fprintf(arquivo, "      <telefone_responsavel>%s</telefone_responsavel>\n", hotel->TelefoneResp);
    fprintf(arquivo, "      <telefone>%s</telefone>\n", hotel->Telefone);
    fprintf(arquivo, "      <checkin>%s</checkin>\n", hotel->CheckIn);
    fprintf(arquivo, "      <checkout>%s</checkout>\n", hotel->CheckOut);
    fprintf(arquivo, "      <margem_lucro>%.2f</margem_lucro>\n", hotel->MargemLucro);
    fprintf(arquivo, "      <tipo_salvamento>%d</tipo_salvamento>\n", hotel->TipoSalvamento);
    fprintf(arquivo, "      <ativo>%d</ativo>\n", hotel->ativo);
    fprintf(arquivo, "      <endereco>\n");
    fprintf(arquivo, "        <rua>%s</rua>\n", hotel->endereco.rua);
    fprintf(arquivo, "        <numero>%s</numero>\n", hotel->endereco.numero);
    fprintf(arquivo, "        <complemento>%s</complemento>\n", hotel->endereco.complemento);
    fprintf(arquivo, "        <bairro>%s</bairro>\n", hotel->endereco.bairro);
    fprintf(arquivo, "        <cidade>%s</cidade>\n", hotel->endereco.cidade);
    fprintf(arquivo, "        <estado>%s</estado>\n", hotel->endereco.estado);
    fprintf(arquivo, "        <cep>%s</cep>\n", hotel->endereco.cep);
    fprintf(arquivo, "      </endereco>\n");
    fprintf(arquivo, "    </registro>\n");
    fprintf(arquivo, "  </tabela>\n");

    // funcao q vai salvar a tabela temporaria no arquivo final
    // AINDA TEM Q IMPLEMENTAR ================================================
    salvarTabelaTempNoArquivo(caminho, "hotel", arquivo);
    fclose(arquivo);
}

void ImportarHotelXml(Hotel *hotel, char *caminho) {
    FILE *arquivo = fopen(caminho, "r");
    char linha[500];
    int dentroTabela = 0;

    // se n deu pra abrir o arquivo, retorna erro
    if (arquivo == NULL) {
        printf("Erro ao abrir o arquivo para importacao.\n");
        return;
    }

    HotelInit(hotel);

    // le o xml linha por linha
    while (fgets(linha, sizeof(linha), arquivo) != NULL) {
        // Confere o status da linha atual
        // ( 0) se n ta dentro da tabela, ignora
        // ( 1) se ta dentro da tabela, le os dados
        // (-1) se acabou a tabela, termina
        int status = verificarLinhaTabela(linha, "hotel", &dentroTabela);
        if (status == 0) {
            continue;
        }
        if (status == -1) {
            break;
        }

        lerTagTexto(linha, "nome_fantasia", hotel->NomeFantasia, sizeof(hotel->NomeFantasia));
        lerTagTexto(linha, "razao_social", hotel->RazaoSocial, sizeof(hotel->RazaoSocial));
        lerTagTexto(linha, "inscricao_estadual", hotel->InscricaoEstadual, sizeof(hotel->InscricaoEstadual));
        lerTagTexto(linha, "cnpj", hotel->CNPJ, sizeof(hotel->CNPJ));
        lerTagTexto(linha, "email", hotel->Email, sizeof(hotel->Email));
        lerTagTexto(linha, "nome_responsavel", hotel->NomeResp, sizeof(hotel->NomeResp));
        lerTagTexto(linha, "telefone_responsavel", hotel->TelefoneResp, sizeof(hotel->TelefoneResp));
        lerTagTexto(linha, "telefone", hotel->Telefone, sizeof(hotel->Telefone));
        lerTagTexto(linha, "checkin", hotel->CheckIn, sizeof(hotel->CheckIn));
        lerTagTexto(linha, "checkout", hotel->CheckOut, sizeof(hotel->CheckOut));
        lerTagDouble(linha, "margem_lucro", &hotel->MargemLucro);
        lerTagInteiro(linha, "tipo_salvamento", &hotel->TipoSalvamento);
        lerTagInteiro(linha, "ativo", &hotel->ativo);
        lerTagTexto(linha, "rua", hotel->endereco.rua, sizeof(hotel->endereco.rua));
        lerTagTexto(linha, "numero", hotel->endereco.numero, sizeof(hotel->endereco.numero));
        lerTagTexto(linha, "complemento", hotel->endereco.complemento, sizeof(hotel->endereco.complemento));
        lerTagTexto(linha, "bairro", hotel->endereco.bairro, sizeof(hotel->endereco.bairro));
        lerTagTexto(linha, "cidade", hotel->endereco.cidade, sizeof(hotel->endereco.cidade));
        lerTagTexto(linha, "estado", hotel->endereco.estado, sizeof(hotel->endereco.estado));
        lerTagTexto(linha, "cep", hotel->endereco.cep, sizeof(hotel->endereco.cep));
    }

    fclose(arquivo);
}

// Operador

void ExportarOperadorXml(ListaOperador *lista, char *caminho) {
    // Declaracaro de variaveis
    FILE *arquivo = tmpfile();
    ListaOperador *atual;      // aux pra percorrer a lista

    // se n deu pra abrir o arquivo, retorna erro
    if (arquivo == NULL) {
        printf("Erro ao abrir o arquivo temporario para exportacao.\n");
        return;
    }

    // cria o arquivo temporario com os dados certos
    fprintf(arquivo, "  <tabela nome=\"operador\">\n");
    for (atual = lista; atual != NULL; atual = atual->proximo) {
        fprintf(arquivo, "    <registro>\n");
        fprintf(arquivo, "      <id>%d</id>\n", atual->operador.id);
        fprintf(arquivo, "      <nome>%s</nome>\n", atual->operador.nome);
        fprintf(arquivo, "      <usuario>%s</usuario>\n", atual->operador.usuario);
        fprintf(arquivo, "      <senha>%s</senha>\n", atual->operador.senha);
        fprintf(arquivo, "      <permissoes>%d</permissoes>\n", atual->operador.permissoes);
        fprintf(arquivo, "      <ativo>%d</ativo>\n", atual->operador.ativo);
        fprintf(arquivo, "    </registro>\n");
    }
    fprintf(arquivo, "  </tabela>\n");

    // funcao q vai salvar a tabela temporaria no arquivo final
    // AINDA TEM Q IMPLEMENTAR ================================================
    salvarTabelaTempNoArquivo(caminho, "operador", arquivo);
    fclose(arquivo);
}

void ImportarOperadorXml(ListaOperador **lista, char *caminho) {
    FILE *arquivo = fopen(caminho, "r");
    char linha[500];
    ListaOperador *novo;
    Operador operador;
    int lendo_reg = 0;
    int dentroTabela = 0;

    // se n deu pra abrir o arquivo, retorna erro
    if (arquivo == NULL) {
        printf("Erro ao abrir o arquivo para importacao.\n");
        return;
    }

    // se a lista n ta vazia, libera os elementos tds pra comecar do zero
    if (*lista != NULL) {
        OperadorListaLiberar(*lista);
        *lista = NULL;
    }

    // limpa o operador pra n ter lixo de memoria
    OperadorInit(&operador);

    // le o xml linha por linha
    while (fgets(linha, sizeof(linha), arquivo) != NULL) {
        // Confere o status da linha atual
        // ( 0) se n ta dentro da tabela, ignora
        // ( 1) se ta dentro da tabela, le os dados
        // (-1) se acabou a tabela, termina
        int status = verificarLinhaTabela(linha, "operador", &dentroTabela);
        if (status == 0) {
            continue;
        }
        if (status == -1) {
            break;
        }

        if (strstr(linha, "<registro>") != NULL) {
            lendo_reg = 1;
            OperadorInit(&operador);
            continue;
        }

        if (lendo_reg && strstr(linha, "</registro>") != NULL) {
            novo = (ListaOperador *) malloc(sizeof(ListaOperador));

            if (novo != NULL) {
                novo->operador = operador;
                novo->proximo = *lista;
                *lista = novo;
            }
            lendo_reg = 0;
            continue;
        }

        if (!lendo_reg) {
            continue;
        }

        lerTagInteiro(linha, "id", &operador.id);
        lerTagTexto(linha, "nome", operador.nome, sizeof(operador.nome));
        lerTagTexto(linha, "usuario", operador.usuario, sizeof(operador.usuario));
        lerTagTexto(linha, "senha", operador.senha, sizeof(operador.senha));
        lerTagInteiro(linha, "permissoes", &operador.permissoes);
        lerTagInteiro(linha, "ativo", &operador.ativo);
    }

    fclose(arquivo);
}

// Hospede

void ExportarHospedeXml(ListaHospede *lista, char *caminho) {
    // Declaracaro de variaveis
    FILE *arquivo = tmpfile();
    ListaHospede *atual; // aux pra percorrer a lista

    // se n deu pra abrir o arquivo, retorna erro
    if (arquivo == NULL) {
        printf("Erro ao abrir o arquivo temporario para exportacao.\n");
        return;
    }

    // cria o arquivo temporario com os dados certos
    fprintf(arquivo, "  <tabela nome=\"hospede\">\n");
    for (atual = lista; atual != NULL; atual = atual->proximo) {
        fprintf(arquivo, "    <registro>\n");
        fprintf(arquivo, "      <id>%d</id>\n", atual->hospede.id);
        fprintf(arquivo, "      <nome>%s</nome>\n", atual->hospede.nome);
        fprintf(arquivo, "      <cpf>%s</cpf>\n", atual->hospede.cpf);
        fprintf(arquivo, "      <email>%s</email>\n", atual->hospede.email);
        fprintf(arquivo, "      <telefone>%s</telefone>\n", atual->hospede.telefone);
        fprintf(arquivo, "      <sexo>%s</sexo>\n", atual->hospede.sexo);
        fprintf(arquivo, "      <data_nascimento>%s</data_nascimento>\n", atual->hospede.dataNascimento);
        fprintf(arquivo, "      <estado_civil>%s</estado_civil>\n", atual->hospede.estadoCivil);
        fprintf(arquivo, "      <ativo>%d</ativo>\n", atual->hospede.ativo);
        fprintf(arquivo, "      <endereco>\n");
        fprintf(arquivo, "        <rua>%s</rua>\n", atual->hospede.endereco.rua);
        fprintf(arquivo, "        <numero>%s</numero>\n", atual->hospede.endereco.numero);
        fprintf(arquivo, "        <complemento>%s</complemento>\n", atual->hospede.endereco.complemento);
        fprintf(arquivo, "        <bairro>%s</bairro>\n", atual->hospede.endereco.bairro);
        fprintf(arquivo, "        <cidade>%s</cidade>\n", atual->hospede.endereco.cidade);
        fprintf(arquivo, "        <estado>%s</estado>\n", atual->hospede.endereco.estado);
        fprintf(arquivo, "        <cep>%s</cep>\n", atual->hospede.endereco.cep);
        fprintf(arquivo, "      </endereco>\n");
        fprintf(arquivo, "    </registro>\n");
    }
    fprintf(arquivo, "  </tabela>\n");
    
    // funcao q vai salvar a tabela temporaria no arquivo final
    // AINDA TEM Q IMPLEMENTAR ================================================
    salvarTabelaTempNoArquivo(caminho, "hospede", arquivo);
    fclose(arquivo);
}

void ImportarHospedeXml(ListaHospede **lista, char *caminho) {
    FILE *arquivo = fopen(caminho, "r");
    char linha[500];
    TipoHospede hospede;
    ListaHospede *novo;
    int lendo_reg = 0;
    int dentroTabela = 0;

    // se n deu pra abrir o arquivo, retorna erro
    if (arquivo == NULL) {
        printf("Erro ao abrir o arquivo para importacao.\n");
        return;
    }

    if (*lista != NULL) {
        HospedeListaLiberar(*lista);
        *lista = NULL;
    }

    // limpa o operador pra n ter lixo de memoria
    HospedeInit(&hospede);

    // le o xml linha por linha
    while (fgets(linha, sizeof(linha), arquivo) != NULL) {
        // Confere o status da linha atual
        // ( 0) se n ta dentro da tabela, ignora
        // ( 1) se ta dentro da tabela, le os dados
        // (-1) se acabou a tabela, termina
        int status = verificarLinhaTabela(linha, "hospede", &dentroTabela);
        if (status == 0) {
            continue;
        }
        if (status == -1) {
            break;
        }

        if (strstr(linha, "<registro>") != NULL) {
            lendo_reg = 1;
            HospedeInit(&hospede);
            continue;
        }

        if (lendo_reg && strstr(linha, "</registro>") != NULL) {
            novo = (ListaHospede *) malloc(sizeof(ListaHospede));
            if (novo != NULL) {
                novo->hospede = hospede;
                novo->proximo = *lista;
                *lista = novo;
            }
            lendo_reg = 0;
            continue;
        }

        if (!lendo_reg) {
            continue;
        }

        lerTagInteiro(linha, "id", &hospede.id);
        lerTagTexto(linha, "nome", hospede.nome, sizeof(hospede.nome));
        lerTagTexto(linha, "cpf", hospede.cpf, sizeof(hospede.cpf));
        lerTagTexto(linha, "email", hospede.email, sizeof(hospede.email));
        lerTagTexto(linha, "telefone", hospede.telefone, sizeof(hospede.telefone));
        lerTagTexto(linha, "sexo", hospede.sexo, sizeof(hospede.sexo));
        lerTagTexto(linha, "data_nascimento", hospede.dataNascimento, sizeof(hospede.dataNascimento));
        lerTagTexto(linha, "estado_civil", hospede.estadoCivil, sizeof(hospede.estadoCivil));
        lerTagInteiro(linha, "ativo", &hospede.ativo);
        lerTagTexto(linha, "rua", hospede.endereco.rua, sizeof(hospede.endereco.rua));
        lerTagTexto(linha, "numero", hospede.endereco.numero, sizeof(hospede.endereco.numero));
        lerTagTexto(linha, "complemento", hospede.endereco.complemento, sizeof(hospede.endereco.complemento));
        lerTagTexto(linha, "bairro", hospede.endereco.bairro, sizeof(hospede.endereco.bairro));
        lerTagTexto(linha, "cidade", hospede.endereco.cidade, sizeof(hospede.endereco.cidade));
        lerTagTexto(linha, "estado", hospede.endereco.estado, sizeof(hospede.endereco.estado));
        lerTagTexto(linha, "cep", hospede.endereco.cep, sizeof(hospede.endereco.cep));
    }

    fclose(arquivo);
}

// Categoria

void ExportarCategoriaXml(ListaCategoria *lista, char *caminho) {
    // Declaracaro de variaveis
    FILE *arquivo = tmpfile();
    ListaCategoria *atual; // aux pra percorrer a lista

    // se n deu pra abrir o arquivo, retorna erro
    if (arquivo == NULL) {
        printf("Erro ao abrir o arquivo temporario para exportacao.\n");
        return;
    }

    // cria o arquivo temporario com os dados certos
    fprintf(arquivo, "  <tabela nome=\"categoria\">\n");

    for (atual = lista; atual != NULL; atual = atual->proximo) {
        fprintf(arquivo, "    <registro>\n");
        fprintf(arquivo, "      <id>%d</id>\n", atual->categoria.id);
        fprintf(arquivo, "      <descricao>%s</descricao>\n", atual->categoria.descricao);
        fprintf(arquivo, "      <valor_diaria>%.2f</valor_diaria>\n", atual->categoria.valorDiaria);
        fprintf(arquivo, "      <max_adultos>%d</max_adultos>\n", atual->categoria.maxAdultos);
        fprintf(arquivo, "      <max_criancas>%d</max_criancas>\n", atual->categoria.maxCriancas);
        fprintf(arquivo, "      <ativo>%d</ativo>\n", atual->categoria.ativo);
        fprintf(arquivo, "    </registro>\n");
    }
    fprintf(arquivo, "  </tabela>\n");

    // funcao q vai salvar a tabela temporaria no arquivo final
    // AINDA TEM Q IMPLEMENTAR ================================================
    salvarTabelaTempNoArquivo(caminho, "categoria", arquivo);
    fclose(arquivo);
}

void ImportarCategoriaXml(ListaCategoria **lista, char *caminho) {
    FILE *arquivo = fopen(caminho, "r");
    char linha[500];
    TipoCategoria categoria;
    ListaCategoria *novo;
    int lendo_reg = 0;
    int dentroTabela = 0;

    // se n deu pra abrir o arquivo, retorna erro
    if (arquivo == NULL) {
        printf("Erro ao abrir o arquivo para importacao.\n");
        return;
    }

    if (*lista != NULL) {
        CategoriaListaLiberar(*lista);
        *lista = NULL;
    }
    
    // limpa o operador pra n ter lixo de memoria
    CategoriasInit(&categoria);

    // le o xml linha por linha
    while (fgets(linha, sizeof(linha), arquivo) != NULL) {
        // Confere o status da linha atual
        // ( 0) se n ta dentro da tabela, ignora
        // ( 1) se ta dentro da tabela, le os dados
        // (-1) se acabou a tabela, termina
        int status = verificarLinhaTabela(linha, "categoria", &dentroTabela);
        if (status == 0) {
            continue;
        }
        if (status == -1) {
            break;
        }

        if (strstr(linha, "<registro>") != NULL) {
            lendo_reg = 1;
            CategoriasInit(&categoria);
            continue;
        }

        if (lendo_reg && strstr(linha, "</registro>") != NULL) {
            novo = (ListaCategoria *) malloc(sizeof(ListaCategoria));
            if (novo != NULL) {
                novo->categoria = categoria;
                novo->proximo = *lista;
                *lista = novo;
            }
            lendo_reg = 0;
            continue;
        }

        if (!lendo_reg) {
            continue;
        }

        lerTagInteiro(linha, "id", &categoria.id);
        lerTagTexto(linha, "descricao", categoria.descricao, sizeof(categoria.descricao));
        lerTagFloat(linha, "valor_diaria", &categoria.valorDiaria);
        lerTagInteiro(linha, "max_adultos", &categoria.maxAdultos);
        lerTagInteiro(linha, "max_criancas", &categoria.maxCriancas);
        lerTagInteiro(linha, "ativo", &categoria.ativo);
    }

    fclose(arquivo);
}

// Acomodacao

void ExportarAcomodacaoXml(ListaAcomodacao *lista, char *caminho) {
    // Declaracaro de variaveis
    FILE *arquivo = tmpfile();
    ListaAcomodacao *atual; // aux pra percorrer a lista

    // se n deu pra abrir o arquivo, retorna erro
    if (arquivo == NULL) {
        printf("Erro ao abrir o arquivo temporario para exportacao.\n");
        return;
    }

    // cria o arquivo temporario com os dados certos
    fprintf(arquivo, "  <tabela nome=\"acomodacao\">\n");
    for (atual = lista; atual != NULL; atual = atual->proximo) {
        fprintf(arquivo, "    <registro>\n");
        fprintf(arquivo, "      <id>%d</id>\n", atual->acomodacao.id);
        fprintf(arquivo, "      <id_categoria>%d</id_categoria>\n", atual->acomodacao.idCategoria);
        fprintf(arquivo, "      <descricao>%s</descricao>\n", atual->acomodacao.descricao);
        fprintf(arquivo, "      <facilidades>%s</facilidades>\n", atual->acomodacao.facilidades);
        fprintf(arquivo, "      <ativo>%d</ativo>\n", atual->acomodacao.ativo);
        fprintf(arquivo, "    </registro>\n");
    }
    fprintf(arquivo, "  </tabela>\n");
    
    // funcao q vai salvar a tabela temporaria no arquivo final
    // AINDA TEM Q IMPLEMENTAR ================================================
    salvarTabelaTempNoArquivo(caminho, "acomodacao", arquivo);
    fclose(arquivo);
}

void ImportarAcomodacaoXml(ListaAcomodacao **lista, char *caminho) {
    FILE *arquivo = fopen(caminho, "r");
    char linha[500];
    TipoAcomodacao acomodacao;
    ListaAcomodacao *novo;
    int lendo_reg = 0;
    int dentroTabela = 0;

    // se n deu pra abrir o arquivo, retorna erro
    if (arquivo == NULL) {
        printf("Erro ao abrir o arquivo para importacao.\n");
        return;
    }

    if (*lista != NULL) {
        AcomodacaoListaLiberar(*lista);
        *lista = NULL;
    }
    
    // limpa o operador pra n ter lixo de memoria
    AcomodacaoInit(&acomodacao);

    // le o xml linha por linha
    while (fgets(linha, sizeof(linha), arquivo) != NULL) {
        // Confere o status da linha atual
        // ( 0) se n ta dentro da tabela, ignora
        // ( 1) se ta dentro da tabela, le os dados
        // (-1) se acabou a tabela, termina
        int status = verificarLinhaTabela(linha, "acomodacao", &dentroTabela);
        if (status == 0) {
            continue;
        }
        if (status == -1) {
            break;
        }

        if (strstr(linha, "<registro>") != NULL) {
            lendo_reg = 1;
            AcomodacaoInit(&acomodacao);
            continue;
        }

        if (lendo_reg && strstr(linha, "</registro>") != NULL) {
            novo = (ListaAcomodacao *) malloc(sizeof(ListaAcomodacao));
            if (novo != NULL) {
                novo->acomodacao = acomodacao;
                novo->proximo = *lista;
                *lista = novo;
            }
            lendo_reg = 0;
            continue;
        }

        if (!lendo_reg) {
            continue;
        }

        lerTagInteiro(linha, "id", &acomodacao.id);
        lerTagInteiro(linha, "id_categoria", &acomodacao.idCategoria);
        lerTagTexto(linha, "descricao", acomodacao.descricao, sizeof(acomodacao.descricao));
        lerTagTexto(linha, "facilidades", acomodacao.facilidades, sizeof(acomodacao.facilidades));
        lerTagInteiro(linha, "ativo", &acomodacao.ativo);
    }

    fclose(arquivo);
}

// Reserva

void ExportarReservaXml(ListaReserva *lista, char *caminho) {
    // Declaracaro de variaveis
    FILE *arquivo = tmpfile();
    ListaReserva *atual; // aux pra percorrer a lista

    // se n deu pra abrir o arquivo, retorna erro
    if (arquivo == NULL) {
        printf("Erro ao abrir o arquivo temporario para exportacao.\n");
        return;
    }

    // cria o arquivo temporario com os dados certos
    fprintf(arquivo, "  <tabela nome=\"reserva\">\n");
    for (atual = lista; atual != NULL; atual = atual->proximo) {
        fprintf(arquivo, "    <registro>\n");
        fprintf(arquivo, "      <id>%d</id>\n", atual->reserva.id);
        fprintf(arquivo, "      <id_hospede>%d</id_hospede>\n", atual->reserva.idHospede);
        fprintf(arquivo, "      <id_acomodacao>%d</id_acomodacao>\n", atual->reserva.idAcomodacao);
        fprintf(arquivo, "      <data_entrada>%s</data_entrada>\n", atual->reserva.dataEntrada);
        fprintf(arquivo, "      <data_saida>%s</data_saida>\n", atual->reserva.dataSaida);
        fprintf(arquivo, "      <num_adultos>%d</num_adultos>\n", atual->reserva.numAdultos);
        fprintf(arquivo, "      <num_criancas>%d</num_criancas>\n", atual->reserva.numCriancas);
        fprintf(arquivo, "      <pagar_na_entrada>%d</pagar_na_entrada>\n", atual->reserva.pagarNaEntrada);
        fprintf(arquivo, "      <status>%d</status>\n", atual->reserva.status);
        fprintf(arquivo, "      <total_diarias>%.2f</total_diarias>\n", atual->reserva.totalDiarias);
        fprintf(arquivo, "    </registro>\n");
    }
    fprintf(arquivo, "  </tabela>\n");
    
    // funcao q vai salvar a tabela temporaria no arquivo final
    // AINDA TEM Q IMPLEMENTAR ================================================
    salvarTabelaTempNoArquivo(caminho, "reserva", arquivo);
    fclose(arquivo);
}

void ImportarReservaXml(ListaReserva **lista, char *caminho) {
    FILE *arquivo = fopen(caminho, "r");
    char linha[500];
    TipoReserva reserva;
    ListaReserva *novo;
    int lendo_reg = 0;
    int dentroTabela = 0;

    // se n deu pra abrir o arquivo, retorna erro
    if (arquivo == NULL) {
        printf("Erro ao abrir o arquivo para importacao.\n");
        return;
    }

    if (*lista != NULL) {
        ReservaListaLiberar(*lista);
        *lista = NULL;
    }
    
    // limpa o operador pra n ter lixo de memoria
    ReservaInit(&reserva);

    // le o xml linha por linha
    while (fgets(linha, sizeof(linha), arquivo) != NULL) {
        // Confere o status da linha atual
        // ( 0) se n ta dentro da tabela, ignora
        // ( 1) se ta dentro da tabela, le os dados
        // (-1) se acabou a tabela, termina
        int status = verificarLinhaTabela(linha, "reserva", &dentroTabela);
        if (status == 0) {
            continue;
        }
        if (status == -1) {
            break;
        }

        if (strstr(linha, "<registro>") != NULL) {
            lendo_reg = 1;
            ReservaInit(&reserva);
            continue;
        }

        if (lendo_reg && strstr(linha, "</registro>") != NULL) {
            novo = (ListaReserva *) malloc(sizeof(ListaReserva));
            if (novo != NULL) {
                novo->reserva = reserva;
                novo->proximo = *lista;
                *lista = novo;
            }
            lendo_reg = 0;
            continue;
        }

        if (!lendo_reg) {
            continue;
        }

        lerTagInteiro(linha, "id", &reserva.id);
        lerTagInteiro(linha, "id_hospede", &reserva.idHospede);
        lerTagInteiro(linha, "id_acomodacao", &reserva.idAcomodacao);
        lerTagTexto(linha, "data_entrada", reserva.dataEntrada, sizeof(reserva.dataEntrada));
        lerTagTexto(linha, "data_saida", reserva.dataSaida, sizeof(reserva.dataSaida));
        lerTagInteiro(linha, "num_adultos", &reserva.numAdultos);
        lerTagInteiro(linha, "num_criancas", &reserva.numCriancas);
        lerTagInteiro(linha, "pagar_na_entrada", &reserva.pagarNaEntrada);
        lerTagInteiro(linha, "status", &reserva.status);
        lerTagFloat(linha, "total_diarias", &reserva.totalDiarias);
    }

    fclose(arquivo);
}

// Produto

void ExportarProdutoXml(ListaProduto *lista, char *caminho) {
    // Declaracaro de variaveis
    FILE *arquivo = tmpfile();
    ListaProduto *atual; // aux pra percorrer a lista

    // se n deu pra abrir o arquivo, retorna erro
    if (arquivo == NULL) {
        printf("Erro ao abrir o arquivo temporario para exportacao.\n");
        return;
    }

    // cria o arquivo temporario com os dados certos
    fprintf(arquivo, "  <tabela nome=\"produto\">\n");
    for (atual = lista; atual != NULL; atual = atual->proximo) {
        fprintf(arquivo, "    <registro>\n");
        fprintf(arquivo, "      <id>%d</id>\n", atual->produto.id);
        fprintf(arquivo, "      <descricao>%s</descricao>\n", atual->produto.descricao);
        fprintf(arquivo, "      <estoque>%d</estoque>\n", atual->produto.estoque);
        fprintf(arquivo, "      <estoque_minimo>%d</estoque_minimo>\n", atual->produto.estoqueMinimo);
        fprintf(arquivo, "      <preco_custo>%.2f</preco_custo>\n", atual->produto.precoCusto);
        fprintf(arquivo, "      <preco_venda>%.2f</preco_venda>\n", atual->produto.precoVenda);
        fprintf(arquivo, "      <ativo>%d</ativo>\n", atual->produto.ativo);
        fprintf(arquivo, "    </registro>\n");
    }
    fprintf(arquivo, "  </tabela>\n");
    
    // funcao q vai salvar a tabela temporaria no arquivo final
    // AINDA TEM Q IMPLEMENTAR ================================================
    salvarTabelaTempNoArquivo(caminho, "produto", arquivo);
    fclose(arquivo);
}

void ImportarProdutoXml(ListaProduto **lista, char *caminho) {
    FILE *arquivo = fopen(caminho, "r");
    char linha[500];
    TipoProduto produto;
    ListaProduto *novo;
    int lendo_reg = 0;
    int dentroTabela = 0;

    // se n deu pra abrir o arquivo, retorna erro
    if (arquivo == NULL) {
        printf("Erro ao abrir o arquivo para importacao.\n");
        return;
    }

    if (*lista != NULL) {
        ProdutoListaLiberar(*lista);
        *lista = NULL;
    }
    
    // limpa o operador pra n ter lixo de memoria
    ProdutoInit(&produto);

    // le o xml linha por linha
    while (fgets(linha, sizeof(linha), arquivo) != NULL) {
        // Confere o status da linha atual
        // ( 0) se n ta dentro da tabela, ignora
        // ( 1) se ta dentro da tabela, le os dados
        // (-1) se acabou a tabela, termina
        int status = verificarLinhaTabela(linha, "produto", &dentroTabela);
        if (status == 0) {
            continue;
        }
        if (status == -1) {
            break;
        }

        if (strstr(linha, "<registro>") != NULL) {
            lendo_reg = 1;
            ProdutoInit(&produto);
            continue;
        }

        if (lendo_reg && strstr(linha, "</registro>") != NULL) {
            novo = (ListaProduto *) malloc(sizeof(ListaProduto));
            if (novo != NULL) {
                novo->produto = produto;
                novo->proximo = *lista;
                *lista = novo;
            }
            lendo_reg = 0;
            continue;
        }

        if (!lendo_reg) {
            continue;
        }

        lerTagInteiro(linha, "id", &produto.id);
        lerTagTexto(linha, "descricao", produto.descricao, sizeof(produto.descricao));
        lerTagInteiro(linha, "estoque", &produto.estoque);
        lerTagInteiro(linha, "estoque_minimo", &produto.estoqueMinimo);
        lerTagFloat(linha, "preco_custo", &produto.precoCusto);
        lerTagFloat(linha, "preco_venda", &produto.precoVenda);
        lerTagInteiro(linha, "ativo", &produto.ativo);
    }

    fclose(arquivo);
}

// Fornecedor

void ExportarFornecedorXml(ListaFornecedor *lista, char *caminho) {
    // Declaracaro de variaveis
    FILE *arquivo = tmpfile();
    ListaFornecedor *atual; // aux pra percorrer a lista

    // se n deu pra abrir o arquivo, retorna erro
    if (arquivo == NULL) {
        printf("Erro ao abrir o arquivo temporario para exportacao.\n");
        return;
    }

    // cria o arquivo temporario com os dados certos
    fprintf(arquivo, "  <tabela nome=\"fornecedor\">\n");

    for (atual = lista; atual != NULL; atual = atual->proximo) {
        fprintf(arquivo, "    <registro>\n");
        fprintf(arquivo, "      <id>%d</id>\n", atual->fornecedor.id);
        fprintf(arquivo, "      <nome_fantasia>%s</nome_fantasia>\n", atual->fornecedor.nomeFantasia);
        fprintf(arquivo, "      <razao_social>%s</razao_social>\n", atual->fornecedor.razaoSocial);
        fprintf(arquivo, "      <inscricao_estadual>%s</inscricao_estadual>\n", atual->fornecedor.inscricaoEstadual);
        fprintf(arquivo, "      <cnpj>%s</cnpj>\n", atual->fornecedor.cnpj);
        fprintf(arquivo, "      <endereco>%s</endereco>\n", atual->fornecedor.endereco);
        fprintf(arquivo, "      <telefone>%s</telefone>\n", atual->fornecedor.telefone);
        fprintf(arquivo, "      <email>%s</email>\n", atual->fornecedor.email);
        fprintf(arquivo, "      <ativo>%d</ativo>\n", atual->fornecedor.ativo);
        fprintf(arquivo, "    </registro>\n");
    }

    fprintf(arquivo, "  </tabela>\n");
    
    // funcao q vai salvar a tabela temporaria no arquivo final
    // AINDA TEM Q IMPLEMENTAR ================================================
    salvarTabelaTempNoArquivo(caminho, "fornecedor", arquivo);
    fclose(arquivo);
}

void ImportarFornecedorXml(ListaFornecedor **lista, char *caminho) {
    FILE *arquivo = fopen(caminho, "r");
    char linha[500];
    TipoFornecedor fornecedor;
    ListaFornecedor *novo;
    int lendo_reg = 0;
    int dentroTabela = 0;

    // se n deu pra abrir o arquivo, retorna erro
    if (arquivo == NULL) {
        printf("Erro ao abrir o arquivo para importacao.\n");
        return;
    }

    if (*lista != NULL) {
        FornecedorListaLiberar(*lista);
        *lista = NULL;
    }
    
    // limpa o operador pra n ter lixo de memoria
    FornecedorInit(&fornecedor);

    // le o xml linha por linha
    while (fgets(linha, sizeof(linha), arquivo) != NULL) {
        // Confere o status da linha atual
        // ( 0) se n ta dentro da tabela, ignora
        // ( 1) se ta dentro da tabela, le os dados
        // (-1) se acabou a tabela, termina
        int status = verificarLinhaTabela(linha, "fornecedor", &dentroTabela);
        if (status == 0) {
            continue;
        }
        if (status == -1) {
            break;
        }

        if (strstr(linha, "<registro>") != NULL) {
            lendo_reg = 1;
            FornecedorInit(&fornecedor);
            continue;
        }

        if (lendo_reg && strstr(linha, "</registro>") != NULL) {
            novo = (ListaFornecedor *) malloc(sizeof(ListaFornecedor));
            if (novo != NULL) {
                novo->fornecedor = fornecedor;
                novo->proximo = *lista;
                *lista = novo;
            }
            lendo_reg = 0;
            continue;
        }

        if (!lendo_reg) {
            continue;
        }

        lerTagInteiro(linha, "id", &fornecedor.id);
        lerTagTexto(linha, "nome_fantasia", fornecedor.nomeFantasia, sizeof(fornecedor.nomeFantasia));
        lerTagTexto(linha, "razao_social", fornecedor.razaoSocial, sizeof(fornecedor.razaoSocial));
        lerTagTexto(linha, "inscricao_estadual", fornecedor.inscricaoEstadual, sizeof(fornecedor.inscricaoEstadual));
        lerTagTexto(linha, "cnpj", fornecedor.cnpj, sizeof(fornecedor.cnpj));
        lerTagTexto(linha, "endereco", fornecedor.endereco, sizeof(fornecedor.endereco));
        lerTagTexto(linha, "telefone", fornecedor.telefone, sizeof(fornecedor.telefone));
        lerTagTexto(linha, "email", fornecedor.email, sizeof(fornecedor.email));
        lerTagInteiro(linha, "ativo", &fornecedor.ativo);
    }

    fclose(arquivo);
}

// Caixa

void ExportarCaixaXml(ListaCaixa *lista, char *caminho) {
    FILE *arquivo = tmpfile();

    if (arquivo == NULL) {
        printf("Erro ao abrir o arquivo temporario para exportacao.\n");
        return;
    }

    fprintf(arquivo, "  <tabela nome=\"caixa\">\n");

    for (ListaCaixa *atual = lista; atual != NULL; atual = atual->proximo) {
        fprintf(arquivo, "    <registro>\n");
        fprintf(arquivo, "      <id>%d</id>\n", atual->caixa.id);
        fprintf(arquivo, "      <data>%s</data>\n", atual->caixa.data);
        fprintf(arquivo, "      <tipo>%d</tipo>\n", atual->caixa.tipo);
        fprintf(arquivo, "      <valor>%.2f</valor>\n", atual->caixa.valor);
        fprintf(arquivo, "      <descricao>%s</descricao>\n", atual->caixa.descricao);
        fprintf(arquivo, "      <metodo_pagamento>%d</metodo_pagamento>\n", atual->caixa.metodoPagamento);
        fprintf(arquivo, "      <id_referencia>%d</id_referencia>\n", atual->caixa.idReferencia);
        fprintf(arquivo, "      <ativo>%d</ativo>\n", atual->caixa.ativo);
        fprintf(arquivo, "    </registro>\n");
    }

    fprintf(arquivo, "  </tabela>\n");
    
    // funcao q vai salvar a tabela temporaria no arquivo final
    // AINDA TEM Q IMPLEMENTAR ================================================
    salvarTabelaTempNoArquivo(caminho, "caixa", arquivo);
    fclose(arquivo);
}

void ImportarCaixaXml(ListaCaixa **lista, char *caminho) {
    FILE *arquivo = fopen(caminho, "r");
    char linha[500];
    TipoCaixa caixa;
    ListaCaixa *novo;
    int lendo_reg = 0;
    int dentroTabela = 0;

    // se n deu pra abrir o arquivo, retorna erro
    if (arquivo == NULL) {
        printf("Erro ao abrir o arquivo para importacao.\n");
        return;
    }

    if (*lista != NULL) {
        CaixaListaLiberar(*lista);
        *lista = NULL;
    }
    
    // limpa o operador pra n ter lixo de memoria
    CaixaInit(&caixa);

    // le o xml linha por linha
    while (fgets(linha, sizeof(linha), arquivo) != NULL) {
        // Confere o status da linha atual
        // ( 0) se n ta dentro da tabela, ignora
        // ( 1) se ta dentro da tabela, le os dados
        // (-1) se acabou a tabela, termina
        int status = verificarLinhaTabela(linha, "caixa", &dentroTabela);
        if (status == 0) {
            continue;
        }
        if (status == -1) {
            break;
        }

        if (strstr(linha, "<registro>") != NULL) {
            lendo_reg = 1;
            CaixaInit(&caixa);
            continue;
        }

        if (lendo_reg && strstr(linha, "</registro>") != NULL) {
            novo = (ListaCaixa *) malloc(sizeof(ListaCaixa));
            if (novo != NULL) {
                novo->caixa = caixa;
                novo->proximo = *lista;
                *lista = novo;
            }
            lendo_reg = 0;
            continue;
        }

        if (!lendo_reg) {
            continue;
        }

        lerTagInteiro(linha, "id", &caixa.id);
        lerTagTexto(linha, "data", caixa.data, sizeof(caixa.data));
        lerTagInteiro(linha, "tipo", &caixa.tipo);
        lerTagDouble(linha, "valor", &caixa.valor);
        lerTagTexto(linha, "descricao", caixa.descricao, sizeof(caixa.descricao));
        lerTagInteiro(linha, "metodo_pagamento", &caixa.metodoPagamento);
        lerTagInteiro(linha, "id_referencia", &caixa.idReferencia);
        lerTagInteiro(linha, "ativo", &caixa.ativo);
    }

    fclose(arquivo);
}

// Checkin

void ExportarCheckinXml(ListaCheckin *lista, char *caminho) {
    FILE *arquivo = tmpfile();

    if (arquivo == NULL) {
        printf("Erro ao abrir o arquivo temporario para exportacao.\n");
        return;
    }

    fprintf(arquivo, "  <tabela nome=\"checkin\">\n");

    for (ListaCheckin *atual = lista; atual != NULL; atual = atual->proximo) {
        fprintf(arquivo, "    <registro>\n");
        fprintf(arquivo, "      <id>%d</id>\n", atual->checkin.id);
        fprintf(arquivo, "      <id_reserva>%d</id_reserva>\n", atual->checkin.idReserva);
        fprintf(arquivo, "      <id_hospede>%d</id_hospede>\n", atual->checkin.idHospede);
        fprintf(arquivo, "      <id_acomodacao>%d</id_acomodacao>\n", atual->checkin.idAcomodacao);
        fprintf(arquivo, "      <data_checkin>%s</data_checkin>\n", atual->checkin.dataCheckin);
        fprintf(arquivo, "      <data_checkout>%s</data_checkout>\n", atual->checkin.dataCheckout);
        fprintf(arquivo, "      <total_diarias>%.2f</total_diarias>\n", atual->checkin.totalDiarias);
        fprintf(arquivo, "      <total_produtos>%.2f</total_produtos>\n", atual->checkin.totalProdutos);
        fprintf(arquivo, "      <total_geral>%.2f</total_geral>\n", atual->checkin.totalGeral);
        fprintf(arquivo, "      <diarias_paras>%d</diarias_paras>\n", atual->checkin.diariasParas);
        fprintf(arquivo, "      <encerrado>%d</encerrado>\n", atual->checkin.encerrado);
        fprintf(arquivo, "      <ativo>%d</ativo>\n", atual->checkin.ativo);
        fprintf(arquivo, "    </registro>\n");
    }

    fprintf(arquivo, "  </tabela>\n");
    
    // funcao q vai salvar a tabela temporaria no arquivo final
    // AINDA TEM Q IMPLEMENTAR ================================================
    salvarTabelaTempNoArquivo(caminho, "checkin", arquivo);
    fclose(arquivo);
}

void ImportarCheckinXml(ListaCheckin **lista, char *caminho) {
    FILE *arquivo = fopen(caminho, "r");
    char linha[500];
    TipoCheckin checkin;
    ListaCheckin *novo;
    int lendo_reg = 0;
    int dentroTabela = 0;

    // se n deu pra abrir o arquivo, retorna erro
    if (arquivo == NULL) {
        printf("Erro ao abrir o arquivo para importacao.\n");
        return;
    }

    if (*lista != NULL) {
        CheckinListaLiberar(*lista);
        *lista = NULL;
    }
    
    // limpa o operador pra n ter lixo de memoria
    CheckinInit(&checkin);

    // le o xml linha por linha
    while (fgets(linha, sizeof(linha), arquivo) != NULL) {
        // Confere o status da linha atual
        // ( 0) se n ta dentro da tabela, ignora
        // ( 1) se ta dentro da tabela, le os dados
        // (-1) se acabou a tabela, termina
        int status = verificarLinhaTabela(linha, "checkin", &dentroTabela);
        if (status == 0) {
            continue;
        }
        if (status == -1) {
            break;
        }

        if (strstr(linha, "<registro>") != NULL) {
            lendo_reg = 1;
            CheckinInit(&checkin);
            continue;
        }

        if (lendo_reg && strstr(linha, "</registro>") != NULL) {
            novo = (ListaCheckin *) malloc(sizeof(ListaCheckin));
            if (novo != NULL) {
                novo->checkin = checkin;
                novo->proximo = *lista;
                *lista = novo;
            }
            lendo_reg = 0;
            continue;
        }

        if (!lendo_reg) {
            continue;
        }

        lerTagInteiro(linha, "id", &checkin.id);
        lerTagInteiro(linha, "id_reserva", &checkin.idReserva);
        lerTagInteiro(linha, "id_hospede", &checkin.idHospede);
        lerTagInteiro(linha, "id_acomodacao", &checkin.idAcomodacao);
        lerTagTexto(linha, "data_checkin", checkin.dataCheckin, sizeof(checkin.dataCheckin));
        lerTagTexto(linha, "data_checkout", checkin.dataCheckout, sizeof(checkin.dataCheckout));
        lerTagFloat(linha, "total_diarias", &checkin.totalDiarias);
        lerTagFloat(linha, "total_produtos", &checkin.totalProdutos);
        lerTagFloat(linha, "total_geral", &checkin.totalGeral);
        lerTagInteiro(linha, "diarias_paras", &checkin.diariasParas);
        lerTagInteiro(linha, "encerrado", &checkin.encerrado);
        lerTagInteiro(linha, "ativo", &checkin.ativo);
    }

    fclose(arquivo);
}

// Conta Pagar

void ExportarContaPagarXml(ListaContaPagar *lista, char *caminho) {
    FILE *arquivo = tmpfile();

    if (arquivo == NULL) {
        printf("Erro ao abrir o arquivo temporario para exportacao.\n");
        return;
    }

    fprintf(arquivo, "  <tabela nome=\"conta_pagar\">\n");

    for (ListaContaPagar *atual = lista; atual != NULL; atual = atual->proximo) {
        fprintf(arquivo, "    <registro>\n");
        fprintf(arquivo, "      <id>%d</id>\n", atual->conta.id);
        fprintf(arquivo, "      <id_fornecedor>%d</id_fornecedor>\n", atual->conta.idFornecedor);
        fprintf(arquivo, "      <id_nota_fiscal>%d</id_nota_fiscal>\n", atual->conta.idNotaFiscal);
        fprintf(arquivo, "      <descricao>%s</descricao>\n", atual->conta.descricao);
        fprintf(arquivo, "      <valor>%.2f</valor>\n", atual->conta.valor);
        fprintf(arquivo, "      <data_vencimento>%s</data_vencimento>\n", atual->conta.dataVencimento);
        fprintf(arquivo, "      <data_pagamento>%s</data_pagamento>\n", atual->conta.dataPagamento);
        fprintf(arquivo, "      <numero_parcela>%d</numero_parcela>\n", atual->conta.numeroParcela);
        fprintf(arquivo, "      <total_parcelas>%d</total_parcelas>\n", atual->conta.totalParcelas);
        fprintf(arquivo, "      <status>%d</status>\n", atual->conta.status);
        fprintf(arquivo, "      <ativo>%d</ativo>\n", atual->conta.ativo);
        fprintf(arquivo, "    </registro>\n");
    }

    fprintf(arquivo, "  </tabela>\n");
    
    // funcao q vai salvar a tabela temporaria no arquivo final
    // AINDA TEM Q IMPLEMENTAR ================================================
    salvarTabelaTempNoArquivo(caminho, "conta_pagar", arquivo);
    fclose(arquivo);
}

void ImportarContaPagarXml(ListaContaPagar **lista, char *caminho) {
    FILE *arquivo = fopen(caminho, "r");
    char linha[500];
    TipoContaPagar conta;
    ListaContaPagar *novo;
    int lendo_reg = 0;
    int dentroTabela = 0;

    // se n deu pra abrir o arquivo, retorna erro
    if (arquivo == NULL) {
        printf("Erro ao abrir o arquivo para importacao.\n");
        return;
    }

    if (*lista != NULL) {
        ContaPagarListaLiberar(*lista);
        *lista = NULL;
    }
    
    // limpa o operador pra n ter lixo de memoria
    ContaPagarInit(&conta);

    // le o xml linha por linha
    while (fgets(linha, sizeof(linha), arquivo) != NULL) {
        // Confere o status da linha atual
        // ( 0) se n ta dentro da tabela, ignora
        // ( 1) se ta dentro da tabela, le os dados
        // (-1) se acabou a tabela, termina
        int status = verificarLinhaTabela(linha, "conta_pagar", &dentroTabela);
        if (status == 0) {
            continue;
        }
        if (status == -1) {
            break;
        }

        if (strstr(linha, "<registro>") != NULL) {
            lendo_reg = 1;
            ContaPagarInit(&conta);
            continue;
        }

        if (lendo_reg && strstr(linha, "</registro>") != NULL) {
            novo = (ListaContaPagar *) malloc(sizeof(ListaContaPagar));
            if (novo != NULL) {
                novo->conta = conta;
                novo->proximo = *lista;
                *lista = novo;
            }
            lendo_reg = 0;
            continue;
        }

        if (!lendo_reg) {
            continue;
        }

        lerTagInteiro(linha, "id", &conta.id);
        lerTagInteiro(linha, "id_fornecedor", &conta.idFornecedor);
        lerTagInteiro(linha, "id_nota_fiscal", &conta.idNotaFiscal);
        lerTagTexto(linha, "descricao", conta.descricao, sizeof(conta.descricao));
        lerTagFloat(linha, "valor", &conta.valor);
        lerTagTexto(linha, "data_vencimento", conta.dataVencimento, sizeof(conta.dataVencimento));
        lerTagTexto(linha, "data_pagamento", conta.dataPagamento, sizeof(conta.dataPagamento));
        lerTagInteiro(linha, "numero_parcela", &conta.numeroParcela);
        lerTagInteiro(linha, "total_parcelas", &conta.totalParcelas);
        lerTagInteiro(linha, "status", &conta.status);
        lerTagInteiro(linha, "ativo", &conta.ativo);
    }

    fclose(arquivo);
}

// Conta Receber

void ExportarContaReceberXml(ListaContaReceber *lista, char *caminho) {
    FILE *arquivo = tmpfile();

    if (arquivo == NULL) {
        printf("Erro ao abrir o arquivo temporario para exportacao.\n");
        return;
    }

    fprintf(arquivo, "  <tabela nome=\"conta_receber\">\n");

    for (ListaContaReceber *atual = lista; atual != NULL; atual = atual->proximo) {
        fprintf(arquivo, "    <registro>\n");
        fprintf(arquivo, "      <id>%d</id>\n", atual->conta.id);
        fprintf(arquivo, "      <id_hospede>%d</id_hospede>\n", atual->conta.idHospede);
        fprintf(arquivo, "      <descricao>%s</descricao>\n", atual->conta.descricao);
        fprintf(arquivo, "      <valor>%.2f</valor>\n", atual->conta.valor);
        fprintf(arquivo, "      <data_vencimento>%s</data_vencimento>\n", atual->conta.dataVencimento);
        fprintf(arquivo, "      <data_recebimento>%s</data_recebimento>\n", atual->conta.dataRecebimento);
        fprintf(arquivo, "      <status>%d</status>\n", atual->conta.status);
        fprintf(arquivo, "      <ativo>%d</ativo>\n", atual->conta.ativo);
        fprintf(arquivo, "    </registro>\n");
    }

    fprintf(arquivo, "  </tabela>\n");
    
    // funcao q vai salvar a tabela temporaria no arquivo final
    // AINDA TEM Q IMPLEMENTAR ================================================
    salvarTabelaTempNoArquivo(caminho, "conta_receber", arquivo);
    fclose(arquivo);
}

void ImportarContaReceberXml(ListaContaReceber **lista, char *caminho) {
    FILE *arquivo = fopen(caminho, "r");
    char linha[500];
    TipoContaReceber conta;
    ListaContaReceber *novo;
    int lendo_reg = 0;
    int dentroTabela = 0;

    // se n deu pra abrir o arquivo, retorna erro
    if (arquivo == NULL) {
        printf("Erro ao abrir o arquivo para importacao.\n");
        return;
    }

    if (*lista != NULL) {
        ContaReceberListaLiberar(*lista);
        *lista = NULL;
    }
    
    // limpa o operador pra n ter lixo de memoria
    ContaReceberInit(&conta);

    // le o xml linha por linha
    while (fgets(linha, sizeof(linha), arquivo) != NULL) {
        // Confere o status da linha atual
        // ( 0) se n ta dentro da tabela, ignora
        // ( 1) se ta dentro da tabela, le os dados
        // (-1) se acabou a tabela, termina
        int status = verificarLinhaTabela(linha, "conta_receber", &dentroTabela);
        if (status == 0) {
            continue;
        }
        if (status == -1) {
            break;
        }

        if (strstr(linha, "<registro>") != NULL) {
            lendo_reg = 1;
            ContaReceberInit(&conta);
            continue;
        }

        if (lendo_reg && strstr(linha, "</registro>") != NULL) {
            novo = (ListaContaReceber *) malloc(sizeof(ListaContaReceber));
            if (novo != NULL) {
                novo->conta = conta;
                novo->proximo = *lista;
                *lista = novo;
            }
            lendo_reg = 0;
            continue;
        }

        if (!lendo_reg) {
            continue;
        }

        lerTagInteiro(linha, "id", &conta.id);
        lerTagInteiro(linha, "id_hospede", &conta.idHospede);
        lerTagTexto(linha, "descricao", conta.descricao, sizeof(conta.descricao));
        lerTagFloat(linha, "valor", &conta.valor);
        lerTagTexto(linha, "data_vencimento", conta.dataVencimento, sizeof(conta.dataVencimento));
        lerTagTexto(linha, "data_recebimento", conta.dataRecebimento, sizeof(conta.dataRecebimento));
        lerTagInteiro(linha, "status", &conta.status);
        lerTagInteiro(linha, "ativo", &conta.ativo);
    }

    fclose(arquivo);
}

// Venda

void ExportarVendaXml(ListaVenda *lista, char *caminho) {
    FILE *arquivo = tmpfile();

    if (arquivo == NULL) {
        printf("Erro ao abrir o arquivo temporario para exportacao.\n");
        return;
    }

    fprintf(arquivo, "  <tabela nome=\"venda\">\n");

    for (ListaVenda *atual = lista; atual != NULL; atual = atual->proximo) {
        fprintf(arquivo, "    <registro>\n");
        fprintf(arquivo, "      <id>%d</id>\n", atual->venda.id);
        fprintf(arquivo, "      <id_hospede>%d</id_hospede>\n", atual->venda.idHospede);
        fprintf(arquivo, "      <data>%s</data>\n", atual->venda.data);
        fprintf(arquivo, "      <num_itens>%d</num_itens>\n", atual->venda.numItens);
        fprintf(arquivo, "      <total>%.2f</total>\n", atual->venda.total);
        fprintf(arquivo, "      <forma_pagamento>%d</forma_pagamento>\n", atual->venda.formaPagamento);
        fprintf(arquivo, "      <lancada_no_caixa>%d</lancada_no_caixa>\n", atual->venda.lancadaNoCaixa);
        fprintf(arquivo, "      <ativo>%d</ativo>\n", atual->venda.ativo);
        fprintf(arquivo, "    </registro>\n");
    }

    fprintf(arquivo, "  </tabela>\n");
    
    // funcao q vai salvar a tabela temporaria no arquivo final
    // AINDA TEM Q IMPLEMENTAR ================================================
    salvarTabelaTempNoArquivo(caminho, "venda", arquivo);
    fclose(arquivo);
}

void ImportarVendaXml(ListaVenda **lista, char *caminho) {
    FILE *arquivo = fopen(caminho, "r");
    char linha[500];
    TipoVenda venda;
    ListaVenda *novo;
    int lendo_reg = 0;
    int dentroTabela = 0;

    // se n deu pra abrir o arquivo, retorna erro
    if (arquivo == NULL) {
        printf("Erro ao abrir o arquivo para importacao.\n");
        return;
    }

    if (*lista != NULL) {
        VendaListaLiberar(*lista);
        *lista = NULL;
    }
    
    // limpa o operador pra n ter lixo de memoria
    VendaInit(&venda);

    // le o xml linha por linha
    while (fgets(linha, sizeof(linha), arquivo) != NULL) {
        // Confere o status da linha atual
        // ( 0) se n ta dentro da tabela, ignora
        // ( 1) se ta dentro da tabela, le os dados
        // (-1) se acabou a tabela, termina
        int status = verificarLinhaTabela(linha, "venda", &dentroTabela);
        if (status == 0) {
            continue;
        }
        if (status == -1) {
            break;
        }

        if (strstr(linha, "<registro>") != NULL) {
            lendo_reg = 1;
            VendaInit(&venda);
            continue;
        }

        if (lendo_reg && strstr(linha, "</registro>") != NULL) {
            novo = (ListaVenda *) malloc(sizeof(ListaVenda));
            if (novo != NULL) {
                novo->venda = venda;
                novo->proximo = *lista;
                *lista = novo;
            }
            lendo_reg = 0;
            continue;
        }

        if (!lendo_reg) {
            continue;
        }

        lerTagInteiro(linha, "id", &venda.id);
        lerTagInteiro(linha, "id_hospede", &venda.idHospede);
        lerTagTexto(linha, "data", venda.data, sizeof(venda.data));
        lerTagInteiro(linha, "num_itens", &venda.numItens);
        lerTagFloat(linha, "total", &venda.total);
        lerTagInteiro(linha, "forma_pagamento", &venda.formaPagamento);
        lerTagInteiro(linha, "lancada_no_caixa", &venda.lancadaNoCaixa);
        lerTagInteiro(linha, "ativo", &venda.ativo);
    }

    fclose(arquivo);
}

// Nota Fiscal

void ExportarNotaFiscalXml(ListaNotaFiscal *lista, char *caminho) {
    FILE *arquivo = tmpfile();

    if (arquivo == NULL) {
        printf("Erro ao abrir o arquivo temporario para exportacao.\n");
        return;
    }

    fprintf(arquivo, "  <tabela nome=\"nota_fiscal\">\n");

    for (ListaNotaFiscal *atual = lista; atual != NULL; atual = atual->proximo) {
        fprintf(arquivo, "    <registro>\n");
        fprintf(arquivo, "      <id>%d</id>\n", atual->nota.id);
        fprintf(arquivo, "      <id_fornecedor>%d</id_fornecedor>\n", atual->nota.idFornecedor);
        fprintf(arquivo, "      <data>%s</data>\n", atual->nota.data);
        fprintf(arquivo, "      <frete>%.2f</frete>\n", atual->nota.frete);
        fprintf(arquivo, "      <imposto>%.2f</imposto>\n", atual->nota.imposto);
        fprintf(arquivo, "      <num_itens>%d</num_itens>\n", atual->nota.numItens);
        fprintf(arquivo, "      <total_nota>%.2f</total_nota>\n", atual->nota.totalNota);
        fprintf(arquivo, "      <forma_pagamento>%d</forma_pagamento>\n", atual->nota.formaPagamento);
        fprintf(arquivo, "      <valor_entrada>%.2f</valor_entrada>\n", atual->nota.valorEntrada);
        fprintf(arquivo, "      <num_parcelas>%d</num_parcelas>\n", atual->nota.numParcelas);
        fprintf(arquivo, "      <ativo>%d</ativo>\n", atual->nota.ativo);
        fprintf(arquivo, "    </registro>\n");
    }

    fprintf(arquivo, "  </tabela>\n");
    
    // funcao q vai salvar a tabela temporaria no arquivo final
    // AINDA TEM Q IMPLEMENTAR ================================================
    salvarTabelaTempNoArquivo(caminho, "nota_fiscal", arquivo);
    fclose(arquivo);
}

void ImportarNotaFiscalXml(ListaNotaFiscal **lista, char *caminho) {
    FILE *arquivo = fopen(caminho, "r");
    char linha[500];
    TipoNotaFiscal nota;
    ListaNotaFiscal *novo;
    int lendo_reg = 0;
    int dentroTabela = 0;

    // se n deu pra abrir o arquivo, retorna erro
    if (arquivo == NULL) {
        printf("Erro ao abrir o arquivo para importacao.\n");
        return;
    }

    if (*lista != NULL) {
        NotaFiscalListaLiberar(*lista);
        *lista = NULL;
    }
    
    // limpa o operador pra n ter lixo de memoria
    NotaFiscalInit(&nota);

    // le o xml linha por linha
    while (fgets(linha, sizeof(linha), arquivo) != NULL) {
        // Confere o status da linha atual
        // ( 0) se n ta dentro da tabela, ignora
        // ( 1) se ta dentro da tabela, le os dados
        // (-1) se acabou a tabela, termina
        int status = verificarLinhaTabela(linha, "nota_fiscal", &dentroTabela);
        if (status == 0) {
            continue;
        }
        if (status == -1) {
            break;
        }

        if (strstr(linha, "<registro>") != NULL) {
            lendo_reg = 1;
            NotaFiscalInit(&nota);
            continue;
        }

        if (lendo_reg && strstr(linha, "</registro>") != NULL) {
            novo = (ListaNotaFiscal *) malloc(sizeof(ListaNotaFiscal));
            if (novo != NULL) {
                novo->nota = nota;
                novo->proximo = *lista;
                *lista = novo;
            }
            lendo_reg = 0;
            continue;
        }

        if (!lendo_reg) {
            continue;
        }

        lerTagInteiro(linha, "id", &nota.id);
        lerTagInteiro(linha, "id_fornecedor", &nota.idFornecedor);
        lerTagTexto(linha, "data", nota.data, sizeof(nota.data));
        lerTagFloat(linha, "frete", &nota.frete);
        lerTagFloat(linha, "imposto", &nota.imposto);
        lerTagInteiro(linha, "num_itens", &nota.numItens);
        lerTagFloat(linha, "total_nota", &nota.totalNota);
        lerTagInteiro(linha, "forma_pagamento", &nota.formaPagamento);
        lerTagFloat(linha, "valor_entrada", &nota.valorEntrada);
        lerTagInteiro(linha, "num_parcelas", &nota.numParcelas);
        lerTagInteiro(linha, "ativo", &nota.ativo);
    }

    fclose(arquivo);
}

// ============================================================
// MENU PRINCIPAL

void ImportExportControllerExecutar(ListaHospede **listaHospede,
                                   ListaReserva **listaReserva,
                                   ListaAcomodacao **listaAcomodacao,
                                   ListaCategoria **listaCategoria,
                                   ListaProduto **listaProduto,
                                   Hotel *hotel,
                                   ListaOperador **listaOperador,
                                   ListaNotaFiscal **listaNotaFiscal,
                                   ListaVenda **listaVenda,
                                   ListaCaixa **listaCaixa,
                                   ListaCheckin **listaCheckin,
                                   ListaContaPagar **listaContaPagar,
                                   ListaContaReceber **listaContaReceber) {
    int opcao;
    int opcao2;
    char caminho[300];
    ListaFornecedor *listaFornecedor = NULL;

    do {
        mostrarMenuXML();
        opcao = ler_int("Opcao");
        opcao2 = ler_int("Deseja importar ou exportar? (1: Exportar | 2: Importar)");

        // já pega o caminho desejado
        pedirCaminhoXml(caminho, sizeof(caminho));

        // seleciona qual estrutura primeiro dps ve oq tem q fzr comk ela
        switch (opcao) {
            case 1:
                // Hotel

                if (opcao2 == 1) {
                    ExportarHotelXml(hotel, caminho);
                    printf("Hotel exportado para XML.\n");
                } else if (opcao2 == 2) {
                    ImportarHotelXml(hotel, caminho);
                    printf("Hotel importado do XML.\n");
                } else {
                    printf("Opcao invalida.\n");
                }

                break;
            case 2:
                // Operador

                if (opcao2 == 1) {
                    ExportarOperadorXml(*listaOperador, caminho);
                    printf("Operadores exportados para XML.\n");
                } else if (opcao2 == 2) {
                    ImportarOperadorXml(listaOperador, caminho);
                    printf("Operadores importados do XML.\n");
                } else {
                    printf("Opcao invalida.\n");
                }

                break;
            case 3:
                // Hospede

                if (opcao2 == 1) {
                    ExportarHospedeXml(*listaHospede, caminho);
                    printf("Hospedes exportados para XML.\n");
                } else if (opcao2 == 2) {
                    ImportarHospedeXml(listaHospede, caminho);
                    printf("Hospedes importados do XML.\n");
                } else {
                    printf("Opcao invalida.\n");
                }

                break;
            case 4:
                // Categoria

                if (opcao2 == 1) {
                    ExportarCategoriaXml(*listaCategoria, caminho);
                    printf("Categorias exportadas para XML.\n");
                } else if (opcao2 == 2) {
                    ImportarCategoriaXml(listaCategoria, caminho);
                    printf("Categorias importadas do XML.\n");
                } else {
                    printf("Opcao invalida.\n");
                }
                
                break;
            case 5:
                // Acomodacao
                
                if (opcao2 == 1) {
                    ExportarAcomodacaoXml(*listaAcomodacao, caminho);
                    printf("Acomodacoes exportadas para XML.\n");
                } else if (opcao2 == 2) {
                    ImportarAcomodacaoXml(listaAcomodacao, caminho);
                    printf("Acomodacoes importadas do XML.\n");
                } else {
                    printf("Opcao invalida.\n");
                }

                break;
            case 6:
                // Reserva
                if (opcao2 == 1) {
                    ExportarReservaXml(*listaReserva, caminho);
                    printf("Reservas exportadas para XML.\n");
                } else if (opcao2 == 2) {
                    ImportarReservaXml(listaReserva, caminho);
                    printf("Reservas importadas do XML.\n");
                } else {
                    printf("Opcao invalida.\n");
                }
                break;
            case 7:
                // Produto
                if (opcao2 == 1) {
                    ExportarProdutoXml(*listaProduto, caminho);
                    printf("Produtos exportados para XML.\n");
                } else if (opcao2 == 2) {
                    ImportarProdutoXml(listaProduto, caminho);
                    printf("Produtos importados do XML.\n");
                } else {
                    printf("Opcao invalida.\n");
                }
                break;
            case 8:
                // Fornecedor
                
                if (opcao2 == 1) {
                    ExportarFornecedorXml(listaFornecedor, caminho);
                    printf("Fornecedores exportados para XML.\n");
                } else if (opcao2 == 2) {
                    ImportarFornecedorXml(&listaFornecedor, caminho);
                    printf("Fornecedores importados do XML.\n");
                } else {
                    printf("Opcao invalida.\n");
                }

                break;
            case 9:
                // Caixa

                if (opcao2 == 1) {
                    ExportarCaixaXml(*listaCaixa, caminho);
                    printf("Caixa exportado para XML.\n");
                } else if (opcao2 == 2) {
                    ImportarCaixaXml(listaCaixa, caminho);
                    printf("Caixa importado do XML.\n");
                } else {
                    printf("Opcao invalida.\n");
                }

                break;
            case 10:
                // Check-in
                if (opcao2 == 1) {
                    ExportarCheckinXml(*listaCheckin, caminho);
                    printf("Check-ins exportados para XML.\n");
                } else if (opcao2 == 2) {
                    ImportarCheckinXml(listaCheckin, caminho);
                    printf("Check-ins importados do XML.\n");
                } else {
                    printf("Opcao invalida.\n");
                }

                break;
            case 11:
                // Conta a pagar

                if (opcao2 == 1) {
                    ExportarContaPagarXml(*listaContaPagar, caminho);
                    printf("Contas a pagar exportadas para XML.\n");
                } else if (opcao2 == 2) {
                    ImportarContaPagarXml(listaContaPagar, caminho);
                    printf("Contas a pagar importadas do XML.\n");
                } else {
                    printf("Opcao invalida.\n");
                }
                break;
            case 12:
                // Conta a receber
                if (opcao2 == 1) {
                    ExportarContaReceberXml(*listaContaReceber, caminho);
                    printf("Contas a receber exportadas para XML.\n");
                } else if (opcao2 == 2) {
                    ImportarContaReceberXml(listaContaReceber, caminho);
                    printf("Contas a receber importadas do XML.\n");
                } else {
                    printf("Opcao invalida.\n");
                }
                break;
            case 13:
                // Venda
                if (opcao2 == 1) {
                    ExportarVendaXml(*listaVenda, caminho);
                    printf("Vendas exportadas para XML.\n");
                } else if (opcao2 == 2) {
                    ImportarVendaXml(listaVenda, caminho);
                    printf("Vendas importadas do XML.\n");
                } else {
                    printf("Opcao invalida.\n");
                }
                break;
            case 14:
                // Nota fiscal
                if (opcao2 == 1) {
                    ExportarNotaFiscalXml(*listaNotaFiscal, caminho);
                    printf("Notas fiscais exportadas para XML.\n");
                } else if (opcao2 == 2) {
                    ImportarNotaFiscalXml(listaNotaFiscal, caminho);
                    printf("Notas fiscais importadas do XML.\n");
                } else {
                    printf("Opcao invalida.\n");
                }
                break;
            case 15:
                // Exportar tudo
                ExportarHotelXml(hotel, caminho);
                ExportarOperadorXml(*listaOperador, caminho);
                ExportarHospedeXml(*listaHospede, caminho);
                ExportarCategoriaXml(*listaCategoria, caminho);
                ExportarAcomodacaoXml(*listaAcomodacao, caminho);
                ExportarReservaXml(*listaReserva, caminho);
                ExportarProdutoXml(*listaProduto, caminho);
                ExportarFornecedorXml(listaFornecedor, caminho);
                ExportarCaixaXml(*listaCaixa, caminho);
                ExportarCheckinXml(*listaCheckin, caminho);
                ExportarContaPagarXml(*listaContaPagar, caminho);
                ExportarContaReceberXml(*listaContaReceber, caminho);
                ExportarVendaXml(*listaVenda, caminho);
                ExportarNotaFiscalXml(*listaNotaFiscal, caminho);
                printf("Tudo exportado para XML.\n");
                break;
            case 0:
                break;
            default:
                printf("Opcao invalida.\n");
                break;
        }

        if (opcao != 0) {
            pausar();
        }
    } while (opcao != 0);
}
