#include "jogador_16882202.h"
#include "../baralho.h"
#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

static int meu_id_global;
static int num_jogadores_global;
static int num_cartas_total_rodada;
static Carta minha_mao_global[6];
static int manilha_global;
static int minha_aposta_global;

static bool manilhas_em_jogo[4];

extern const Carta USADA;

static int get_forca_interna(Carta c) {
    if (c.valor == -1) return -1;
    if (c.valor == manilha_global) {
        return 10 + c.naipe;
    }
    switch(c.valor) {
        case 4: return 0; case 5: return 1; case 6: return 2;
        case 7: return 3; case 10: return 4; case 11: return 5;
        case 12: return 6; case 1: return 7; case 2: return 8;
        case 3: return 9;
    }
    return -1;
}

const char* nome_16882202() {
    return "Rei dos Piratas";
}

void iniciar_16882202(const int id, const int n_jogadores) {
    meu_id_global = id;
    num_jogadores_global = n_jogadores;
}

void nova_rodada_16882202(int rodada, const Carta carta_virada, int n_cartas, const Carta* mao) {
    num_cartas_total_rodada = n_cartas;
    manilha_global = definir_manilha(carta_virada);
    for (int i = 0; i < n_cartas; i++) {
        minha_mao_global[i] = mao[i];
    }
    for (int i = 0; i < 4; i++) {
        manilhas_em_jogo[i] = true;
    }
}

int apostar_16882202(const int* apostas) {
    int vitorias_provaveis = 0;
    for (int i = 0; i < num_cartas_total_rodada; i++) {
        int forca = get_forca_interna(minha_mao_global[i]);
        if (forca >= 10) {
            bool alguma_manilha_mais_forte_em_jogo = false;
            for (int naipe_rival = forca - 10 + 1; naipe_rival < 4; naipe_rival++) {
                if (manilhas_em_jogo[naipe_rival]) {
                    alguma_manilha_mais_forte_em_jogo = true;
                    break;
                }
            }
            if (!alguma_manilha_mais_forte_em_jogo) {
                vitorias_provaveis++;
            }
        } else if (forca == 9) {
            vitorias_provaveis++;
        }
    }
    minha_aposta_global = vitorias_provaveis;
    return minha_aposta_global;
}

int jogar_16882202(Carta* mesa, int n_cartas_na_mesa, int vitorias) {
    for (int i = 0; i < n_cartas_na_mesa; i++) {
        if (mesa[i].valor == manilha_global) {
            manilhas_em_jogo[mesa[i].naipe] = false;
        }
    }

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
    int vitorias_necessarias = minha_aposta_global - vitorias;
    int cartas_restantes = 0;
    for (int i = 0; i < num_cartas_total_rodada; i++) {
        if (minha_mao_global[i].valor != -1) cartas_restantes++;
    }
    bool modo_urgencia = (vitorias_necessarias >= cartas_restantes && vitorias_necessarias > 0);

    if (vitorias < minha_aposta_global) {
        if (modo_urgencia) {
            int idx_vencedora = -1;
            int forca_vencedora = 101;
            for(int i = 0; i < num_cartas_total_rodada; i++){
                if(minha_mao_global[i].valor == -1) continue;
                int f = get_forca_interna(minha_mao_global[i]);
                if(f > forca_max_mesa && f < forca_vencedora){
                    idx_vencedora = i;
                    forca_vencedora = f;
                }
            }
            indice_escolhido = idx_vencedora;
        } else {
            int idx_vencedora_comum = -1;
            int forca_vencedora_comum = 10;
            for (int i = 0; i < num_cartas_total_rodada; i++) {
                if (minha_mao_global[i].valor == -1) continue;
                int f = get_forca_interna(minha_mao_global[i]);
                if (f >= 10) continue;
                if (f > forca_max_mesa && f < forca_vencedora_comum) {
                    idx_vencedora_comum = i;
                    forca_vencedora_comum = f;
                }
            }
            if (idx_vencedora_comum != -1) {
                indice_escolhido = idx_vencedora_comum;
            } else {
                int idx_vencedora_manilha = -1;
                int forca_vencedora_manilha = 101;
                for (int i = 0; i < num_cartas_total_rodada; i++) {
                    if (minha_mao_global[i].valor == -1) continue;
                    int f = get_forca_interna(minha_mao_global[i]);
                    if (f > forca_max_mesa && f < forca_vencedora_manilha) {
                        idx_vencedora_manilha = i;
                        forca_vencedora_manilha = f;
                    }
                }
                indice_escolhido = idx_vencedora_manilha;
            }
        }
        
        if(indice_escolhido == -1){
            int idx_pior_carta = -1;
            int forca_pior_carta = 101;
            for (int i = 0; i < num_cartas_total_rodada; i++) {
                if (minha_mao_global[i].valor == -1) continue;
                int f = get_forca_interna(minha_mao_global[i]);
                if (f < forca_pior_carta) {
                    idx_pior_carta = i;
                    forca_pior_carta = f;
                }
            }
            indice_escolhido = idx_pior_carta;
        }
    } else {
        int idx_maior_perdedora = -1;
        int forca_maior_perdedora = -1;
        for (int i = 0; i < num_cartas_total_rodada; i++) {
            if (minha_mao_global[i].valor == -1) continue;
            int f = get_forca_interna(minha_mao_global[i]);
            if (f < forca_max_mesa && f > forca_maior_perdedora) {
                idx_maior_perdedora = i;
                forca_maior_perdedora = f;
            }
        }
        if (idx_maior_perdedora != -1) {
            indice_escolhido = idx_maior_perdedora;
        } else {
            int idx_pior_carta = -1;
            int forca_pior_carta = 101;
            for (int i = 0; i < num_cartas_total_rodada; i++) {
                if (minha_mao_global[i].valor == -1) continue;
                int f = get_forca_interna(minha_mao_global[i]);
                if (f < forca_pior_carta) {
                    idx_pior_carta = i;
                    forca_pior_carta = f;
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
