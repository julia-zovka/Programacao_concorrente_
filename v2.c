// multiplos consumidores e produtotes
#include <stdio.h>
#include <stdlib.h>
#include <semaphore.h>
#include <pthread.h>
#include <unistd.h>

#define BSIZE 10   
#define PRODS 20  

#define N_PROD 3  
#define N_CONS 3  


typedef struct {
    int buf[BSIZE];
    int nextin;
    int nextout;
    sem_t vazios; 
    sem_t cheios; 
    sem_t mex;    
} buffer_t;


buffer_t b;

void initbuffer(buffer_t * b) {
    b->nextin = 0;
    b->nextout = 0;
    sem_init(&(b->vazios), 0, BSIZE); // Começa com 10 espaços livres
    sem_init(&(b->cheios), 0, 0);     // Começa com 0 itens ocupados
    sem_init(&(b->mex), 0, 1);        // Mutex começa em 1 (aberto)
}

void *producer(void *arg) {
    int my_id = *(int *)arg; 

    for (int i = 0; i < PRODS; i++) {
        sem_wait(&(b.vazios)); // Espera ter espaço
        sem_wait(&(b.mex));    // Entra na Região Crítica

        b.buf[b.nextin] = i;
        printf("Produtor [%d] produziu: %d\n", my_id, i);
        b.nextin = (b.nextin + 1) % BSIZE;

        sem_post(&(b.mex));    // Sai da Região Crítica
        sem_post(&(b.cheios)); // Avisa que tem um item novo
        
        usleep(100000); // Pequeno delay para visualizarmos a alternância
    }
    return NULL;
}

void *consumer(void *arg) {
    int my_id = *(int *)arg; 

    int item;
    for (int i = 0; i < PRODS; i++) {
        sem_wait(&(b.cheios)); // Espera ter algo para comer
        sem_wait(&(b.mex));    // Entra na Região Crítica

        item = b.buf[b.nextout];
        printf("Consumidor [%d] consumiu: %d\n", my_id, item);
        b.nextout = (b.nextout + 1) % BSIZE;
        sem_post(&(b.mex));    // Sai da Região Crítica
        sem_post(&(b.vazios)); // Avisa que liberou um espaço
        
        usleep(100000); // Consumidor um pouco mais lento
    }
    return NULL;
}

int main() {

    pthread_t threads_prod[N_PROD];
    pthread_t threads_cons[N_CONS];
    int id_p[N_PROD], id_c[N_CONS]; // Arrays para guardar os IDs

    initbuffer(&b);
    
    for(int i = 0; i < N_PROD; i++) {
        id_p[i] = i + 1;
        pthread_create(&threads_prod[i], NULL, producer, (void *)&id_p[i]);
    }

    for(int i = 0; i < N_CONS; i++) {
        id_c[i] = i + 1;
        pthread_create(&threads_cons[i], NULL, consumer,(void *)&id_c[i]);
    }

    for(int i = 0; i < N_PROD; i++) {
        pthread_join(threads_prod[i], NULL);
    }

    for(int i = 0; i < N_CONS; i++) {
        pthread_join(threads_cons[i], NULL);
    }

    // Destruir semáforos ao finalizar
    sem_destroy(&b.vazios);
    sem_destroy(&b.cheios);
    sem_destroy(&b.mex);

    return 0;
}