#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <unistd.h>

typedef struct mthread {
	int id;
	char message[50];
	pthread_t thread;
} MThread;

pthread_mutex_t condition_mutex = PTHREAD_MUTEX_INITIALIZER;

void *thread_function (void *arg) {
	MThread *thread = arg;
	int i;
	#ifdef __linux__
	sleep(rand());
	#else
	Sleep(rand());
	#endif

	pthread_mutex_lock( &condition_mutex );

	for(i = 0; i < 3; i++) {
		#ifdef __linux__
		sleep(1);
		#else
	    Sleep(1);
		#endif
	    printf("%d in critical place\n", thread->id);
	}

	pthread_mutex_unlock( &condition_mutex );

	return 0;
}

int main(void) {
	int id;
	int num_of_threads = -1;

	srand(time(NULL));

	while(num_of_threads < 0 || num_of_threads > 6) {
		printf("Zadajte pocet threadow(od 0 do 5):\n");
		scanf("%d", &num_of_threads);
	}

	MThread *threads = malloc(num_of_threads*sizeof(MThread));

	for(id = 0; id < num_of_threads; id++) {
		threads[id].id = id;
		pthread_create(&(threads[id].thread), NULL, &thread_function, (void*) &(threads[id]));
	}

	for(id = 0; id < num_of_threads; id++) {
		pthread_join(threads[id].thread, NULL);
	}

	free(threads);
	return 0;
}
