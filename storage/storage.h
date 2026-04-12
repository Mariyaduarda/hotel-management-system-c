// storage/stroge.h
#ifndef STORAGE_H
#define STORAGE_H

#include "../model/hospede.h"

// Define o tipo de storage escolhido
typedef enum {
    ARQUIVO_BIN,
    MEMORIA,
    ARQUIVO_TXT
} TipoStorage;

// Estrutura de armazenamento generica
typedef struct {
    void ((*salvar_hospede) (Hospede *hospede));
    void ((*salvar_reserva) (Reserva *reserva));
    void (*listar_hospedes) ();
    void (*deletar_hospede) (int id);
} Storage;

Storage criarStorage(TipoStorage tipo);

#endif // STORAGE_H