#include <stdio.h>
#include <stdlib.h>
#include "baralho.h" // Usamos o baralho.h oficial


static int id_16882202;
static int num_cartas_16882202;
static Carta mao_16882202[6];
static int manilha_16882202;
static int minha_aposta_16882202;


void remover_carta_da_mao(int index) {
    for (int i = index; i < num_cartas_16882202 - 1; i++) {
        mao_16882202[i] = mao_16882202[i + 1];
    }
    num_cartas_16882202--;
}



const char* nome_16882202() {
    return "jogador_16882202";
}

void iniciar_16882202(const int meu_id, const int n_jogadores) {
    id_16882202 = meu_id;
}

void nova_rodada_16882202(const Carta carta_virada, const int n_cartas, Carta* minha_mao) {
    num_cartas_16882202 = n_cartas;
    manilha_16882202 = get_manilha(carta_virada); // get_manilha é de baralho.h
    for (int i = 0; i < n_cartas; i++) {
        mao_16882202[i] = minha_mao[i];
    }
}

int apostar_16882202(const int* apostas) {
    int cartas_fortes = 0;
    for (int i = 0; i < num_cartas_16882202; i++) {
        // A função get_forca já lida com a lógica da manilha!
        // Força da manilha > 9. Força de A,2,3 >= 7.
        if (get_forca(mao_16882202[i], manilha_16882202) >= 7) {
            cartas_fortes++;
        }
    }
    minha_aposta_16882202 = cartas_fortes;
    return minha_aposta_16882202;
}

int jogar_16882202(const int rodada, const int n_jogadas, const Carta* mesa, const int* apostas, const int* vitorias) {
    // 1. Achar a carta mais forte na mesa
    int forca_max_mesa = -1;
    if (n_jogadas > 0) {
        for (int i = 0; i < n_jogadas; i++) {
            int forca_atual = get_forca(mesa[i], manilha_16882202);
            if (forca_atual > forca_max_mesa) {
                forca_max_mesa = forca_atual;
            }
        }
    }

    int indice_escolhido = -1;

    // 2. Decidir se queremos ganhar ou perder a mão
    if (vitorias[id_16882202] < minha_aposta_16882202) {
        // === ESTRATÉGIA: TENTAR GANHAR ===
        int idx_menor_ganhadora = -1;
        int forca_menor_ganhadora = 100; // Valor alto

        for (int i = 0; i < num_cartas_16882202; i++) {
            int forca_minha_carta = get_forca(mao_16882202[i], manilha_16882202);
            if (forca_minha_carta > forca_max_mesa) { // Se a carta ganha
                if (forca_minha_carta < forca_menor_ganhadora) {
                    idx_menor_ganhadora = i;
                    forca_menor_ganhadora = forca_minha_carta;
                }
            }
        }

        if (idx_menor_ganhadora != -1) {
            indice_escolhido = idx_menor_ganhadora; // Joga a mais fraca que ainda ganha
        } else {
            // Não consigo ganhar, descarto a pior carta
            int idx_pior_carta = 0;
            int forca_pior_carta = get_forca(mao_16882202[0], manilha_16882202);
            for(int i = 1; i < num_cartas_16882202; i++) {
                if(get_forca(mao_16882202[i], manilha_16882202) < forca_pior_carta) {
                    forca_pior_carta = get_forca(mao_16882202[i], manilha_16882202);
                    idx_pior_carta = i;
                }
            }
            indice_escolhido = idx_pior_carta;
        }
    } else {
        // === ESTRATÉGIA: TENTAR PERDER ===
        int idx_maior_perdedora = -1;
        int forca_maior_perdedora = -1; // Valor baixo

        for (int i = 0; i < num_cartas_16882202; i++) {
            int forca_minha_carta = get_forca(mao_16882202[i], manilha_16882202);
            if (forca_minha_carta < forca_max_mesa) { // Se a carta perde
                if (forca_minha_carta > forca_maior_perdedora) {
                    idx_maior_perdedora = i;
                    forca_maior_perdedora = forca_minha_carta;
                }
            }
        }
        
        if (idx_maior_perdedora != -1) {
            indice_escolhido = idx_maior_perdedora; // Joga a mais forte que ainda perde
        } else {
            // Forçado a ganhar, joga a carta mais fraca para minimizar o dano
             int idx_pior_carta = 0;
            int forca_pior_carta = get_forca(mao_16882202[0], manilha_16882202);
            for(int i = 1; i < num_cartas_16882202; i++) {
                if(get_forca(mao_16882202[i], manilha_16882202) < forca_pior_carta) {
                    forca_pior_carta = get_forca(mao_16882202[i], manilha_16882202);
                    idx_pior_carta = i;
                }
            }
            indice_escolhido = idx_pior_carta;
        }
    }
    
    remover_carta_da_mao(indice_escolhido);
    
    return indice_escolhido;
}
