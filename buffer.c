#include <stdio.h>
#include <pthread.h>
#include <semaphore.h>
#define SIZE 3
int buffer[SIZE];
int in = 0, out = 0;
sem_t empty;
sem_t full;
pthread_mutex_t mutex;

void produce() {
    int item, value;
    sem_getvalue(&empty, &value);
    if (value == 0) {
        printf("\nBuffer is FULL! Cannot produce.\n");
        return;
    }
    printf("\nEnter item to produce: ");
    scanf("%d", &item);
    sem_wait(&empty);
    pthread_mutex_lock(&mutex);
    buffer[in] = item;
    printf("Producer produced item %d\n", item);
    in = (in + 1) % SIZE;
    pthread_mutex_unlock(&mutex);
    sem_post(&full);
}

void consume() {
    int item, value;
    sem_getvalue(&full, &value);
    if (value == 0) {
        printf("\nBuffer is EMPTY! Cannot consume.\n");
        return;
    }
    sem_wait(&full);
    pthread_mutex_lock(&mutex);
    item = buffer[out];
    printf("Consumer consumed item %d\n", item);
    out = (out + 1) % SIZE;
    pthread_mutex_unlock(&mutex);
    sem_post(&empty);
}

int main() {
    int choice;
    sem_init(&empty, 0, SIZE);
    sem_init(&full, 0, 0);
    pthread_mutex_init(&mutex, NULL);
    printf("\n--- PRODUCER CONSUMER PROBLEM USING SEMAPHORES ---\n");
    printf("Buffer size = %d\n", SIZE);
    while (1) {
        printf("\n1. Produce\n2. Consume\n3. Exit\nEnter your choice: ");
        scanf("%d", &choice);
        switch (choice) {
            case 1:
                produce();
                break;
            case 2:
                consume();
                break;
            case 3:
                printf("\nExiting...\n");
                sem_destroy(&empty);
                sem_destroy(&full);
                pthread_mutex_destroy(&mutex);
                return 0;
            default:
                printf("\nInvalid choice! Please enter 1, 2, or 3.\n");
        }
    }
    return 0;
}
