#include <stdio.h>
#include <pthread.h>
#include <unistd.h>

void* say_hello(void* arg) {
    printf("Salam! Ana thread wahed\n");
    printf("Thread wahed salit\n");
    return NULL;
}

void* say_bye(void* arg) {
    printf("Salam! Ana thread jouj\n");
    printf("Thread jouj salit\n");
    return NULL;
}

int main() {
    pthread_t t1, t2;

    pthread_create(&t1, NULL, say_hello, NULL);
    pthread_create(&t2, NULL, say_bye, NULL);


    pthread_join(t1, NULL);
    pthread_join(t2, NULL);

    printf("Kollochi sali, ghadi nsali ana tani!\n");
    return 0;
}
// #include "philo.h"

// void* my_routine(void* arg) {
//     int* x = (int*) arg; // castina l int*
//     printf("l9ima hiya: %d\n", *x);
//     return NULL;
// }

// int main() {
//     pthread_t t;
//     int value = 42;
//     pthread_create(&t, NULL, my_routine, &value);
//     pthread_join(t, NULL);
//     return 0;
// }
