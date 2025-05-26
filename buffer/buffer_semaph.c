#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <pthread.h>
#include <unistd.h>
#include <math.h>
#include <semaphore.h>

#define BUFFER_SIZE 6

pthread_mutex_t lock;
char buffer[BUFFER_SIZE];

sem_t semaph_empty;
sem_t semaph_full;

void *write_to_buffer(void *arg)
{
    char *message = (char *)arg;
    int msg_size = strlen(message);
    int done = 0;
    int pos = 0;
    while (!done)
    {
        sem_wait(&semaph_empty);
        pthread_mutex_lock(&lock);
        for (int i = 0; i < BUFFER_SIZE; i++)
        {
            buffer[i] = message[i + pos];
            if (message[i + pos] == '\n')
            {
                done = 1;
                break;
            }
        }
        pos += BUFFER_SIZE;
        sem_post(&semaph_full);
        pthread_mutex_unlock(&lock);
    }
}

void *read_buffer(void *arg)
{
    int done = 0;
    while (!done)
    {
        sem_wait(&semaph_full);
        pthread_mutex_lock(&lock);
        for (int i = 0; i < BUFFER_SIZE; i++)
        {
            printf("%c", buffer[i]);
            if (buffer[i] == '\n')
            {
                done = 1;
                break;
            }
        }
        sem_post(&semaph_empty);
        pthread_mutex_unlock(&lock);
    }
}

int main()
{
    pthread_mutex_init(&lock, NULL);
    pthread_t writer_th;
    pthread_t reader_th;
    sem_init(&semaph_empty,0,1);
    sem_init(&semaph_full,0,0);

    char *message = "Hello Embraer (PES)!\n";
    pthread_create(&writer_th, NULL, &write_to_buffer, (void *)message);
    pthread_create(&reader_th, NULL, &read_buffer, NULL);

    pthread_join(writer_th, NULL);
    pthread_join(reader_th, NULL);
    pthread_mutex_destroy(&lock);

    sem_destroy(&semaph_empty);
    sem_destroy(&semaph_full);
    return 0;
}