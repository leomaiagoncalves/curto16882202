#include "jogador_16882202.h"
#include "../baralho.h"
#include <stdio.h>
#include <stdlib.h>

static int meu_id_global;
static int num_cartas_total_rodada;
static Carta minha_mao_global[6];
static int manilha_global;
static int minha_aposta_global;

extern const Carta USADA;

static int get_forca_interna(Carta c) {
    if (c.valor == manilha_global) {
        return 10 + c.naipe;
    }
    switch(c.valor) {
        case 4: return 0;
        case 5: return 1;
        case 6: return 2;
        case 7: return 3;
        case 10: return 4;
        case 11: return 5;
        case 12: return 6;
        case 1: return 7;
        case 2: return 8;
        case 3: return 9;
    }
    return -1;
}

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
    int cartas_fortes = 0;
    for (int i = 0; i < num_cartas_total_rodada; i++) {
        if (get_forca_interna(minha_mao_global[i]) >= 7) {
            cartas_fortes++;
        }
    }
    minha_aposta_global = cartas_fortes;
    return minha_aposta_global;
}

int jogar_16882202(Carta* mesa, int n_cartas_na_mesa, int vitorias) {
    int forca_max_mesa = -1;
    if (n_cartas_na_mesa > 0) {
        for (int i = 0; i < n_cartas_na_mesa; i++) {
            int forca_atual = get_forca_interna(mesa[i]);
            if (forca_atual > forca_max_mesa) {
                forca_max_mesa = forca_atual;
            }
        }
    }

    int indice_escolhido = -1;

    if (vitorias < minha_aposta_global) {
        int idx_menor_ganhadora = -1;
        int forca_menor_ganhadora = 100;
        for (int i = 0; i < num_cartas_total_rodada; i++) {
            if (carta_foi_usada(minha_mao_global[i])) continue;

            int forca_minha_carta = get_forca_interna(minha_mao_global[i]);
            if (forca_minha_carta > forca_max_mesa) {
                if (forca_minha_carta < forca_menor_ganhadora) {
                    idx_menor_ganhadora = i;
                    forca_menor_ganhadora = forca_minha_carta;
                }
            }
        }
        if (idx_menor_ganhadora != -1) {
            indice_escolhido = idx_menor_ganhadora;
        } else {
            int idx_pior_carta = -1;
            int forca_pior_carta = 100;
            for(int i = 0; i < num_cartas_total_rodada; i++) {
                if (carta_foi_usada(minha_mao_global[i])) continue;
                if(get_forca_interna(minha_mao_global[i]) < forca_pior_carta) {
                    forca_pior_carta = get_forca_interna(minha_mao_global[i]);
                    idx_pior_carta = i;
                }
            }
            indice_escolhido = idx_pior_carta;
        }
    } else {
        int idx_maior_perdedora = -1;
        int forca_maior_perdedora = -1;
        for (int i = 0; i < num_cartas_total_rodada; i++) {
            if (carta_foi_usada(minha_mao_global[i])) continue;

            int forca_minha_carta = get_forca_interna(minha_mao_global[i]);
            if (forca_minha_carta < forca_max_mesa) {
                if (forca_minha_carta > forca_maior_perdedora) {
                    idx_maior_perdedora = i;
                    forca_maior_perdedora = forca_minha_carta;
                }
            }
        }
        if (idx_maior_perdedora != -1) {
            indice_escolhido = idx_maior_perdedora;
        } else {
            int idx_pior_carta = -1;
            int forca_pior_carta = 100;
            for(int i = 0; i < num_cartas_total_rodada; i++) {
                if (carta_foi_usada(minha_mao_global[i])) continue;
                if(get_forca_interna(minha_mao_global[i]) < forca_pior_carta) {
                    forca_pior_carta = get_forca_interna(minha_mao_global[i]);
                    idx_pior_carta = i;
                }
            }
            indice_escolhido = idx_pior_carta;
        }
    }
    
    minha_mao_global[indice_escolhido] = USADA;
    
    return indice_escolhido;
}
