#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

#include "territorio.h"
#include "jogo.h"
#include "missoes.h"

#define BUFFER 128

/* Implementações de resolver (em main por praticidade) */
int resolver_basico(Territorio *at, Territorio *df) {
    // rola um dado para cada lado
    int *dadoA = (int*) malloc(sizeof(int));
    int *dadoD = (int*) malloc(sizeof(int));
    if (!dadoA || !dadoD) {
        free(dadoA); free(dadoD);
        return 0;
    }
    *dadoA = (rand() % 6) + 1;
    *dadoD = (rand() % 6) + 1;
    printf("Atacante rolou: %d, Defensor rolou: %d\n", *dadoA, *dadoD);
    int resultado = 0;
    if (*dadoA > *dadoD) {
        df->tropas -= 1;
        resultado = 1;
        if (df->tropas <= 0) {
            printf("Território %s conquistado!\n", df->nome);
            df->dono = at->dono;
            // mover uma tropa do atacante para o novo território (se possível)
            if (at->tropas > 1) {
                at->tropas -= 1;
                df->tropas = 1;
            } else {
                df->tropas = 0; // raro, mas mantém coerência
            }
        } else {
            printf("Defensor perdeu 1 tropa. Tropas defensor: %d\n", df->tropas);
        }
    } else {
        at->tropas -= 1;
        resultado = 0;
        printf("Ataque falhou. Atacante perdeu 1 tropa. Tropas atacante: %d\n", at->tropas);
    }
    free(dadoA); free(dadoD);
    return resultado;
}

int resolver_agressivo(Territorio *at, Territorio *df) {
    // exemplo: atacante rola 2 dados (soma), defensor 1 dado
    int *a1 = (int*) malloc(sizeof(int));
    int *a2 = (int*) malloc(sizeof(int));
    int *d1 = (int*) malloc(sizeof(int));
    if (!a1 || !a2 || !d1) { free(a1); free(a2); free(d1); return 0; }
    *a1 = (rand() % 6) + 1;
    *a2 = (rand() % 6) + 1;
    *d1 = (rand() % 6) + 1;
    int somaA = *a1 + *a2;
    int somaD = *d1;
    printf("Atacante rolou: %d + %d = %d, Defensor rolou: %d\n", *a1, *a2, somaA, somaD);
    int resultado = 0;
    if (somaA > somaD) {
        df->tropas -= 1;
        resultado = 1;
        if (df->tropas <= 0) {
            df->dono = at->dono;
            if (at->tropas > 1) { at->tropas -= 1; df->tropas = 1; }
            else df->tropas = 0;
        }
    } else {
        at->tropas -= 1;
        resultado = 0;
    }
    free(a1); free(a2); free(d1);
    return resultado;
}

/* Funções auxiliares locais */
void iniciar_mapa_exemplo(Mapa *m) {
    // Exemplo simplificado contendo alguns territórios de Asia e America do Sul
    Territorio t;

    // Ásia (alguns)
    strncpy(t.nome, "China", MAX_NOME_T); strncpy(t.continente, "Asia", MAX_CONTINENTE_T);
    strncpy(t.cor, "Vermelho", MAX_COR_T); t.tropas = 5; t.dono = 1;
    mapa_adicionar(m, t);

    strncpy(t.nome, "India", MAX_NOME_T); strncpy(t.continente, "Asia", MAX_CONTINENTE_T);
    strncpy(t.cor, "Azul", MAX_COR_T); t.tropas = 4; t.dono = 2;
    mapa_adicionar(m, t);

    strncpy(t.nome, "Russia", MAX_NOME_T); strncpy(t.continente, "Asia", MAX_CONTINENTE_T);
    strncpy(t.cor, "Amarelo", MAX_COR_T); t.tropas = 3; t.dono = 1;
    mapa_adicionar(m, t);

    // America do Sul
    strncpy(t.nome, "Brasil", MAX_NOME_T); strncpy(t.continente, "America do Sul", MAX_CONTINENTE_T);
    strncpy(t.cor, "Verde", MAX_COR_T); t.tropas = 4; t.dono = 2;
    mapa_adicionar(m, t);

    strncpy(t.nome, "Argentina", MAX_NOME_T); strncpy(t.continente, "America do Sul", MAX_CONTINENTE_T);
    strncpy(t.cor, "Laranja", MAX_COR_T); t.tropas = 2; t.dono = 1;
    mapa_adicionar(m, t);
}

