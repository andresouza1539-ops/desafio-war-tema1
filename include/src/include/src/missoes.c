#include <string.h>
#include "missoes.h"

int verifica_continente(Mapa *m, const char *continente, int jogador) {
    if (!m) return 0;
    int encontrou = 0;
    for (int i = 0; i < m->tamanho; ++i) {
        if (strcasecmp(m->arr[i].continente, continente) == 0) {
            encontrou = 1;
            if (m->arr[i].dono != jogador) return 0; // se qualquer territorio do continente não for do jogador -> falha
        }
    }
    return encontrou ? 1 : 0;
}

int missao_asia(Mapa *m, int jogador) {
    return verifica_continente(m, "Asia", jogador);
}

int missao_america_sul(Mapa *m, int jogador) {
    return verifica_continente(m, "America do Sul", jogador)
           || verifica_continente(m, "America_do_Sul", jogador); // aceitar underscores se o usuário usar
}
