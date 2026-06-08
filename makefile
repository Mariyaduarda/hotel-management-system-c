CC     = gcc
CFLAGS = -Wall -Wextra -g
TARGET = hotelbao

SRC := $(filter-out model/relatorio.c, $(wildcard main.c common.c model/*.c controller/*.c view/*.c utils/*.c))
OBJ := $(SRC:.c=.o)

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