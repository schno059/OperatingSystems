/*

Name: Jacob Schnoor
Date: 2/24/21
Type: Semaphore Deadlock Version

*/

#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <semaphore.h>
#include <unistd.h>

int shared= 0;
void race(void);
void deadlocker(void);
sem_t sem1, sem2;

int main(){
    sem_init(&sem1, 0, 1);
    sem_init(&sem2, 0, 1);
    pthread_t player1, player2, player3;

    pthread_create(&player1, NULL, (void *)race, NULL);
    pthread_create(&player2, NULL, (void *)deadlocker, NULL);
    pthread_create(&player3, NULL, (void *)race, NULL);

    pthread_join(player1, NULL);
    pthread_join(player2, NULL);
    pthread_join(player3, NULL);
    printf("Total Number = %d\n", shared);
    sem_destroy(&sem1);
    sem_destroy(&sem2);
    return 0;
}

void race(void) {
    sem_wait(&sem1);
    sleep(5);
    sem_wait(&sem2);
    long i,tmp;
    for(i=1; i<=200000; i++) {
        tmp = shared;
        tmp = tmp + 1;
        shared = tmp;
    }
    sem_post(&sem2);
    sem_post(&sem1);
}

void deadlocker(void) {
    sem_wait(&sem2);
    sleep(5);
    sem_wait(&sem1);
    long i,tmp;
    for(i=1; i<=4000000; i+=2) {
        tmp = shared;
        tmp = tmp + 1;
        shared = tmp;
    }
    sem_post(&sem1);
    sem_post(&sem2);
}
