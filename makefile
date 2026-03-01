CC = gcc
CFLAGS = -Wall -g
LIBS = -lssl -lcrypto

programa: main.c model/operador.c
	$(CC) $(CFLAGS) main.c model/operador.c -o programa $(LIBS)

clean:
	del programa.exe