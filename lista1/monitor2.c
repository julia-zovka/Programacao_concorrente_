#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <unistd.h>
#include <time.h>

typedef struct {
    int readers;
    int writing;
    pthread_mutex_t lock;
    pthread_cond_t ok_to_read;
    pthread_cond_t ok_to_write;
} RW_Monitor;

RW_Monitor monitor = {0, 0, PTHREAD_MUTEX_INITIALIZER, PTHREAD_COND_INITIALIZER, PTHREAD_COND_INITIALIZER};

void start_read(int id) {
    pthread_mutex_lock(&monitor.lock);
    while (monitor.writing) {
        pthread_cond_wait(&monitor.ok_to_read, &monitor.lock);
    }
    monitor.readers++;
    printf("  [Leitor %d] começou a ler.\n", id);
    pthread_mutex_unlock(&monitor.lock);
}

void end_read(int id) {
    pthread_mutex_lock(&monitor.lock);
    monitor.readers--;
    printf("  [Leitor %d] Terminou de ler.\n", id);
    if (monitor.readers == 0) {
        pthread_cond_signal(&monitor.ok_to_write);
    }
    pthread_mutex_unlock(&monitor.lock);
}

void start_write() {
    pthread_mutex_lock(&monitor.lock);
    while (monitor.readers > 0 || monitor.writing) {
        pthread_cond_wait(&monitor.ok_to_write, &monitor.lock);
    }
    monitor.writing = 1;
    pthread_mutex_unlock(&monitor.lock);
}

void end_write() {
    pthread_mutex_lock(&monitor.lock);
    monitor.writing = 0;
    pthread_cond_signal(&monitor.ok_to_write);
    pthread_cond_broadcast(&monitor.ok_to_read);
    pthread_mutex_unlock(&monitor.lock);
}


void* Reader(void* arg) {
    int id = *(int*)arg;
    while (1) {
        start_read(id);
        usleep(500000); // Simula leitura
        end_read(id);
        usleep(100000); // Pausa para evitar que a mesma thread pegue o lock de novo
    }
    return NULL;
}

void* Writer(void* arg) {
    while (1) {
        start_write();
        printf(">>> [ESCRITOR] Escrevendo dados importantes...\n");
        usleep(1000000); // Simula escrita
        printf(">>> [ESCRITOR] Escrita concluída.\n");
        end_write();
        usleep(100000); // Pausa para evitar que a mesma thread pegue o lock de novo

    }
    return NULL;
}

int main() {
    srand(time(NULL));
    int num_leitores = (rand() % 8) + 3; 
    pthread_t threads_l[num_leitores];
    pthread_t thread_e;
    int ids[num_leitores];

    printf("Iniciando Sistema: 1 Escritor | %d Leitores\n\n", num_leitores);

    pthread_create(&thread_e, NULL, Writer, NULL);

    for (int i = 0; i < num_leitores; i++) {
        ids[i] = i + 1;
        pthread_create(&threads_l[i], NULL, Reader, &ids[i]);
    }

    pthread_join(thread_e, NULL);
    return 0;
}