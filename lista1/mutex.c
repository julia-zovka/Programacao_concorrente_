#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <stdbool.h>
#include <time.h>
#include <unistd.h>

typedef struct {
    int tampinhas_A ;
    int tampinhas_B;
    bool jogo_ativo;
    pthread_mutex_t mutex;
} Jogo;

Jogo jogo;

// um e outro obri
void* jogador_A(void* arg) {
    for (int i = 0; i < 50; i++) {
        pthread_mutex_lock(&jogo.mutex);

        // Verifica se o jogo deve encerrar
        if (!jogo.jogo_ativo || jogo.tampinhas_A == 0 || jogo.tampinhas_B == 0) {
            jogo.jogo_ativo = false;
            pthread_mutex_unlock(&jogo.mutex);
            break;
        }

        if (rand() % 2 == 0) { // Sucesso
            jogo.tampinhas_A--;
            jogo.tampinhas_B++;
            printf("A acertou! A:%d | B:%d\n", jogo.tampinhas_A, jogo.tampinhas_B);
        } else { // Erro
            printf("A errou! A:%d | B:%d\n", jogo.tampinhas_A, jogo.tampinhas_B);
        }

        pthread_mutex_unlock(&jogo.mutex);
        usleep(10000); 
    }
    return NULL;
}

void* jogador_B(void* arg) {
    for (int i = 0; i < 50; i++) {
        pthread_mutex_lock(&jogo.mutex);

        if (!jogo.jogo_ativo || jogo.tampinhas_B == 0 || jogo.tampinhas_A == 0) {
            jogo.jogo_ativo = false;
            pthread_mutex_unlock(&jogo.mutex);
            break;
        }

        if (rand() % 2 == 0) { // Sucesso
            jogo.tampinhas_B--;
            jogo.tampinhas_A++;
            printf("B acertou! A:%d | B:%d\n", jogo.tampinhas_A, jogo.tampinhas_B);
        } else { 
            printf("B errou! A:%d | B:%d\n", jogo.tampinhas_A, jogo.tampinhas_B);
        }

        pthread_mutex_unlock(&jogo.mutex);
        usleep(10000);
    }
    return NULL;
}

int main() {
    srand(time(NULL));
    pthread_t t1, t2;

    jogo.tampinhas_A = 5;
    jogo.tampinhas_B = 5;
    jogo.jogo_ativo = true;
    pthread_mutex_init(&jogo.mutex, NULL);

    pthread_create(&t1, NULL, jogador_A, NULL);
    pthread_create(&t2, NULL, jogador_B, NULL);

    pthread_join(t1, NULL);
    pthread_join(t2, NULL);

    //final do jogooo
    printf("\n=== RESULTADO FINAL ===\n");
    printf("Jogador A: %d tampinhas\n", jogo.tampinhas_A);
    printf("Jogador B: %d tampinhas\n", jogo.tampinhas_B);

    if (jogo.tampinhas_A < jogo.tampinhas_B) {
        printf("Vencedor: Jogador A\n");
    } else if (jogo.tampinhas_B < jogo.tampinhas_A) {
        printf("Vencedor: Jogador B\n");
    } else {
        printf("Resultado: Empate\n");
    }

    pthread_mutex_destroy(&jogo.mutex);
    return 0;
}