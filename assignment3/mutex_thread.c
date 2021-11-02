/*

Name: Jacob Schnoor
Date: 2/24/21
Type: Mutex Lock Version

*/
#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>

int shared= 0;
void race(void);
pthread_mutex_t lock;

int main(){
    pthread_t player1, player2, player3;

    pthread_create(&player1, NULL, (void *)race, NULL);
    pthread_create(&player2, NULL, (void *)race, NULL);
    pthread_create(&player3, NULL, (void *)race, NULL);

    pthread_join(player1, NULL);
    pthread_join(player2, NULL);
    pthread_join(player3, NULL);
    printf("Total Number = %d\n", shared);
    return 0;

}

void race(void) {
    pthread_mutex_lock(&lock);
    long i,tmp;
    for(i=1; i<=200000; i++) {
        tmp = shared;
        tmp = tmp + 1;
        shared = tmp;
    }
    pthread_mutex_unlock(&lock);
}
