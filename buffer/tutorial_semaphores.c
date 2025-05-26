#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <pthread.h>
#include <unistd.h>
#include <time.h>
#include <semaphore.h>

int buffer[10];
int count = 0;

sem_t semaph_empty;
sem_t semaph_full;
pthread_mutex_t lock;

void *write_to_buffer(void *arg)
{
    while (1)
    {
        // Produce data
        int x = rand() % 100;

        // Add to buffer
        sem_wait(&semaph_empty);//waits until it can decrement the semaphore value (until it is >0)
        pthread_mutex_lock(&lock);

        buffer[count] = x;
        count++;

        pthread_mutex_unlock(&lock);
        sem_post(&semaph_full); //increments semaphore of full slots
    }
}
void *read_buffer(void *arg)
{
    while (1)
    {
        
        sem_wait(&semaph_full); //waits until at least 1 full
        pthread_mutex_lock(&lock);
        // Remove from the buffer as a stack
        int y = buffer[count - 1];
        count--;
        pthread_mutex_unlock(&lock);
        sem_post(&semaph_empty);
        
        // Consume
        //sleep(1);
        printf("Got %d\n", y);
    }
}

int main()
{
    srand(time(NULL));
    pthread_mutex_init(&lock, NULL);
    sem_init(&semaph_empty,0,10);
    sem_init(&semaph_full,0,0);

    pthread_t writer_th;
    pthread_t reader_th;
    if (pthread_create(&writer_th, NULL, &write_to_buffer, NULL) != 0)
    {
        return 1;
    }
    if (pthread_create(&reader_th, NULL, &read_buffer, NULL) != 0)
    {
        return 1;
    }

    if (pthread_join(writer_th, NULL) != 0)
    {
        return 2;
    }
    if (pthread_join(reader_th, NULL) != 0)
    {
        return 2;
    }
    pthread_mutex_destroy(&lock);
    sem_destroy(&semaph_empty);
    sem_destroy(&semaph_full);
    return 0;
}