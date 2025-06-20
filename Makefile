CC = gcc
CFLAGS = -Wall -Wextra -std=c99 -g

SOURCES = main.c baralho.c mao.c rodada.c jogo.c jogadores/aleatorio1.c jogadores/aleatorio2.c jogadores/simples.c jogadores/simples2.c jogadores/jogador_16882202.c
OBJS = $(SOURCES:.c=.o)
TARGET = main

all: $(TARGET)

$(TARGET): $(OBJS)
	$(CC) $(CFLAGS) -o $(TARGET) $(OBJS)

%.o: %.c
	$(CC) $(CFLAGS) -c -o $@ $<

jogadores/%.o: jogadores/%.c
	$(CC) $(CFLAGS) -c -o $@ $<

clean:
	rm -f *.o jogadores/*.o $(TARGET)
