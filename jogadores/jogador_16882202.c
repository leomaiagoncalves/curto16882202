#include <stdio.h>
#include <stdlib.h>
#include "baralho.h"



static int meu_id_global;
static int num_cartas_atuais;
static Carta minha_mao_global[6]; 
static int manilha_global;
static int minha_aposta_global;


static void remover_carta_da_mao_interna(int index) {
    for (int i = index; i < num_cartas_atuais - 1; i++) {
        minha_mao_global[i] = minha_mao_global[i + 1];
    }
    num_cartas_atuais--;
}


const char* nome() {
	return "jogador_16882202";
}

void iniciar(const int id, const int n_jogadores) {
	meu_id_global = id;
}

void nova_rodada(const Carta carta_virada, const int n_cartas, Carta* mao) {
    num_cartas_atuais = n_cartas;
    manilha_global = get_manilha(carta_virada); 

    for (int i = 0; i < n_cartas; i++) {
        minha_mao_global[i] = mao[i];
    }
}

int apostar(const int* apostas) {
	// Estratégia de aposta: contar o número de "cartas fortes".
    int cartas_fortes = 0;
    for (int i = 0; i < num_cartas_atuais; i++) {
        if (get_forca(minha_mao_global[i], manilha_global) >= 7) {
            cartas_fortes++;
        }
    }
    minha_aposta_global = cartas_fortes;
	return minha_aposta_global;
}

int jogar(const int rodada, const int n_jogadas, const Carta* mesa, const int* apostas, const int* vitorias) {
    // 1. Achar a carta mais forte que já está na mesa
    int forca_max_mesa = -1;
    if (n_jogadas > 0) {
        for (int i = 0; i < n_jogadas; i++) {
            int forca_atual = get_forca(mesa[i], manilha_global);
            if (forca_atual > forca_max_mesa) {
                forca_max_mesa = forca_atual;
            }
        }
    }

    int indice_escolhido = -1;

    // 2. Decide a estratégia: ganhar ou perder?
    if (vitorias[meu_id_global] < minha_aposta_global) {
        // --- ESTRATÉGIA: TENTAR GANHAR ---
        int idx_menor_ganhadora = -1;
        int forca_menor_ganhadora = 100; // Valor artificialmente alto

        // Encontra a carta mais fraca que ainda seja capaz de ganhar a mão
        for (int i = 0; i < num_cartas_atuais; i++) {
            int forca_minha_carta = get_forca(minha_mao_global[i], manilha_global);
            if (forca_minha_carta > forca_max_mesa) { // Se a carta ganha...
                if (forca_minha_carta < forca_menor_ganhadora) { // ...e é a mais fraca até agora
                    idx_menor_ganhadora = i;
                    forca_menor_ganhadora = forca_minha_carta;
                }
            }
        }

        if (idx_menor_ganhadora != -1) {
            indice_escolhido = idx_menor_ganhadora; // Joga a mais fraca que ganha
        } else {
            // Se não pode ganhar, joga a pior carta para descartar
            int idx_pior_carta = 0;
            int forca_pior_carta = get_forca(minha_mao_global[0], manilha_global);
            for(int i = 1; i < num_cartas_atuais; i++) {
                if(get_forca(minha_mao_global[i], manilha_global) < forca_pior_carta) {
                    forca_pior_carta = get_forca(minha_mao_global[i], manilha_global);
                    idx_pior_carta = i;
                }
            }
            indice_escolhido = idx_pior_carta;
        }
    } else {
        // --- ESTRATÉGIA: TENTAR PERDER ---
        int idx_maior_perdedora = -1;
        int forca_maior_perdedora = -1; // Valor baixo

        // Encontra a carta mais forte que ainda perde a mão
        for (int i = 0; i < num_cartas_atuais; i++) {
            int forca_minha_carta = get_forca(minha_mao_global[i], manilha_global);
            if (forca_minha_carta < forca_max_mesa) { // Se a carta perde...
                if (forca_minha_carta > forca_maior_perdedora) { // ...e é a mais forte que perde
                    idx_maior_perdedora = i;
                    forca_maior_perdedora = forca_minha_carta;
                }
            }
        }
        
        if (idx_maior_perdedora != -1) {
            indice_escolhido = idx_maior_perdedora; // Joga a mais forte que perde
        } else {
            // Se todas as cartas ganham, é forçado a vencer.
            // Joga a mais fraca delas para "minimizar o dano".
            int idx_pior_carta = 0;
            int forca_pior_carta = get_forca(minha_mao_global[0], manilha_global);
            for(int i = 1; i < num_cartas_atuais; i++) {
                if(get_forca(minha_mao_global[i], manilha_global) < forca_pior_carta) {
                    forca_pior_carta = get_forca(minha_mao_global[i], manilha_global);
                    idx_pior_carta = i;
                }
            }
            indice_escolhido = idx_pior_carta;
        }
    }

    remover_carta_da_mao_interna(indice_escolhido);
    
    return indice_escolhido;
}
