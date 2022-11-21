#include <stdio.h>
#include <pthread.h>
#include <semaphore.h>
#include <malloc.h>
#include  <stdlib.h>
#include <time.h>

pthread_mutex_t AB,BC,CD,EB,FA;

void attendre (int d) {
    struct timespec delay;
    delay.tv_sec = d;
    delay.tv_nsec = 0;
    nanosleep(&delay,NULL);
}
void  station_A(int id) {
    printf("metro %d dans la station A\n", id);
    attendre(2);

}
void  station_B(int id) {
    printf("metro %d dans la station B\n", id);
    attendre(2);

}
void  station_C(int id) {
    printf("metro %d dans la station C\n", id);
    attendre(2);
}
void  station_D(int id) {
    //sem_wait(&D);
    printf("metro %d dans la station D\n", id);
    attendre(2);
}
void  station_E(int id) {
    printf("metro %d dans la station E\n", id);
    attendre(2);
    //sem_post(&B);
}
void  station_F(int id) {
    printf("metro %d dans la station F\n", id);
    attendre(2);
}



void * metro(void * arg) {
    int id = abs(rand());
    char depart = (char)arg;


    switch(depart) {
        case 'A':
            station_A(id);
            pthread_mutex_lock(&AB);
            printf("metro %d dans le segment AB\n", id);
            station_B(id);
            pthread_mutex_unlock(&AB);
            pthread_mutex_lock(&BC);
            printf("metro %d dans le segment BC\n", id);
            station_C(id);
            pthread_mutex_unlock(&BC);
            pthread_mutex_lock(&CD);
            printf("metro %d dans le segment CD\n", id);
            station_D(id);
            pthread_mutex_unlock(&CD);
            break;
        case 'F':
            station_F(id);
            pthread_mutex_lock(&FA);
            printf("metro %d dans le segment FA\n", id);
            station_A(id);
            pthread_mutex_unlock(&FA);
            pthread_mutex_lock(&AB);
            printf("metro %d dans le segment AB\n", id);
            station_B(id);
            pthread_mutex_unlock(&AB);
            pthread_mutex_lock(&BC);
            printf("metro %d dans le segment BC\n", id);
            station_C(id);
            pthread_mutex_unlock(&BC);
            pthread_mutex_lock(&CD);
            printf("metro %d dans le segment CD\n", id);
            station_D(id);
            pthread_mutex_unlock(&CD);

            break;
        case 'E':
            station_E(id);
            pthread_mutex_lock(&EB);
            printf("metro %d dans le segment EB\n", id);
            station_B(id);
            pthread_mutex_unlock(&EB);
            pthread_mutex_lock(&BC);
            printf("metro %d dans le segment BC\n", id);
            station_C(id);
            pthread_mutex_unlock(&BC);
            pthread_mutex_lock(&CD);
            printf("metro %d dans le segment CD\n", id);
            station_D(id);
            pthread_mutex_unlock(&CD);
            break;
    }

}
int main(int argc,char ** argv) {
    srand(time(0));

    pthread_t metro1, metro2, metro3, metro4, metro5, metro6;

    pthread_mutex_init(&AB,NULL);
    pthread_mutex_init(&BC,NULL);
    pthread_mutex_init(&CD,NULL);
    pthread_mutex_init(&EB,NULL);
    pthread_mutex_init(&FA,NULL);


    pthread_create(&metro1, NULL, metro, (void*)'A');
    pthread_create(&metro2, NULL, metro, (void *) 'E');
    pthread_create(&metro3, NULL, metro, (void *) 'F');
    pthread_create(&metro4, NULL, metro, (void *) 'A');
    pthread_create(&metro5, NULL, metro, (void *) 'E');
    pthread_create(&metro6, NULL, metro, (void *) 'F');

    pthread_join(metro1, NULL);
    pthread_join(metro2, NULL);
    pthread_join(metro3, NULL);
    pthread_join(metro4, NULL);
    pthread_join(metro5, NULL);
    pthread_join(metro6, NULL);

    return 0;
}
