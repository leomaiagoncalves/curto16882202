#include "jogador_16882202.h"
#include "../baralho.h"
#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <math.h>

static int meu_id_global;
static int num_cartas_total_rodada;
static Carta minha_mao_global[6];
static int manilha_global;
static int minha_aposta_global;

extern const Carta USADA;

static int avaliar_potencial_carta(Carta c) {
    if (c.valor == -1) return 0;

    if (c.valor == manilha_global) {
        return 70 + (c.naipe * 10); // Paus (naipe 3) = 100, Ouros (naipe 0) = 70
    }
    switch(c.valor) {
        case 3: return 50;
        case 2: return 40;
        case 1: return 30; // AS
        case 12: return 10; // K
        case 11: return 5; // J
        case 10: return 2; // Q
        default: return 1; // 4, 5, 6, 7
    }
}

const char* nome_16882202() {
    return "Yonkou";
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
    float potencial_total = 0;
    for (int i = 0; i < num_cartas_total_rodada; i++) {
        potencial_total += avaliar_potencial_carta(minha_mao_global[i]);
    }
    
    float potencial_medio_por_carta = potencial_total / num_cartas_total_rodada;
    
    if (potencial_medio_por_carta > 60) {
        minha_aposta_global = round(num_cartas_total_rodada * 0.75);
    } else if (potencial_medio_por_carta > 40) {
        minha_aposta_global = round(num_cartas_total_rodada * 0.5);
    } else if (potencial_medio_por_carta > 20) {
        minha_aposta_global = round(num_cartas_total_rodada * 0.25);
    } else {
        minha_aposta_global = 0;
    }

    if (minha_aposta_global > num_cartas_total_rodada) {
        minha_aposta_global = num_cartas_total_rodada;
    }
    return minha_aposta_global;
}

int jogar_16882202(Carta* mesa, int n_cartas_na_mesa, int vitorias) {
    int forca_max_mesa = -1;
    if (n_cartas_na_mesa > 0) {
        for (int i = 0; i < n_cartas_na_mesa; i++) {
            // Usa o potencial para comparar, mas precisa da força real para vencer
            int forca_atual_na_mesa = avaliar_potencial_carta(mesa[i]);
            if (forca_atual_na_mesa > forca_max_mesa) {
                forca_max_mesa = forca_atual_na_mesa;
            }
        }
    }

    int indice_escolhido = -1;

    if (vitorias < minha_aposta_global) {
        // TENTAR GANHAR com a carta de menor potencial que ainda vence
        int idx_candidato = -1;
        int potencial_candidato = 101; 
        for (int i = 0; i < num_cartas_total_rodada; i++) {
            if (minha_mao_global[i].valor == -1) continue;
            int p = avaliar_potencial_carta(minha_mao_global[i]);
            if (p > forca_max_mesa && p < potencial_candidato) {
                idx_candidato = i;
                potencial_candidato = p;
            }
        }

        if (idx_candidato != -1) {
            indice_escolhido = idx_candidato;
        } else {
            // Se não pode ganhar, descarta a de menor potencial
            int idx_pior_carta = -1;
            int potencial_pior_carta = 101;
            for (int i = 0; i < num_cartas_total_rodada; i++) {
                if (minha_mao_global[i].valor == -1) continue;
                int p = avaliar_potencial_carta(minha_mao_global[i]);
                if (p < potencial_pior_carta) {
                    idx_pior_carta = i;
                    potencial_pior_carta = p;
                }
            }
            indice_escolhido = idx_pior_carta;
        }
    } else {
        // TENTAR PERDER com a carta de maior potencial que ainda perde
        int idx_candidato = -1;
        int potencial_candidato = -1;
        for (int i = 0; i < num_cartas_total_rodada; i++) {
            if (minha_mao_global[i].valor == -1) continue;
            int p = avaliar_potencial_carta(minha_mao_global[i]);
            if (p < forca_max_mesa && p > potencial_candidato) {
                idx_candidato = i;
                potencial_candidato = p;
            }
        }
        
        if (idx_candidato != -1) {
            indice_escolhido = idx_candidato;
        } else {
            // Forçado a ganhar, joga a de menor potencial
            int idx_pior_carta = -1;
            int potencial_pior_carta = 101;
            for (int i = 0; i < num_cartas_total_rodada; i++) {
                if (minha_mao_global[i].valor == -1) continue;
                int p = avaliar_potencial_carta(minha_mao_global[i]);
                if (p < potencial_pior_carta) {
                    idx_pior_carta = i;
                    potencial_pior_carta = p;
                }
            }
            indice_escolhido = idx_pior_carta;
        }
    }

    if (indice_escolhido == -1) {
        for(int i = 0; i < num_cartas_total_rodada; i++){
            if(minha_mao_global[i].valor != -1){
                indice_escolhido = i;
                break;
            }
        }
    }
    
    if (indice_escolhido != -1) {
        minha_mao_global[indice_escolhido].valor = -1;
    }
    
    return indice_escolhido;
}
