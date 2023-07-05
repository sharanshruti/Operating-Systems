#include <pthread.h>
#include <semaphore.h>
#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>

#define MaxItems 5 
#define BufferSize 5 

sem_t empty;
sem_t full;
int in = 0;
int out = 0;
int buffer[BufferSize];
pthread_mutex_t mutex;

void insert_item(int *item)
{
     for(int i = 0; i < MaxItems; i++) {
        int y = item[i];
        sem_wait(&empty);
        pthread_mutex_lock(&mutex);
        buffer[in] = y;
        printf("Producer : Insert Item %d at %d\n", buffer[in],in);
        in = (in+1)%BufferSize;
        pthread_mutex_unlock(&mutex);

        srand(time(0));
        int sleep_time = rand() % 9 + 2;
        sleep(sleep_time);
        sem_post(&full);
    }
}

void remove_item()
{
    srand(time(0));
    int sleep_time = rand() % 9 + 2;
    sleep(sleep_time);
    for(int i = 0; i < MaxItems; i++) {
        sem_wait(&full);
        pthread_mutex_lock(&mutex);
        int x = buffer[out];
        printf("Consumer : Remove Item %d from %d\n",x, out);
        buffer[out] = 0;
        out = (out+1)%BufferSize;
        pthread_mutex_unlock(&mutex);
        sem_post(&empty);
    }
}

void *producer(void *pno)
{   
    int *item = ((int *)pno);
    insert_item(item);

    sleep(5);
    printf("Buffer : ");
    for(int j = 0; j < BufferSize; j++)
        printf("%d\t", buffer[j]);   
    printf("\n");
    exit(0);
}

void *consumer(void *cno)
{   
    remove_item();
}

int main(int argc, char **argv)
{   
    pthread_t pro,con[atoi(argv[1])];
    pthread_mutex_init(&mutex, NULL);

    sem_init(&empty,0,BufferSize);
    sem_init(&full,0,0);

    int a[10] = {1001,1002,1003,1004,1005,1006,1007,1008,1009,1010}; 

    pthread_create(&pro, NULL, (void *)producer, (void *)&a);

    for(int i = 0; i < atoi(argv[1]); i++) {
        pthread_create(&con[i], NULL, (void *)consumer, NULL);
    }


    for(int i = 0; i < atoi(argv[1]); i++) {
        pthread_join(con[i], NULL);
    }

    pthread_join(pro, NULL);

    pthread_mutex_destroy(&mutex);
    sem_destroy(&empty);
    sem_destroy(&full);

    return 0;
}