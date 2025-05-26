#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <pthread.h>
#include <unistd.h>
// #include <time.h>
#include <math.h>
// #include <semaphore.h>

#define BUFFER_SIZE 6

pthread_mutex_t lock;
char buffer[BUFFER_SIZE];
int counter = 0;

void *write_to_buffer(void *arg)
{
    char *message = (char *)arg;
    int msg_size = strlen(message);
    int done = 0;
    int pos = 0;
    while (!done)
    {
        pthread_mutex_lock(&lock);
        if (counter == 0)
        {
            for (int i = 0; i < BUFFER_SIZE; i++)
            {
                buffer[i] = message[i + pos];
                if (message[i + pos] == '\n')
                {
                    done = 1;
                    break;
                }
                else
                {
                    ++counter;
                }
            }
            pos += BUFFER_SIZE;
        }
        pthread_mutex_unlock(&lock);
    }
    // free(arg);
}

void *read_buffer(void *arg)
{
    int done = 0;
    while (!done)
    {
        pthread_mutex_lock(&lock);
        if (counter > 0)
        {
            for (int i = 0; i < BUFFER_SIZE; i++)
            {
                --counter;
                printf("%c", buffer[i]);
                if (buffer[i] == '\n')
                {
                    done = 1;
                    break;
                }
            }
        }
        pthread_mutex_unlock(&lock);
    }
}

int main()
{
    pthread_mutex_init(&lock, NULL);
    pthread_t writer_th;
    pthread_t reader_th;
    char *message = "Hello Embraer (PES)!\n";
    // int size = strlen(message);
    pthread_create(&writer_th, NULL, &write_to_buffer, (void *)message);
    pthread_create(&reader_th, NULL, &read_buffer, NULL);

    pthread_join(writer_th, NULL);
    pthread_join(reader_th, NULL);
    pthread_mutex_destroy(&lock);
    return 0;
}