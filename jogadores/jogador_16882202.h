#ifndef JOGADOR_16882202_H
#define JOGADOR_16882202_H

#include "baralho.h"


const char* nome();

void iniciar(const int id, const int n_jogadores);

void nova_rodada(const Carta carta_virada, const int n_cartas, Carta* mao);

int apostar(const int* apostas);

int jogar(const int rodada, const int n_jogadas, const Carta* mesa, const int* apostas, const int* vitorias);


#endif 
