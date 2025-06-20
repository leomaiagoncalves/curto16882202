#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "baralho.h"
#include "rodada.h"
#include "mao.h"
#include "jogo.h"

#include "jogadores/jogador_16882202.h"
#include "jogadores/aleatorio2.h"
#include "jogadores/simples.h"
#include "jogadores/simples2.h"

#define NUM_JOGADORES 4

Jogo jogo;

void iniciar_jogadores() {
    // AQUI ESTÁ A ÚNICA MUDANÇA:
    jogo.nomes[0] = nome_jogador_16882202();
    
    jogo.nomes[1] = nome_aleatorio2();
    jogo.nomes[2] = nome_simples();
    jogo.nomes[3] = nome_simples2();

    iniciar_16882202(0, NUM_JOGADORES);
    iniciar_aleatorio2(1, NUM_JOGADORES);
    iniciar_simples(2, NUM_JOGADORES);
    iniciar_simples2(3, NUM_JOGADORES);

    memset(jogo.penalidades, 0, sizeof(jogo.penalidades));
    jogo.jogador_inicial_mao = jogo.jogador_inicial_rodada = 0;
    jogo.num_jogadores = NUM_JOGADORES;
}

void informar_maos_para_jogadores(int rodada, const Rodada* r) {
    nova_rodada_16882202(rodada, r->carta_virada, r->cartas_por_jogador, r->maos[0]);
    nova_rodada_aleatorio2(rodada, r->carta_virada, r->cartas_por_jogador, r->maos[1]);
    nova_rodada_simples(rodada, r->carta_virada, r->cartas_por_jogador, r->maos[2]);
    nova_rodada_simples2(rodada, r->carta_virada, r->cartas_por_jogador, r->maos[3]);
}

void coletar_apostas(Rodada* r) {
    printf("Apostas:\n");

    for (int i = 0; i < NUM_JOGADORES; i++) {
        r->apostas[i] = -1;
    }

    for (int i = 0; i < NUM_JOGADORES; i++) {
        int j = (jogo.jogador_inicial_rodada + i) % NUM_JOGADORES;

        if (j == 0) r->apostas[j] = apostar_16882202(r->apostas);
        else if (j == 1) r->apostas[j] = apostar_aleatorio2(r->apostas);
        else if (j == 2) r->apostas[j] = apostar_simples(r->apostas);
        else if (j == 3) r->apostas[j] = apostar_simples2(r->apostas);

        printf("%s:\t%d\n", jogo.nomes[j], r->apostas[j]);
    }
    printf("\n");
}

int processar_jogadas(Rodada* r, Carta* cartas_na_mesa) {
    int novo_jogador_inicial = jogo.jogador_inicial_mao;

    for (int i = 0; i < jogo.num_jogadores; i++) {
        int j = (jogo.jogador_inicial_mao + i) % NUM_JOGADORES;
        int idx = -1;

        if (j == 0) idx = jogar_16882202(cartas_na_mesa, i, r->vitorias[j]);
        else if (j == 1) idx = jogar_aleatorio2(cartas_na_mesa, i, r->vitorias[j]);
        else if (j == 2) idx = jogar_simples(cartas_na_mesa, i, r->vitorias[j]);
        else if (j == 3) idx = jogar_simples2(cartas_na_mesa, i, r->vitorias[j]);

        if (checar_e_processar_descarte(idx, j, r, cartas_na_mesa)) {
            printf("Jogador %s tentou descartar uma carta invalida e foi eliminado!\n", jogo.nomes[j]);
            if (j == novo_jogador_inicial) {
                novo_jogador_inicial = (novo_jogador_inicial + 1) % jogo.num_jogadores;
            }
        }
    }

    return novo_jogador_inicial;
}

int main() {
    iniciar_jogadores();

    for (int rodada = 1; rodada <= NUM_RODADAS; rodada++) {
        executar_rodada(rodada);
    }

    imprimir_resultado_final();
    return 0;
}
