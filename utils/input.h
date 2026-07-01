#ifndef INPUT_H
#define INPUT_H

// utilidade
void limpar_buffer_entrada(void);

// numeros
int    ler_int(char *prompt);
long   ler_long(char *prompt);
float  ler_float(char *prompt);
double ler_double(char *prompt);

// numeros com intervalo
int  ler_int_intervalo(char *prompt, int min, int max);
float ler_float_intervalo(char *prompt, float min, float max);

// texto
void   ler_string(char *prompt, char *buffer, int tamanho);]
char   ler_char(char *prompt);

// outros
int ler_confirmacao(char *prompt);


#endif