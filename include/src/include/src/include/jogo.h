#ifndef JOGO_H
#define JOGO_H

#include "territorio.h"

/* Tipo de função para resolver ataque:
   recebe ponteiros para atacante e defensor e retorna 1 se atacante venceu a rodada (defensor perdeu 1 tropa), 0 se atacante perdeu 1 tropa */
typedef int (*ResolveFn)(Territorio *at, Territorio *df);

/* Funções de interação / ataque */
int resolver_basico(Territorio *at, Territorio *df);
int resolver_agressivo(Territorio *at, Territorio *df); // exemplo alternativo

/* Interface do jogo */
void iniciar_mapa_exemplo(Mapa *m);
void cadastro_interativo(Mapa *m);
void atacar_interativo(Mapa *m, ResolveFn resolver);
void checar_missoes(Mapa *m);

#endif
