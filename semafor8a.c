#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <semaphore.h>
#include <unistd.h>

#define N 2
#define C 5

//TODO solve segmentation fault

sem_t *sem[N];
int ids[N];
int counter = 0;
int stop = 0;

void *incrementer(void *arg) {
	int id = *(int*)arg;
	int i;
	for(i=0; i<C; i++) {
		sleep(1);

		sem_wait(sem[id]);
		printf("Semafor %d incrementing\n", id);
		counter++;
	}

	if(id < N) {
		for(i=0; i<C; i++) {
			sem_post(sem[id+1]);
		}
	}
	
	return NULL;
}

int main(void) {
	int i;

	for(i=0; i<N; i++) { 
		sem[i] = malloc(sizeof(sem_t));
		if(sem_init(sem[i], 0, 0) == -1) {
			printf("\nERROR CREATING SEMAFOR\n");
			exit(EXIT_FAILURE);
		}
	}

	pthread_t *threads[N];

	for(i=0; i<N; i++) {
		ids[i] = i;
		threads[i] = malloc(sizeof(pthread_t));
		pthread_create(threads[i], NULL, incrementer, (void*) &ids[i]);
	}

	
	for(i=0; i<C; i++) {	
		sem_post(sem[0]);
	}

	for(i=0; i<N; i++) {
		pthread_join(*threads[i], NULL);
	}

	for(i=0; i<N; i++) {
		sem_destroy(sem[i]);
		free(sem[i]);
	}

	exit(EXIT_SUCCESS);
}
