#include "../common.h"

void lerString(char *destino, int tamanho){
    setbuf(stdin, NULL); // Limpa o buffer de entrada
    fgets(destino, tamanho, stdin); // Lê a string, incluindo espaços
    destino[strcspn(destino, "\n")] = '\0'; // Remove o caractere de nova linha
}