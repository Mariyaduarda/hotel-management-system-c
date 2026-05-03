CC     = gcc
CFLAGS = -Wall -Wextra -g
TARGET = hotelbao

SRC = \
    main.c \
    model/acomodacao.c \
    model/categoria.c \
    model/hospede.c \
    model/hotel.c \
    model/operador.c \
    model/produto.c \
    model/reserva.c \
    controller/hospede_controller.c \
    controller/reserva_controller.c \
    controller/relatorio_controller.c \
    view/menu_principal.c \
    view/hospede_view.c \
    view/reserva_view.c \
    view/relatorio_view.c \
    utils/validacao.c \
    utils/relatorio.c

OBJ = $(SRC:.c=.o)

# ── Regra principal ──────────────────────────────────────
all: $(TARGET)

$(TARGET): $(OBJ)
	$(CC) $(CFLAGS) -o $(TARGET) $(OBJ) -lssl -lcrypto -lm

# ── Compilação de cada .c em .o ──────────────────────────
%.o: %.c
	$(CC) $(CFLAGS) -c $< -o $@

# ── Limpeza ──────────────────────────────────────────────
clean:
	rm -f $(OBJ) $(TARGET)

# ── Rebuild completo ─────────────────────────────────────
re: clean all

# ── Executa o programa ───────────────────────────────────
run: all
	./$(TARGET)

.PHONY: all clean re run