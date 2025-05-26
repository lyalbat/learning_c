#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <pthread.h>
#include <unistd.h>
#include <time.h>
// #include <semaphore.h>

int buffer[10];
int count = 0;
pthread_mutex_t lock;

void *write_to_buffer(void *arg)
{
    while (1)
    {
        // Produce data
        int x = rand() % 100;
        pthread_mutex_lock(&lock);
        if (count < 10)
        {
            // Add to buffer
            buffer[count] = x;
            count++;
        }
        pthread_mutex_unlock(&lock);
    }
}
void *read_buffer(void *arg)
{
    while (1)
    {
        int y = -1;
        pthread_mutex_lock(&lock);
        if (count > 0)
        {
            // Remove from the buffer as a stack
            y = buffer[count - 1];
            count--;
        }
        pthread_mutex_unlock(&lock);

        // Consume
        printf("Got %d\n", y);
    }
}

int main()
{
    srand(time(NULL));
    pthread_mutex_init(&lock, NULL);
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
    return 0;
}