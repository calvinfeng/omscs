#include "priority_readers_and_writers.h"
#include <pthread.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

#define NUM_READERS 5
#define NUM_READS 5
#define NUM_WRITERS 5
#define NUM_WRITES 5

pthread_mutex_t mutex = PTHREAD_MUTEX_INITIALIZER;
pthread_cond_t read_phase = PTHREAD_COND_INITIALIZER;
pthread_cond_t write_phase = PTHREAD_COND_INITIALIZER;

int shared_value = 0;
int waiting_readers = 0;
int active_readers = 0;

// Since each string is represented by char*, the pointer to string is the starting block of memory
// for a list of string.
int main(int argc, char** argv) {
    int reader_ids[NUM_READERS];
    int writer_ids[NUM_WRITERS];

    pthread_t readers[NUM_READERS];
    pthread_t writers[NUM_WRITERS];

	// Seed the random number generator
	srandom((unsigned int)time(NULL));

    int i;
    for (i = 0; i < NUM_READERS; i++) {
        reader_ids[i] = i;
        pthread_create(&readers[i], NULL, read_routine, &reader_ids[i]);
    }

    for (i = 0; i < NUM_WRITERS; i++) {
        writer_ids[i] = i;
        pthread_create(&writers[i], NULL, write_routine, &writer_ids[i]);
    }

    // Time to join

    for (i = 0; i < NUM_READERS; i++) {
        pthread_join(readers[i], NULL);
    }

    for (i = 0; i < NUM_WRITERS; i++) {
        pthread_join(writers[i], NULL);
    }

    return 0;
}

void* read_routine(void* thr_arg) {
    int thread_id = *((int*)thr_arg);
    int reader_count_holder;

    // Each reader reads NUM_READS times.
    int i = 0;
    for (i = 0; i < NUM_READS; i++) {
	    usleep(1000 * (random() % NUM_READERS + NUM_WRITERS));

        pthread_mutex_lock(&mutex);
        waiting_readers++;
        while (active_readers == -1) {
            pthread_cond_wait(&read_phase, &mutex);
        }
        waiting_readers--;
        reader_count_holder = ++active_readers;
        pthread_mutex_unlock(&mutex);

        printf("[reader:%d] is reading %d, current reader count = %d\n", thread_id, shared_value, reader_count_holder);

        pthread_mutex_lock(&mutex);
        active_readers--;
        if (active_readers == 0) {
            // Only signal write phase when there is no reader. Only one writer is allowed to write at a time.
            pthread_cond_signal(&write_phase);
        }
        pthread_mutex_unlock(&mutex);
    }

    pthread_exit(0);
}

void* write_routine(void* thr_arg) {
    int thread_id = *((int*)thr_arg);
    int reader_count_holder;

    // Each writer writes NUM_WRITES times.
    int i = 0;
    for (i = 0; i < NUM_WRITES; i++) {
        usleep(1000 * (random() % NUM_READERS + NUM_WRITERS));
        
        pthread_mutex_lock(&mutex);
        while (active_readers != 0) {
            pthread_cond_wait(&write_phase, &mutex);
        }
        active_readers = -1;
        reader_count_holder = active_readers;
        pthread_mutex_unlock(&mutex);

        printf("[writer: %d] is writing %d, current reader count = %d\n", thread_id, ++shared_value, reader_count_holder);

        pthread_mutex_lock(&mutex);
        active_readers = 0;
        if (waiting_readers > 0) {
            pthread_cond_broadcast(&read_phase);
        } else {
            pthread_cond_signal(&write_phase);
        }
        pthread_mutex_unlock(&mutex);
    }

    pthread_exit(0);
}


