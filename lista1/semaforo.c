#include <stdio.h>
#include <stdlib.h>
#include <semaphore.h>
#include <pthread.h>
#include <unistd.h>
#include <time.h>

#define NUM_MESAS 20 

typedef struct {
    sem_t mesas;
} Restaurante;

typedef struct {
    int id;
    Restaurante *ru;
} Dados;

void *aluno(void *arg) {
    // Recupera os dados e limpa a memória 
    Dados *d = (Dados *)arg;
    int id = d->id;
    Restaurante *r = d->ru;
    free(d); 

    printf("X---Aluno %d chegou no RU e está esperando mesa...\n", id);
    sem_wait(&(r->mesas)); 
    printf("Y---Aluno %d SENTOU para comer.\n", id);
    // comer
    usleep(500000); 
    printf("Z---Aluno %d terminou de comer e LEVANTOU.\n", id);
    sem_post(&(r->mesas));
    return NULL;
}

int main() {
    srand(time(NULL));
    int total_alunos =(rand() % 71) + 30; // 30 a 100 alunos
    pthread_t threads[total_alunos];
    Restaurante ru;

    sem_init(&ru.mesas, 0, NUM_MESAS);

    printf("=== RU ABERTO (Alunos: %d | Mesas: %d) ===\n\n", total_alunos, NUM_MESAS);

    for (int i = 0; i < total_alunos; i++) {
        // Criamos um "pacotinho" de dados para cada thread
        Dados *dados_enviar = malloc(sizeof(Dados));
        dados_enviar->id = i + 1;
        dados_enviar->ru = &ru;

        pthread_create(&threads[i], NULL, aluno, dados_enviar);
    }

    for (int i = 0; i < total_alunos; i++) {
        pthread_join(threads[i], NULL);
    }

    printf("\nO RU fechou. Todos os %d alunos se alimentaram!\n", total_alunos);

    sem_destroy(&ru.mesas);
    return 0;
}

