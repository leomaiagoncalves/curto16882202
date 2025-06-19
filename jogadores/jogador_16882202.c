#include "jogador_16882202.h"
#include "../baralho.h"
#include <stdio.h>
#include <stdlib.h>

static int meu_id_global;
static int num_cartas_total_rodada;
static Carta minha_mao_global[6];
static int manilha_global;

extern const Carta USADA;

const char* nome_16882202() {
    return "jogador_16882202";
}

void iniciar_16882202(const int id, const int n_jogadores) {
    meu_id_global = id;
}

void nova_rodada_16882202(int rodada, const Carta carta_virada, int n_cartas, const Carta* mao) {
    num_cartas_total_rodada = n_cartas;
    manilha_global = definir_manilha(carta_virada);
    for (int i = 0; i < n_cartas; i++) {
        minha_mao_global[i] = mao[i];
    }
}

int apostar_16882202(const int* apostas) {
    // Aposta simples e segura: 1 se tiver manilha, 0 se não.
    for (int i = 0; i < num_cartas_total_rodada; i++) {
        if (minha_mao_global[i].valor == manilha_global) {
            return 1;
        }
    }
    return 0;
}

// VERSÃO "PARANOICA" E DEFENSIVA
int jogar_16882202(Carta* mesa, int n_cartas_na_mesa, int vitorias) {
    int indice_a_jogar = -1;

    // Tenta achar a primeira carta disponível.
    for (int i = 0; i < num_cartas_total_rodada; i++) {
        if (!carta_foi_usada(minha_mao_global[i])) {
            indice_a_jogar = i;
            break; 
        }
    }

   
    if (indice_a_jogar == -1) {
        indice_a_jogar = 0;
    }
    
    minha_mao_global[indice_a_jogar] = USADA;
    
    return indice_a_jogar;
}
