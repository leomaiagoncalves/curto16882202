#ifndef BARALHO_H
#define BARALHO_H

#include "carta.h"

#define TOTAL_CARTAS 40

extern const Carta USADA;

void inicializar_baralho(Carta* baralho);
void embaralhar(Carta* baralho, int tamanho);
void imprimir_valor(Valor v);
void imprimir_carta(Carta c);
int carta_foi_usada(Carta carta);

int get_forca(const Carta c, const int manilha);
int get_manilha(const Carta c);

#endif
