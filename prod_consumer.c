#include <stdio.h>
#include <stdlib.h>                /* PRODUTOR - CONSUMIDOR */
#include <semaphore.h>
#include <pthread.h>

#define BSIZE 10   /* Tamanho do buffer */
#define PRODS 100  /* Número máximo de elementos que serão produzidos (opcional) */

typedef struct {
	int buf[BSIZE]; /* Array (buffer) de tamanho BSIZE (10) */
	int nextin;    /* Posição onde próximo elemento produzido será inserido */
	int nextout;   /* posição de onde o próximo elemento consumido será retirado */
	sem_t vazios;  /* Semáforo: Controle das posições vazias */
	sem_t cheios;  /* Semáforo: Controle das posições preenchidas */
	sem_t mex;     /* Semáfore: Controle da Exclusão Mútua */
} buffer_t;

void initbuffer(buffer_t * b)
{
	 /* Inicialmente todas as posições vazias */
	 /* Nenhum elemento foi produzido ainda */
	 /* Controle da exclusão mútua - funciona como semáforo binário */ 
  	b->nextin = 0;
  	b->nextout = 0;
}

double randomn;

void producer(buffer_t *b) /* b é um ponteiro que aponta para buffer_t */
{
	int i; /* Número de elementos que serão produzidos */
	double j;
		
	for (i = 0; i < PRODS; i++) {
		/* Comportamento "Wait": 
				1- Decrementa se maior que zero e passa adiante
				2- Caso contrário (Buffer Cheio): Espera por um "sem_post(&(b->vazios))" */
		/*Controle da exclusão mútua: 
				1- Igual a "1" - ninguém na região crítica - pode produzir 
				2- Igual a "0" - região crítica ocupada - esperar 		*/			
		randomn = drand48();
		for (j = 0; j < (10000*randomn); j++);
			    /* Só para demorar um pouco */
		b->buf[b->nextin++] = i; /* Insere elemento produzido no buffer */
		printf("Produzido %d\n", i); /* Imprime elemento produzido */
		b->nextin %= BSIZE; /* Usa função módulo (Buffer Circular) para determinar próxima posição */ 
		/* Comportamento "Signal": 
				1- Acorda alguém que esteja esperando
				2- Caso contrário: incrementa número de posições ocupadas */
		sem_post(&(b->cheios)); 
		/* Exclusão Mútua (Signal): Libera região crítica */
		sem_post(&(b->mex));

	}
}

void consumer(buffer_t *b) /* b é um ponteiro que aponta para buffer_t */
{
	int item; /* Elemento que será produzido */
	int i;    /* Número de elementos que serão consumidos */
	double j;

	for (i = 0; i < PRODS; i++) {
		/* Comportamento "Wait": 
				1- Decrementa se maior que zero e passa adiante
				2- Caso contrário (Buffer Vazio): Espera por um "sem_post(&(b->cheios))" */
		/*Controle da exclusão mútua: 
				1- Igual a "1" - ninguém na região crítica - pode consumir 
				2- Igual a "0" - região crítica ocupada - esperar 		*/
		randomn = drand48();
		for (j = 0; j < (10000*randomn); j++)
			;    /* Só para demorar um pouco */
		item = b->buf[b->nextout++]; /* item recebe elemento consumido */
		printf("Consumido       %d\n", item); /* imprime elemento consumido - item */
		b->nextout %= BSIZE; /* Usa função módulo (Buffer Circular) para calcular próxima posição*/ 
		/* Comportamento "Signal": 
				1- Acorda alguém que esteja esperando
				2- Caso contrário: incrementa número de posições vazias */
		sem_post(&(b->vazios)); 
		/* Exclusão Mútua (Signal): Libera região crítica */
		sem_post(&(b->mex)); 
	}
}


int main()
{
	pthread_t thprod, thcons;
	pthread_attr_t attr;
	buffer_t buffer;
	pthread_attr_init(&attr);
	pthread_attr_setscope(&attr, PTHREAD_SCOPE_SYSTEM);
	
	initbuffer(&buffer); /* Inicializa o buffer */
	pthread_create(&thprod, &attr, (void *)producer, (void *) &buffer); /*Cria uma thread produtor*/
	pthread_create(&thcons, &attr, (void *)consumer, (void *) &buffer); /*Cria uma thread consumidor*/
	
	pthread_join(thprod, NULL);
  	pthread_join(thcons, NULL);
  	return 0;
}