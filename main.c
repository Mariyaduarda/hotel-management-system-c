#include "common.h"
#include "model/operador.h"
#include "model/hotel.h"

int main(){
    // gcc main.c model/operador.c model/hotel.c -o programa.exe

    criarOperador();

    // recupera e exibe os dados
    const Operador* op = obterOperador();

    printf("\n=== Dados do Operador ===\n");
    printf("ID: %d\n", op->id);
    printf("Usuario: %s\n", op->usuario);
    printf("Senha (SHA256): %s\n", op->senha);

    // TESTE HOTEL
    Hotel hotel;              // cria variável
    HotelInit(&hotel);        // inicializa

    printf("\n=== Dados do Hotel ===\n");
    printf("Nome Fantasia: %s\n", hotel.NomeFantasia);
    printf("Estado: %s\n", hotel.endereco.estado);
    printf("Check-in: %s\n", hotel.CheckIn);

    return 0;
}