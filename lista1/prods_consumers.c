#include <stdio.h>
#include <stdlib.h>
#include <semaphore.h>
#include <pthread.h>
#include <unistd.h>

#define BSIZE 10 
#define NUM_PRODUCERS 3  
#define MESSAGES 50 
#define MESSAGE_SIZE 256


typedef struct {
    int thread_id ;
    char text[MESSAGE_SIZE];
}message;

typedef struct {
    message buf[BSIZE];
    int nextin;
    int nextout;
    sem_t vazios; 
    sem_t cheios; 
    sem_t mex;    
} buffer_t;

void initbuffer(buffer_t * b) {
    b->nextin = 0;
    b->nextout = 0;
    sem_init(&(b->vazios), 0, BSIZE); // Começa com 10 espaços livres
    sem_init(&(b->cheios), 0, 0);     // Começa com 0 itens ocupados
    sem_init(&(b->mex), 0, 1);        // Mutex começa em 1 (aberto)
}

void *audio_thread(void *arg) {
    buffer_t *b = (buffer_t *)arg;
    int id = (int)pthread_self();

    for (int i = 0; i < MESSAGES; i++) {
        sem_wait(&(b->vazios)); // Espera ter espaço
        sem_wait(&(b->mex));    // Entra na Região Crítica

        b->buf[b->nextin].thread_id = id;
        sprintf(b->buf[b->nextin].text, "audio_thread mensagem de numero %d", i + 1);

        b->nextin = (b->nextin + 1) % BSIZE;
        sem_post(&(b->mex));    // Sai da Região Crítica
        sem_post(&(b->cheios)); // Avisa que tem um item novo
        usleep(100000); // Pequeno delay para visualizarmos a alternância
    }
    return NULL;
}

void *video_thread(void *arg) {
        buffer_t *b = (buffer_t *)arg;
    int id = (int)pthread_self();

    for (int i = 0; i < MESSAGES; i++) {
        sem_wait(&(b->vazios)); // Espera ter espaço
        sem_wait(&(b->mex));    // Entra na Região Crítica

        b->buf[b->nextin].thread_id = id;
        sprintf(b->buf[b->nextin].text, "video_thread mensagem de numero %d", i + 1);

        b->nextin = (b->nextin + 1) % BSIZE;
        sem_post(&(b->mex));    // Sai da Região Crítica
        sem_post(&(b->cheios)); // Avisa que tem um item novo
        usleep(100000); // Pequeno delay para visualizarmos a alternância
    }
    return NULL;
}

void *input_thread(void *arg) {
        buffer_t *b = (buffer_t *)arg;
    int id = (int)pthread_self();

    for (int i = 0; i < MESSAGES; i++) {
        sem_wait(&(b->vazios)); // Espera ter espaço
        sem_wait(&(b->mex));    // Entra na Região Crítica

        b->buf[b->nextin].thread_id = id;
        sprintf(b->buf[b->nextin].text, "input_thread mensagem de numero %d", i + 1);

        b->nextin = (b->nextin + 1) % BSIZE;
        sem_post(&(b->mex));    // Sai da Região Crítica
        sem_post(&(b->cheios)); // Avisa que tem um item novo
        usleep(100000); // Pequeno delay para visualizarmos a alternância
    }
    return NULL;
}

void *log_thread(void *arg) {
    buffer_t *b = (buffer_t *)arg;
    for (int i = 0; i < MESSAGES*3; i++) {
        sem_wait(&(b->cheios)); // Espera ter algo para comer
        sem_wait(&(b->mex));  
        
        message ms = b->buf[b->nextout];
        printf("[Thread (%d)]: %s \n",ms.thread_id,ms.text);


        b->nextout = (b->nextout + 1) % BSIZE;
        sem_post(&(b->mex));    // Sai da Região Crítica
        sem_post(&(b->vazios)); // Avisa que liberou um espaço
        usleep(100000); // Consumidor um pouco mais lento
    }
    return NULL;
}

int main() {
    pthread_t thprod1,thprod2,thprod3, thcons;
    buffer_t buffer;

    initbuffer(&buffer);

    pthread_create(&thprod1, NULL, audio_thread, &buffer);
    pthread_create(&thprod2, NULL, video_thread, &buffer);
    pthread_create(&thprod3, NULL, input_thread, &buffer);

    pthread_create(&thcons, NULL, log_thread, &buffer);

    pthread_join(thprod1, NULL);
    pthread_join(thprod2, NULL);
    pthread_join(thprod3, NULL);
    pthread_join(thcons, NULL);

    // Destruir semáforos ao finalizar
    sem_destroy(&buffer.vazios);
    sem_destroy(&buffer.cheios);
    sem_destroy(&buffer.mex);

    return 0;
}