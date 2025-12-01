#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "territorio.h"

Mapa* mapa_criar(int capacidade_inicial) {
    Mapa *m = (Mapa*) malloc(sizeof(Mapa));
    if (!m) return NULL;
    m->arr = (Territorio*) calloc(capacidade_inicial, sizeof(Territorio));
    if (!m->arr) { free(m); return NULL; }
    m->tamanho = 0;
    m->capacidade = capacidade_inicial;
    return m;
}

void mapa_libera(Mapa *m) {
    if (!m) return;
    free(m->arr);
    free(m);
}

static int mapa_expandir_if_needed(Mapa *m) {
    if (m->tamanho < m->capacidade) return 1;
    int nova = m->capacidade * 2;
    if (nova <= 0) nova = 4;
    Territorio *tmp = (Territorio*) realloc(m->arr, nova * sizeof(Territorio));
    if (!tmp) return 0;
    m->arr = tmp;
    m->capacidade = nova;
    return 1;
}

int mapa_adicionar(Mapa *m, Territorio t) {
    if (!mapa_expandir_if_needed(m)) return 0;
    m->arr[m->tamanho++] = t;
    return 1;
}

void mapa_listar(Mapa *m) {
    if (!m || m->tamanho == 0) {
        printf("Mapa vazio.\n");
        return;
    }
    printf("\nÍdx | Nome                             | Continente        | Tropas | Dono\n");
    printf("----------------------------------------------------------------------------\n");
    for (int i = 0; i < m->tamanho; ++i) {
        Territorio *t = &m->arr[i];
        printf("%3d | %-32s | %-16s | %6d | %4d\n",
               i, t->nome, t->continente, t->tropas, t->dono);
    }
}

Territorio* mapa_obter(Mapa *m, int idx) {
    if (!m || idx < 0 || idx >= m->tamanho) return NULL;
    return &m->arr[idx];
}

int mapa_buscar_por_nome(Mapa *m, const char *nome) {
    if (!m) return -1;
    for (int i = 0; i < m->tamanho; ++i) {
        if (strcasecmp(m->arr[i].nome, nome) == 0) return i;
    }
    return -1;
}
