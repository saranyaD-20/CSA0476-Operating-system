#include <stdio.h>
#include <pthread.h>
#include <semaphore.h>
#include <unistd.h>

#define NUM_READERS 3
#define NUM_WRITERS 2

// Shared data
int shared_data = 0;
sem_t mutex, write_mutex;
int read_count = 0;

// Reader thread function
void* reader(void* id) {
    int reader_id = *(int*)id;
    sleep(1); // Simulating some work
    printf("Reader %d is trying to read.\n", reader_id);
    
    sem_wait(&mutex);
    read_count++;
    if (read_count == 1) {
        sem_wait(&write_mutex);
    }
    sem_post(&mutex);

    // Reading the shared data
    printf("Reader %d is reading data: %d\n", reader_id, shared_data);

    sem_wait(&mutex);
    read_count--;
    if (read_count == 0) {
        sem_post(&write_mutex);
    }
    sem_post(&mutex);

    return NULL;
}

// Writer thread function
void* writer(void* id) {
    int writer_id = *(int*)id;
    sleep(1); // Simulating some work
    printf("Writer %d is trying to write.\n", writer_id);

    sem_wait(&write_mutex);

    // Writing to the shared data
    shared_data = writer_id;
    printf("Writer %d wrote data: %d\n", writer_id, shared_data);

    sem_post(&write_mutex);

    return NULL;
}

int main() {
    pthread_t readers[NUM_READERS];
    pthread_t writers[NUM_WRITERS];

    sem_init(&mutex, 0, 1);
    sem_init(&write_mutex, 0, 1);

    int reader_ids[NUM_READERS];
    int writer_ids[NUM_WRITERS];

    for (int i = 0; i < NUM_READERS; i++) {
        reader_ids[i] = i;
        pthread_create(&readers[i], NULL, reader, &reader_ids[i]);
    }

    for (int i = 0; i < NUM_WRITERS; i++) {
        writer_ids[i] = i;
        pthread_create(&writers[i], NULL, writer, &writer_ids[i]);
    }

    for (int i = 0; i < NUM_READERS; i++) {
        pthread_join(readers[i], NULL);
    }

    for (int i = 0; i < NUM_WRITERS; i++) {
        pthread_join(writers[i], NULL);
    }

    sem_destroy(&mutex);
    sem_destroy(&write_mutex);

    return 0;
}
