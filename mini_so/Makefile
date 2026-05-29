# Makefile do projeto Mini-SO
# Comando principal: make

CC = gcc
CFLAGS = -Wall -Wextra -std=c99 -Iinclude
SRC = src/main.c src/processo.c src/fila.c src/memoria.c src/simulador.c
OUT = build/mini_so

all:
	$(CC) $(CFLAGS) $(SRC) -o $(OUT)

run: all
	./$(OUT)

clean:
	rm -f $(OUT) logs/*.txt
