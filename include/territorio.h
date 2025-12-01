#ifndef TERRITORIO_H
#define TERRITORIO_H

#define MAX_NOME_T 64
#define MAX_COR_T  32
#define MAX_CONTINENTE_T 32

typedef struct {
    char nome[MAX_NOME_T];
    char cor[MAX_COR_T];         // cor do jogador (ex: "Vermelho", "Azul")
    char continente[MAX_CONTINENTE_T]; // ex: "Asia", "America do Sul"
    int tropas;
    int dono; // 0 = neutro, 1 = Jogador 1, 2 = Jogador 2
} Territorio;

/* Vetor de territorios (cadastro) */
typedef struct {
    Territorio *arr;
    int tamanho;
    int capacidade;
} Mapa;

/* Funções de mapa / cadastro */
Mapa* mapa_criar(int capacidade_inicial);
void mapa_libera(Mapa *m);
int mapa_adicionar(Mapa *m, Territorio t);
void mapa_listar(Mapa *m);
Territorio* mapa_obter(Mapa *m, int idx); // retorna ponteiro ou NULL
int mapa_buscar_por_nome(Mapa *m, const char *nome);

#endif
