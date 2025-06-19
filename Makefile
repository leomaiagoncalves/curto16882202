# Makefile final, robusto e à prova de erros de linkagem

CC = gcc
CFLAGS = -Wall -Wextra -std=c99

# Lista de todos os arquivos .c que precisam ser compilados
SOURCES = main.c baralho.c mao.c rodada.c jogo.c jogadores/aleatorio1.c jogadores/aleatorio2.c jogadores/simples.c jogadores/simples2.c jogadores/jogador_16882202.c

# Converte a lista de .c para .o
OBJS = $(SOURCES:.c=.o)

# Nome do executável
TARGET = main

# Regra principal
all: $(TARGET)

# Regra para JUNTAR as peças e criar o 'main'
$(TARGET): $(OBJS)
	@echo ">>> Linkando para criar o programa final..."
	$(CC) $(CFLAGS) -o $(TARGET) $(OBJS)

# Regra para CRIAR as peças (.o) a partir dos códigos (.c)
%.o: %.c
	@echo ">>> Compilando $<..."
	$(CC) $(CFLAGS) -c -o $@ $<

# Regra para criar as peças dos jogadores que estão em uma subpasta
jogadores/%.o: jogadores/%.c
	@echo ">>> Compilando jogador $<..."
	$(CC) $(CFLAGS) -c -o $@ $<

# Regra para limpar tudo
clean:
	@echo "Limpando..."
	rm -f *.o jogadores/*.o $(TARGET)

.PHONY: all clean
