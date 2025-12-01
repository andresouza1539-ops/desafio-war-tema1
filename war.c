#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#define MAX 3 // quantidade de territórios por jogador

typedef struct {
    char nome[30];
    int tropas;
} Territorio;

void exibirTerritorios(Territorio t[], char jogador[]) {
    printf("\n--- Territórios de %s ---\n", jogador);
    for (int i = 0; i < MAX; i++) {
        printf("%d - %s | Tropas: %d\n", i + 1, t[i].nome, t[i].tropas);
    }
}

void atacar(Territorio atacante[], Territorio defensor[]) {
    int atq, def;

    exibirTerritorios(atacante, "Jogador 1 (Atacante)");
    printf("\nEscolha o território atacante: ");
    scanf("%d", &atq);
    atq--;

    exibirTerritorios(defensor, "Jogador 2 (Defensor)");
    printf("\nEscolha o território defensor: ");
    scanf("%d", &def);
    def--;

    if (atacante[atq].tropas <= 1) {
        printf("\n❌ Esse território não tem tropas suficientes para atacar!\n");
        return;
    }

    int dadoAtq = (rand() % 6) + 1;
    int dadoDef = (rand() % 6) + 1;

    printf("\n🎲 Atacante rolou: %d", dadoAtq);
    printf("\n🛡️ Defensor rolou: %d\n", dadoDef);

    if (dadoAtq > dadoDef) {
        defensor[def].tropas--;
        printf("\n🔥 Ataque bem-sucedido! O defensor perdeu uma tropa.\n");

        if (defensor[def].tropas == 0) {
            printf("🏴 Território conquistado!\n");
            defensor[def].tropas = 1;
            atacante[atq].tropas--;
        }

    } else {
        atacante[atq].tropas--;
        printf("\n❌ Ataque falhou! O atacante perdeu uma tropa.\n");
    }
}

int main() {
    srand(time(NULL));

    Territorio jogador1[MAX] = {
        {"Brasil", 5},
        {"Argentina", 4},
        {"Chile", 3}
    };

    Territorio jogador2[MAX] = {
        {"Canada", 5},
        {"USA", 4},
        {"Mexico", 3}
    };

    int opcao;

    do {
        printf("\n========== JOGO WAR (Versão Simplificada) ==========\n");
        printf("1 - Exibir territórios\n");
        printf("2 - Atacar\n");
        printf("0 - Sair\n");
        printf("Escolha: ");
        scanf("%d", &opcao);

        switch(opcao) {
            case 1:
                exibirTerritorios(jogador1, "Jogador 1");
                exibirTerritorios(jogador2, "Jogador 2");
                break;

            case 2:
                atacar(jogador1, jogador2);
                break;

            case 0:
                printf("\nSaindo do jogo...\n");
                break;

            default:
                printf("\nOpção invalida!\n");
        }

    } while (opcao != 0);

    return 0;
}
