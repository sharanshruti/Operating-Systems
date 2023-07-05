#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <pthread.h>
#include <semaphore.h>

#define Size 5
#define MaxElements 5

sem_t empty, full;
pthread_mutex_t my_mutex;
int element_in = 0, element_out = 0, buffer_array[Size];

void insert_item(int *item)
{
    for (int i = 0; i < MaxElements; i++)
    {
        int y = item[i];
        sem_wait(&empty);
        pthread_mutex_lock(&my_mutex);

        buffer_array[element_in] = y;

        printf("Taks done: Producer inserts item %d at %d\n", buffer_array[element_in], element_in);
        element_in = (element_in + 1) % Size;
        pthread_mutex_unlock(&my_mutex);

        srand(time(0));
        sleep(rand() % 8 + 2);
        sem_post(&full);
    }
}

void remove_item()
{
    srand(time(0));
    sleep(rand() % 8 + 2);

    for (int i = 0; i < MaxElements; i++)
    {
        sem_wait(&full);
        pthread_mutex_lock(&my_mutex);

        int x = buffer_array[element_out];
        printf("Task done: Consumer removes item %d from %d\n", x, element_out);

        buffer_array[element_out] = 0;
        element_out = (element_out + 1) % Size;

        pthread_mutex_unlock(&my_mutex);
        sem_post(&empty);
    }
}

void *producer(void *producer_no)
{
    int *item_no = ((int *)producer_no);
    insert_item(item_no);

    sleep(5);

    printf("\nBuffer: ");
    for (int j = 0; j < Size; j++)
        printf("%d  ", buffer_array[j]);
    printf("\n");

    exit(0);
}

void *consumer(void *consumer_no)
{
    remove_item();
}

int main(int argc, char **argv)
{
    pthread_t pro, con[atoi(argv[1])];
    pthread_mutex_init(&my_mutex, NULL);

    sem_init(&empty, 0, Size);
    sem_init(&full, 0, 0);

    int a[10];
    a[0] = 1001;
    for (int i = 1; i < 10; i++)
        a[i] = a[i - 1] + 1;

    pthread_create(&pro, NULL, (void *)producer, (void *)&a);

    for (int i = 0; i < atoi(argv[1]); i++)
        pthread_create(&con[i], NULL, (void *)consumer, NULL);

    for (int i = 0; i < atoi(argv[1]); i++)
        pthread_join(con[i], NULL);

    pthread_join(pro, NULL);

    // Destroy mutex and semaphores
    pthread_mutex_destroy(&my_mutex);
    sem_destroy(&empty);
    sem_destroy(&full);

    return 0;
}