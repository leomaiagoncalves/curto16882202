#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include "baralho.h"

// Definição da carta usada, para ser acessível por outros arquivos
const Carta USADA = { -1, -1 };

// Tabela de conversão de valor para força (4=0, 5=1, ..., 3=9)
static const int forca_valor[] = {
	-1, // 0
	7,  // 1 (A)
	8,  // 2
	9,  // 3
	0,  // 4
	1,  // 5
	2,  // 6
	3,  // 7
	-1, // 8
	-1, // 9
	4,  // 10 (Q)
	5,  // 11 (J)
	6   // 12 (K)
};

// --- Implementação das Funções da Biblioteca ---

int carta_foi_usada(Carta carta) {
    return carta.valor == USADA.valor && carta.naipe == USADA.naipe;
}

void inicializar_baralho(Carta* baralho) {
    int i = 0;
    for (int v = 0; v < 13; v++) {
        if (forca_valor[v] != -1) {
            for (int n = 0; n < 4; n++) {
                baralho[i].valor = v;
                baralho[i].naipe = (Naipe)n;
                i++;
            }
        }
    }
}

void embaralhar(Carta* baralho) {
    srand(time(NULL));
    for (int i = 0; i < TOTAL_CARTAS - 1; i++) {
        int j = i + rand() / (RAND_MAX / (TOTAL_CARTAS - i) + 1);
        Carta t = baralho[j];
        baralho[j] = baralho[i];
        baralho[i] = t;
    }
}

void imprimir_carta(Carta c) {
	if (c.valor == -1) {
		printf("[--] ");
		return;
	}

    switch(c.valor) {
        case AS: printf("[ A"); break;
        case 2: printf("[ 2"); break;
        case 3: printf("[ 3"); break;
        case 4: printf("[ 4"); break;
        case 5: printf("[ 5"); break;
        case 6: printf("[ 6"); break;
        case 7: printf("[ 7"); break;
        case DAMA: printf("[ Q"); break;
        case VALETE: printf("[ J"); break;
        case REI: printf("[ K"); break;
    }

    switch(c.naipe) {
        case OUROS: printf("O] "); break;
        case COPAS: printf("C] "); break;
        case ESPADAS: printf("E] "); break;
        case PAUS: printf("P] "); break;
    }
}

// --- FUNÇÕES OFICIAIS QUE ESTAVAM FALTANDO ---

int get_manilha(const Carta c) {
    if (c.valor == TRES) return QUATRO;
    if (c.valor == SETE) return DAMA;
    if (c.valor == REI) return AS;
    return c.valor + 1;
}

int get_forca(const Carta c, const int manilha) {
    if (c.valor == manilha) return 10 + c.naipe;
    return forca_valor[c.valor];
}
