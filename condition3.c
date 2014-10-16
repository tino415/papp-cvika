#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <unistd.h>

#define COLOR_NONE 0
#define COLOR_RED 1
#define COLOR_GREEN 2
#define COLOR_ORANGE 3

pthread_mutex_t mutex_color = PTHREAD_MUTEX_INITIALIZER;
pthread_cond_t mutex_last_color = PTHREAD_COND_INITIALIZER;

int last_color = COLOR_NONE;

void *vriteColorRed() {
    int i=10;
    while(i-- > 0) {
        pthread_mutex_lock(&mutex_color);

        while(last_color != COLOR_GREEN && last_color != COLOR_NONE) {
            pthread_cond_signal(&mutex_last_color);
            pthread_cond_wait(&mutex_last_color, &mutex_color);
        }

        printf("RED\n");

        last_color = COLOR_RED;

        pthread_cond_signal( &mutex_last_color );

        pthread_mutex_unlock(&mutex_color);
    }
}

void *writeColorGreen() {
    int i = 10;
    while(i-- > 0) {
        pthread_mutex_lock(&mutex_color);

        while(last_color != COLOR_ORANGE && last_color != COLOR_NONE) {
            pthread_cond_signal(&mutex_last_color);
            pthread_cond_wait(&mutex_last_color, &mutex_color);
        }

        printf("GREEN\n");

        last_color = COLOR_GREEN;

        pthread_cond_signal(&mutex_last_color);

        pthread_mutex_unlock(&mutex_color);
    }
}

void *writeColorOrange() {
    int i = 10;
    while(i-- > 0) {
        pthread_mutex_lock(&mutex_color);

        while(last_color != COLOR_RED && last_color != COLOR_NONE) {
            pthread_cond_signal(&mutex_last_color);
            pthread_cond_wait(&mutex_last_color, &mutex_color);
        }

        printf("ORANGE\n");

        last_color = COLOR_ORANGE;

        pthread_cond_signal(&mutex_last_color);

        pthread_mutex_unlock(&mutex_color);
    }
}

int main() {
    srand(time(NULL));
    pthread_t threadOdd, threadEven, threadOrange;

    pthread_create( &threadOdd, NULL, vriteColorRed, NULL);
    pthread_create( &threadEven, NULL, writeColorGreen, NULL);
    pthread_create( &threadOrange, NULL, writeColorOrange, NULL);

    pthread_join(threadOdd, NULL);
    pthread_join(threadEven, NULL);
    pthread_join(threadOrange, NULL);

    exit(EXIT_SUCCESS);
}
