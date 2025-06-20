#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include "baralho.h"

const Carta USADA = { -1, -1 };

int carta_foi_usada(Carta carta) {
    return carta.valor == USADA.valor && carta.naipe == USADA.naipe;
}

void inicializar_baralho(Carta* baralho) {
    int i = 0;
    Valor valores[] = {QUATRO, CINCO, SEIS, SETE, DAMA, VALETE, REI, AS, DOIS, TRES};
    for (int v = 0; v < 10; v++) {
        for (int n = 0; n < 4; n++) {
            baralho[i].valor = valores[v];
            baralho[i].naipe = (Naipe)n;
            i++;
        }
    }
}

void embaralhar(Carta* baralho, int tamanho) {
    srand(time(NULL));
    for (int i = 0; i < tamanho - 1; i++) {
        int j = i + rand() % (tamanho - i);
        Carta temp = baralho[i];
        baralho[i] = baralho[j];
        baralho[j] = temp;
    }
}

void imprimir_valor(Valor v) {
    switch(v) {
        case AS: printf("A"); break;
        case DOIS: printf("2"); break;
        case TRES: printf("3"); break;
        case QUATRO: printf("4"); break;
        case CINCO: printf("5"); break;
        case SEIS: printf("6"); break;
        case SETE: printf("7"); break;
        case DAMA: printf("Q"); break;
        case VALETE: printf("J"); break;
        case REI: printf("K"); break;
    }
}

void imprimir_carta(Carta c) {
    if (carta_foi_usada(c)) {
        printf("[--]");
        return;
    }
    printf("[");
    imprimir_valor(c.valor);
    
    // Usei letras simples para evitar problemas de encoding
    char naipes[] = {'O', 'C', 'E', 'P'};
    printf("%c]", naipes[c.naipe]);
}

int get_manilha(const Carta c) {
    if (c.valor == TRES) return QUATRO;
    if (c.valor == SETE) return DAMA;
    if (c.valor == REI) return AS;
    return c.valor + 1;
}

int get_forca(const Carta c, const int manilha) {
    if (c.valor == manilha) {
        return 10 + c.naipe;
    }
    return c.valor;
}
