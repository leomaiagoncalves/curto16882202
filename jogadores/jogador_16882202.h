#ifndef JOGADOR_16882202_H
#define JOGADOR_16882202_H

#include "../baralho.h" 
const char* nome_16882202();
void iniciar_16882202(const int id, const int n_jogadores);
void nova_rodada_16882202(int rodada, const Carta carta_virada, int n_cartas, const Carta* mao);
int apostar_16882202(const int* apostas);
int jogar_16882202(Carta* cartas_na_mesa, int n_cartas_na_mesa, int vitorias);

#endif 
