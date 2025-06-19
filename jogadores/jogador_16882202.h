#ifndef JOGADOR_16882202_H
#define JOGADOR_16882202_H

#include "baralho.h"



const char* nome_16882202();

void iniciar_16882202(const int meu_id, const int n_jogadores);

void nova_rodada_16882202(const Carta carta_virada, const int n_cartas, Carta* minha_mao);

int apostar_16882202(const int* apostas);

int jogar_16882202(const int rodada, const int n_jogadas, const Carta* mesa, const int* apostas, const int* vitorias);


#endif 
