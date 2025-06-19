CC = gcc
CFLAGS = -Wall -Wextra -std=c99
JOGADORES = jogadores/aleatorio1.c jogadores/aleatorio2.c jogadores/simples.c jogadores/simples2.c jogadores/jogador_16882202.c
OBJ = baralho.o mao.o rodada.o jogo.o

all: main

main:
	$(CC) $(CFLAGS) -o main main.c baralho.c mao.c rodada.c jogo.c $(JOGADORES)

teste_baralho: baralho.c teste_baralho.c
	$(CC) $(CFLAGS) -o teste_baralho baralho.c teste_baralho.c

teste_mao: $(OBJ) teste_mao.c
	$(CC) $(CFLAGS) -o teste_mao $(OBJ) teste_mao.c

teste_rodada: rodada.c baralho.c teste_rodada.c
	$(CC) $(CFLAGS) -o teste_rodada rodada.c baralho.c teste_rodada.c

clean:
	rm -f *.o teste_baralho teste_mao main
