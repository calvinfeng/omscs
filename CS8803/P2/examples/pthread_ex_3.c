#include <stdio.h>
#include <pthread.h>
#include <unistd.h>
#include <stdlib.h>
#define NUM_THREADS 4

// It must return a void pointer to be executed on a pthread.
void* hello(void* arg) {
    int i;
    for (i = 0; i < 10; i++) {
        sleep(1);
        printf("Hello Thread #%d: %d\n", *((int*)arg), i);
    }

    return 0;
}

int main (void) {
    int i;
    pthread_t tid[NUM_THREADS];

    for (i = 0; i < NUM_THREADS; i++) {
        // Explicitly tell the compiler to allocate a new pointer for me to store data.
        int* id = (int *) malloc(sizeof(int)); 
        *id = i; 
        pthread_create(&tid[i], NULL, hello, id);
    }   

    for (i = 0; i < NUM_THREADS; i++) {
        pthread_join(tid[i], NULL);
    }

    return 0;
}