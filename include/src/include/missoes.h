#ifndef MISSOES_H
#define MISSOES_H

#include "territorio.h"

/* Verifica se jogador possui todo o continente (retorna 1 se sim, 0 se não) */
int verifica_continente(Mapa *m, const char *continente, int jogador);

/* Missões definidas (exemplos):
   - Missao 1: Conquistar toda a Asia
   - Missao 2: Conquistar toda a America do Sul
   Retornam 1 se missão completa para jogador, 0 caso contrário.
*/
int missao_asia(Mapa *m, int jogador);
int missao_america_sul(Mapa *m, int jogador);

#endif
