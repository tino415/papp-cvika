#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <unistd.h>

#define MAX 10
#define COUNT_IS_ODD = 1;
#define COUNT_IS_EVEN = 1;

pthread_mutex_t mutex_counting = PTHREAD_MUTEX_INITIALIZER;
pthread_cond_t mutex_is_odd = PTHREAD_COND_INITIALIZER;

int countIsOdd = 0;
int count = 0;

void *addEven() {
    while(1) {
        Sleep(rand()%30);
        pthread_mutex_lock(&mutex_counting);

        while(countIsOdd && count < MAX) {
            pthread_cond_wait(&mutex_is_odd, &mutex_counting);
        }

        if(count < MAX) {
            printf("Is odd\n");

            countIsOdd = !countIsOdd;
            count++;
            pthread_cond_signal(&mutex_is_odd);
        } else {
            pthread_cond_signal(&mutex_is_odd);
            pthread_exit(0);
        }

        pthread_mutex_unlock(&mutex_counting);
    }
}

void *addOdd() {
    while(1) {
        Sleep(rand()%30);
        pthread_mutex_lock(&mutex_counting);

        while(!countIsOdd && count < MAX) {
            pthread_cond_wait(&mutex_is_odd, &mutex_counting);
        }

        if(count < MAX) {
            printf("Is even\n");

            countIsOdd = !countIsOdd;
            count++;
            pthread_cond_signal(&mutex_is_odd);
        } else {
            pthread_cond_signal(&mutex_is_odd);
            pthread_exit(0);
        }

        pthread_mutex_unlock(&mutex_counting);
    }
}

int main() {
    srand(time(NULL));
    pthread_t threadOdd, threadEven;

    pthread_create( &threadOdd, NULL, addOdd, NULL);
    pthread_create( &threadEven, NULL, addEven, NULL);

    pthread_join(threadOdd, NULL);
    pthread_join(threadEven, NULL);

    exit(EXIT_SUCCESS);
}
