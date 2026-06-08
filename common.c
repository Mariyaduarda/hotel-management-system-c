// common.c 
#include "common.h"

/* ── Limpar Buffer ────────────────────────────── */
void limparBuffer() {
    int c;
    while ((c = getchar()) != '\n' && c != EOF);
}
/* ── Ler a string  ────────────────────────────── */
void lerString(char *destino, int tamanho) {
    
    fgets(destino, tamanho, stdin);

    destino[strcspn(destino, "\n")] = '\0';
}

/* ──  ────────────────────────────── */
int LerInt(){
    char linha[100];
    int valor;

    while(1){
        fgets(linha, sizeof(linha), stdin);
        
        if (sscanf(linha, "%d", &valor) == 1) return valor;

        ViewEntradaInvalida();
    }
}

/* ── Converte uma data no formato "dd/mm/aaaa" ────────────────────────────── */
int dataParaInt(const char* data){
    int d = 0, m = 0, a = 0;
    sscanf(data, "%d/%d/%d", &d, &m, &a);
    return a * 10000 + m * 100 + d;
}
