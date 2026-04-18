CC = gcc
CFLAGS = -Wall -g

TARGET = hotelbao

# arquivos fontes
SRC = \
model/acomodacao.c \
model/hospede.c \
model/hotel.c \
model/operador.c \
utils/validacao.c \
view/hospede_view.c \
view/menu_principal.c \
view/menu_relatorio.c \
view/menu_cadastro.c

# Gera automaticamente os .o
OBJ = $(SRC:.c=.o)

# Regra principal
all: $(TARGET)

$(TARGET): $(OBJ)
	$(CC) $(CFLAGS) -o $(TARGET) $(OBJ)

# Compilação de cada .c → .o
%.o: %.c
	$(CC) $(CFLAGS) -c $< -o $@

# Limpar arquivos gerados
clean:
	del /Q model\*.o utils\*.o view\*.o $(TARGET).exe 2>nul || true