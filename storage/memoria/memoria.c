#include "storage.h"
#include "../common.h"


int salvar_bin(Hospede *hospede){
    FILE *arquivo = fopen(ARQUIVO, "ab");
    if (!arquivo) return -1;
    fwrite(hospede, sizeof(hospede), 1, arquivo);
    fclose(arquivo);
    return 0;
}






