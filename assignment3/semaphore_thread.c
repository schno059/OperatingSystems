/*

Name: Jacob Schnoor
Date: 2/24/21
Type: Semaphore Version

*/
#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <semaphore.h>

int shared= 0;
void race(void);
sem_t mutex;

int main(){
    sem_init(&mutex, 0, 1);
    pthread_t player1, player2, player3;

    pthread_create(&player1, NULL, (void *)race, NULL);
    pthread_create(&player2, NULL, (void *)race, NULL);
    pthread_create(&player3, NULL, (void *)race, NULL);

    pthread_join(player1, NULL);
    pthread_join(player2, NULL);
    pthread_join(player3, NULL);
    printf("Total Number = %d\n", shared);
    sem_destroy(&mutex);
    return 0;
}

void race(void) {
    sem_wait(&mutex);
    long i,tmp;
    for(i=1; i<=200000; i++) {
        tmp = shared;
        tmp = tmp + 1;
        shared = tmp;
    }
    sem_post(&mutex);
}
