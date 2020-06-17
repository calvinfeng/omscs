#include <stdio.h>
#include <pthread.h>
#define NUM_THREADS 4

void* thread_func(void* p_arg) {
    int* p = (int*)p_arg;
    int my_num = *p;
    printf("Thread number %d\n", my_num);
    return 0;
}

int main(void) {
    int thread_nums[NUM_THREADS]; // This is a local storage of Thread ID essentially
    pthread_t threads[NUM_THREADS];
    
    int i;
    for (i = 0; i < NUM_THREADS; i++) {
        thread_nums[i] = i;
        pthread_create(&threads[i], NULL, thread_func, &thread_nums[i]);
    }

    for (i = 0; i < NUM_THREADS; i++) {
        pthread_join(threads[i], NULL);
    }

    return 0;
}