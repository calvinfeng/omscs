#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#define BUF_SIZE 3

int buffer[BUF_SIZE];
int add = 0;
int del = 0; 
int num = 0;

pthread_mutex_t m = PTHREAD_MUTEX_INITIALIZER;
pthread_cond_t consumer_cond = PTHREAD_COND_INITIALIZER;
pthread_cond_t producer_cond = PTHREAD_COND_INITIALIZER; 

void* producer(void* param) {
    int i;
    for (i = 1; i <= 20; i++) {
        pthread_mutex_lock(&m);
        if (num > BUF_SIZE) {
            exit(1);
        }

        // Block if buffer size is full
        while (num == BUF_SIZE) {
            pthread_cond_wait(&producer_cond, &m);
        }

        // This is a ring buffer
        buffer[add] = i;
        add = (add + 1) % BUF_SIZE;
        num++;
        pthread_mutex_unlock(&m);

        pthread_cond_signal(&consumer_cond);
        printf("producer has inserted %d\n", i);
    }

    printf("producer has exited\n");
    return 0;
}

void* consumer(void* param) {
    int data;
    
    int i;
    for (i = 1; i <= 20; i++) {
        pthread_mutex_lock(&m);
        if (num < 0) {
            exit(1);
        }
        
        // Block if buffer is empty.
        while (num == 0) {
            pthread_cond_wait(&consumer_cond, &m);
        }

        data = buffer[del];
        del = (del + 1) % BUF_SIZE;
        num--;
        pthread_mutex_unlock(&m);

        pthread_cond_signal(&producer_cond);
        printf("consumer has retrieved %d\n", data);
    }

    printf("consumer has exited\n");
    return 0;
}

int main(int argc, char* argv[]) {
    pthread_t tid_1, tid_2;

    int i;
    if (pthread_create(&tid_1, NULL, producer, NULL) != 0) {
        fprintf(stderr, "unable to create producer thread\n");
        exit(1);
    }

    if (pthread_create(&tid_2, NULL, consumer, NULL) != 0) {
        fprintf(stderr, "unable to create consumer thread\n");
        exit(1);
    }

    pthread_join(tid_1, NULL);
    pthread_join(tid_2, NULL);
    printf("done\n");
}