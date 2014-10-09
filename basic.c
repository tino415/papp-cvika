#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>

//TODO make it done

typedef struct mthread {
	int id;
	char message[50];
	pthread_t thread;
} MThread;

void *thread_function (void *arg) {
	MThread *thread = arg;
	printf("Hello from thread %s\n", thread->message);
	return 0;
}

int main(void) {
	int id;
	int num_of_threads = -1;

	while(num_of_threads < 0 || num_of_threads > 6) {
		printf("Zadajte pocet threadow(od 0 do 5):\n");
		scanf("%d", &num_of_threads);
	}

	MThread *threads = malloc(num_of_threads*sizeof(MThread));

	for(id = 0; id < num_of_threads; id++) {
		printf("Zadajte spravu pre thread %d\n", id);
		scanf("%s", threads[id].message);
	}

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
