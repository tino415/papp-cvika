#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>

pthread_mutex_t mutex_access = PTHREAD_MUTEX_INITIALIZER;
pthread_cond_t cond_ended = PTHREAD_COND_INITIALIZER;
int waitingFor = 0;

void *writeHello(void *arg) {
	int id = *(int*)arg;
	printf("Hellow from thread %d\n", id);

	pthread_mutex_lock(&mutex_access);

	waitingFor--;
	pthread_cond_signal(&cond_ended);

	pthread_mutex_unlock(&mutex_access);
	return 0;
}

int main() {
	pthread_t thread1, thread2;
	int id1 = 1;
	int id2 = 2;
	waitingFor = 2;

	pthread_create( &thread1, NULL, writeHello, &id1);
	pthread_create( &thread2, NULL, writeHello, &id2);

	pthread_mutex_lock(&mutex_access);

	while(waitingFor > 0) {
		pthread_cond_wait(&cond_ended, &mutex_access);
	}

	pthread_mutex_unlock(&mutex_access);

	printf("Obidve vlakna skoncili\n");

	exit(EXIT_SUCCESS);
}
