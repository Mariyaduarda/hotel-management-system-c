CC     = gcc
CFLAGS = -Wall -Wextra -g
TARGET = hotelbao

SRC = \
    main.c \
    common.c \
    model/acomodacao.c \
    model/categoria_acomodacao.c \
    model/hospede.c \
    model/hotel.c \
    model/operador.c \
    model/reserva.c \
    model/produto.c \
    controller/hospede_controller.c \
    controller/reserva_controller.c \
    controller/relatorio_controller.c \
    controller/produto_controller.c \
    controller/hotel_controller.c \
    view/menu_principal.c \
    view/hospede_view.c \
    view/reserva_view.c \
    view/produto_view.c \
    view/relatorio_view.c \
    utils/validacao.c \
    utils/relatorio.c\
    view/login_view.c\

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