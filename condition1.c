#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <unistd.h>

#define NUM_OF_THREADS 5

int sum;

typedef struct mthread {
	int id;
	char message[50];
	pthread_t thread;
} MThread;

pthread_mutex_t condition_mutex = PTHREAD_MUTEX_INITIALIZER;

void *thread_function (void *arg) {
	MThread *thread = arg;
	int i;
	Sleep(rand());

	pthread_mutex_lock( &condition_mutex );

	for(i = 0; i < (thread->id+1); i++) {
	    Sleep(1);
	    sum += NUM_OF_THREADS;
	}

	pthread_mutex_unlock( &condition_mutex );

	return 0;
}

int main(void) {
	int id;

	srand(time(NULL));

	MThread threads[NUM_OF_THREADS];

	for(id = 0; id < NUM_OF_THREADS; id++) {
		threads[id].id = id;
		pthread_create(&(threads[id].thread), NULL, &thread_function, (void*) &(threads[id]));
	}

	for(id = 0; id < NUM_OF_THREADS; id++) {
		pthread_join(threads[id].thread, NULL);
	}

	printf("SUm is %d\n", sum);

	return 0;
}