void cadastro_interativo(Mapa *m) {
    char nome[BUFFER], cor[BUFFER], continente[BUFFER];
    int tropas, dono;
    printf("\nCadastro de território\n");
    printf("Nome: ");
    if (!fgets(nome, BUFFER, stdin)) return;
    nome[strcspn(nome, "\n")] = '\0';
    printf("Cor do dono (ex: Vermelho): ");
    if (!fgets(cor, BUFFER, stdin)) return;
    cor[strcspn(cor, "\n")] = '\0';
    printf("Continente (ex: Asia, America do Sul): ");
    if (!fgets(continente, BUFFER, stdin)) return;
    continente[strcspn(continente, "\n")] = '\0';
    printf("Número de tropas (inteiro): ");
    if (scanf("%d", &tropas) != 1) { while (getchar() != '\n'); printf("Valor inválido.\n"); return; }
    printf("Dono (1 ou 2): ");
    if (scanf("%d", &dono) != 1) { while (getchar() != '\n'); printf("Valor inválido.\n"); return; }
    while (getchar() != '\n');

    Territorio t;
    strncpy(t.nome, nome, MAX_NOME_T - 1); t.nome[MAX_NOME_T-1] = '\0';
    strncpy(t.cor, cor, MAX_COR_T - 1); t.cor[MAX_COR_T-1] = '\0';
    strncpy(t.continente, continente, MAX_CONTINENTE_T - 1); t.continente[MAX_CONTINENTE_T-1] = '\0';
    t.tropas = tropas; t.dono = dono;
    if (mapa_adicionar(m, t)) printf("Território adicionado com sucesso.\n");
    else printf("Erro ao adicionar território.\n");
}

void atacar_interativo(Mapa *m, ResolveFn resolver) {
    mapa_listar(m);
    int ia, id;
    printf("Escolha índice do território atacante: ");
    if (scanf("%d", &ia) != 1) { while (getchar()!='\n'); printf("Entrada inválida.\n"); return; }
    printf("Escolha índice do território defensor: ");
    if (scanf("%d", &id) != 1) { while (getchar()!='\n'); printf("Entrada inválida.\n"); return; }
    while (getchar() != '\n');

    Territorio *at = mapa_obter(m, ia);
    Territorio *df = mapa_obter(m, id);
    if (!at || !df) { printf("Índices inválidos.\n"); return; }
    if (at->dono == df->dono) { printf("Não é possível atacar território do mesmo dono.\n"); return; }
    if (at->tropas <= 1) { printf("Território atacante não tem tropas suficientes (precisa >1).\n"); return; }

    printf("Atacando %s (dono %d) -> %s (dono %d)\n", at->nome, at->dono, df->nome, df->dono);
    resolver(at, df);

    // limpar tropas negativas
    if (at->tropas < 0) at->tropas = 0;
    if (df->tropas < 0) df->tropas = 0;
}

void checar_missoes(Mapa *m) {
    printf("\n--- Verificação de Missões ---\n");
    for (int jogador = 1; jogador <= 2; ++jogador) {
        int asia = missao_asia(m, jogador);
        int amsul = missao_america_sul(m, jogador);
        printf("Jogador %d: Missão Ásia -> %s | Missão América do Sul -> %s\n",
               jogador,
               asia ? "CONCLUIDA" : "NÃO",
               amsul ? "CONCLUIDA" : "NÃO");
    }
}

/* Main com menu */
int main() {
    srand((unsigned) time(NULL));
    Mapa *map = mapa_criar(8);
    if (!map) { printf("Erro ao criar mapa.\n"); return 1; }

    iniciar_mapa_exemplo(map);

    int opc;
    ResolveFn resolver_atual = resolver_basico;

    do {
        printf("\n==== War Estruturado - Tema 1 ====\n");
        printf("1 - Listar territórios\n");
        printf("2 - Cadastrar novo território\n");
        printf("3 - Atacar (resolver básico)\n");
        printf("4 - Atacar (resolver agressivo)\n");
        printf("5 - Checar missões (Ásia / América do Sul)\n");
        printf("0 - Sair\n");
        printf("Escolha: ");
        if (scanf("%d", &opc) != 1) { while (getchar()!='\n'); opc = -1; }
        while (getchar() != '\n');

        switch (opc) {
            case 1:
                mapa_listar(map);
                break;
            case 2:
                cadastro_interativo(map);
                break;
            case 3:
                resolver_atual = resolver_basico;
                atacar_interativo(map, resolver_atual);
                break;
            case 4:
                resolver_atual = resolver_agressivo;
                atacar_interativo(map, resolver_atual);
                break;
            case 5:
                checar_missoes(map);
                break;
            case 0:
                printf("Saindo... boa sorte na guerra!\n");
                break;
            default:
                printf("Opção inválida.\n");
        }
    } while (opc != 0);

    mapa_libera(map);
    return 0;
}
