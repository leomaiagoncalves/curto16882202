#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "simples.h"
#include "../baralho.h"

// Variáveis globais para armazenar o estado do jogador
static int id;
static int num_jogadores;
static Carta mao[6];
static int num_cartas;
static int aposta = 0;
static int minhas_vitorias = 0;

static Valor manilha_atual; // para guardar a manilha da rodada

extern int comparar_cartas(Carta a, Carta b, Valor manilha); // se não estiver no header

const char* nome_simples() {
    return "Simples";
}

// Função auxiliar para pegar o índice da maior carta disponível
int indice_maior_carta() {
    int maior = -1;
    for (int i = 0; i < num_cartas; i++) {
        if (!carta_foi_usada(mao[i])) {
            if (maior == -1 || comparar_cartas(mao[i], mao[maior], manilha_atual) > 0) {
                maior = i;
            }
        }
    }
    mao[maior] = USADA;
    return maior;
}

// Função auxiliar para pegar o índice da menor carta disponível
int indice_menor_carta() {
    int menor = -1;
    for (int i = 0; i < num_cartas; i++) {
        if (!carta_foi_usada(mao[i])) {
            if (menor == -1 || comparar_cartas(mao[i], mao[menor], manilha_atual) < 0) {
                menor = i;
            }
        }
    }
    mao[menor] = USADA; // Marca a carta como usada
    return menor;
}

void iniciar_simples(const int meu_id, const int total_jogadores) {
    id = meu_id;
    num_jogadores = total_jogadores;
}

void nova_rodada_simples(const int rodada, const Carta carta_virada, const int n_cartas, Carta* minha_mao) {
    num_cartas = n_cartas;
    minhas_vitorias = 0;
    manilha_atual = (carta_virada.valor + 1) % 10;

    for (int i = 0; i < n_cartas; i++) {
        mao[i] = minha_mao[i];
    }
}

int apostar_simples(const int* apostas) {
    // Apostar a quantidade de cartas maiores ou iguais a Ás
    int aposta = 0;
    for (int i = 0; i < num_cartas; i++)
        if (mao[i].valor >= AS || mao[i].valor == manilha_atual) 
            aposta++;

    return aposta;
}

void resultado_rodada_simples(int vitorias) {
    minhas_vitorias = vitorias;
}

int jogar_simples(const Carta* mesa, const int num_na_mesa, const int vitorias) {
    int idx = -1;
    if (minhas_vitorias < aposta) {
        idx = indice_maior_carta();
    } else {
        idx = indice_menor_carta();
    }
    mao[idx].valor = -1; // Marca como usada
    return idx;
}