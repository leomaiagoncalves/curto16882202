#include "jogador_16882202.h"
#include "../baralho.h"
#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <math.h>

static int meu_id_global;
static int num_jogadores_global;
static int num_cartas_total_rodada;
static Carta minha_mao_global[6];
static int manilha_global;
static int minha_aposta_global;

static bool tracker_manilhas[4];
static bool tracker_tres[4];
static bool tracker_dois[4];
static bool tracker_as[4];

extern const Carta USADA;

static int get_forca_interna(Carta c) {
    if (c.valor == -1) return -1;
    if (c.valor == manilha_global) return 10 + c.naipe;
    switch(c.valor) {
        case QUATRO: return 0; case CINCO: return 1; case SEIS: return 2;
        case SETE: return 3; case DAMA: return 4; case VALETE: return 5;
        case REI: return 6; case AS: return 7; case DOIS: return 8;
        case TRES: return 9;
    }
    return -1;
}

static void atualizar_trackers(const Carta* mesa, int n_cartas_na_mesa) {
    for (int i = 0; i < n_cartas_na_mesa; i++) {
        Carta c = mesa[i];
        if (c.valor == manilha_global) tracker_manilhas[c.naipe] = false;
        else if (c.valor == TRES) tracker_tres[c.naipe] = false;
        else if (c.valor == DOIS) tracker_dois[c.naipe] = false;
        else if (c.valor == AS) tracker_as[c.naipe] = false;
    }
}

const char* nome_jogador_16882202() {
    return "jogador_16882202";
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
        tracker_manilhas[i] = true;
        tracker_tres[i] = true;
        tracker_dois[i] = true;
        tracker_as[i] = true;
    }
}

int apostar_16882202(const int* apostas) {
    int num_manilhas = 0;
    bool tem_o_3 = false;
    for (int i = 0; i < num_cartas_total_rodada; i++) {
        int forca = get_forca_interna(minha_mao_global[i]);
        if (forca >= 10) num_manilhas++;
        if (forca == 9) tem_o_3 = true;
    }

    int aposta_ideal;
    if (num_manilhas > 0) {
        aposta_ideal = num_manilhas + (tem_o_3 ? 1 : 0);
    } else {
        aposta_ideal = (tem_o_3 ? 1 : 0);
    }
    
    if (aposta_ideal > num_cartas_total_rodada) {
        aposta_ideal = num_cartas_total_rodada;
    }

    int soma_apostas_anteriores = 0;
    for (int i = 0; i < num_jogadores_global; i++) {
        if (apostas[i] != -1) {
            soma_apostas_anteriores += apostas[i];
        }
    }

    if (soma_apostas_anteriores + aposta_ideal > num_cartas_total_rodada) {
        minha_aposta_global = aposta_ideal > 0 ? aposta_ideal - 1 : 0;
    } else {
        minha_aposta_global = aposta_ideal;
    }
    
    return minha_aposta_global;
}

int jogar_16882202(Carta* mesa, int n_cartas_na_mesa, int vitorias) {
    atualizar_trackers(mesa, n_cartas_na_mesa);

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
        if (n_cartas_na_mesa == 0) {
            int idx_lider = -1;
            int forca_lider = -1;
            for (int i = 0; i < num_cartas_total_rodada; i++) {
                if (minha_mao_global[i].valor == -1) continue;
                int f = get_forca_interna(minha_mao_global[i]);
                if (f < 10 && f > forca_lider) {
                    idx_lider = i;
                    forca_lider = f;
                }
            }
            if (idx_lider != -1) {
                indice_escolhido = idx_lider;
            } else {
                forca_lider = 101;
                for (int i = 0; i < num_cartas_total_rodada; i++) {
                    if (minha_mao_global[i].valor == -1) continue;
                    int f = get_forca_interna(minha_mao_global[i]);
                    if (f < forca_lider) {
                        idx_lider = i;
                        forca_lider = f;
                    }
                }
                indice_escolhido = idx_lider;
            }
        } else if (modo_urgencia) {
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
