#include <stdio.h>
#include <stdlib.h>
#include <semaphore.h>
#include <pthread.h>
#include <unistd.h>

#define BSIZE 10   
#define PRODS 20  // Diminuí para o log ficar legível

typedef struct {
    int buf[BSIZE];
    int nextin;
    int nextout;
    sem_t vazios; 
    sem_t cheios; 
    sem_t mex;    
} buffer_t;

void initbuffer(buffer_t * b) {
    b->nextin = 0;
    b->nextout = 0;
    // Inicialização dos Semáforos:
    sem_init(&(b->vazios), 0, BSIZE); // Começa com 10 espaços livres
    sem_init(&(b->cheios), 0, 0);     // Começa com 0 itens ocupados
    sem_init(&(b->mex), 0, 1);        // Mutex começa em 1 (aberto)
}

void *producer(void *arg) {
    buffer_t *b = (buffer_t *)arg;
    for (int i = 0; i < PRODS; i++) {
        sem_wait(&(b->vazios)); // Espera ter espaço
        sem_wait(&(b->mex));    // Entra na Região Crítica

        b->buf[b->nextin] = i;
        printf("Produzido: %d\n", i);
        b->nextin = (b->nextin + 1) % BSIZE;

        sem_post(&(b->mex));    // Sai da Região Crítica
        sem_post(&(b->cheios)); // Avisa que tem um item novo
        
        usleep(100000); // Pequeno delay para visualizarmos a alternância
    }
    return NULL;
}

void *consumer(void *arg) {
    buffer_t *b = (buffer_t *)arg;
    int item;
    for (int i = 0; i < PRODS; i++) {
        sem_wait(&(b->cheios)); // Espera ter algo para comer
        sem_wait(&(b->mex));    // Entra na Região Crítica

        item = b->buf[b->nextout];
        printf("Consumido:       %d\n", item);
        b->nextout = (b->nextout + 1) % BSIZE;

        sem_post(&(b->mex));    // Sai da Região Crítica
        sem_post(&(b->vazios)); // Avisa que liberou um espaço
        
        usleep(100000); // Consumidor um pouco mais lento
    }
    return NULL;
}

int main() {
    pthread_t thprod, thcons;
    buffer_t buffer;

    initbuffer(&buffer);

    pthread_create(&thprod, NULL, producer, &buffer);
    pthread_create(&thcons, NULL, consumer, &buffer);

    pthread_join(thprod, NULL);
    pthread_join(thcons, NULL);

    // Destruir semáforos ao finalizar
    sem_destroy(&buffer.vazios);
    sem_destroy(&buffer.cheios);
    sem_destroy(&buffer.mex);

    return 0;
}