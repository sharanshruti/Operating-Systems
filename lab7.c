#include<stdio.h>
#include<pthread.h>
#include<semaphore.h>
#include<unistd.h>
#include<time.h>
#include<stdlib.h>

#define MAX 5

int buffer[MAX] = {-1};
int full = 0, empty = MAX, mutex = 1;
int start = 0,end = 0;

void wait(int * s){
	while(*s <= 0);
	
	*s  = *s -1;
}

void signal(int * s){
	*s = *s+1;
}

void remove_item(int cid){
	int item = buffer[end];
	buffer[end] = -1;
	end = (end + 1)%MAX;
	
	printf(" << | Item consumed by consumer %d: %d\n", cid,item);
}

void insert_item(int item){
	buffer[start] =  item;
	start = (start+1)%MAX;
	
	printf(" >> | Item produced and inserted to buffer: %d\n", item);
}

void * consumer(void * args){
	int ti = (rand()%10)+2;
	int cid = *(int *)args;
	sleep(ti);
	
	//int item = (rand()%100)+1;
	
	wait(&full);
	wait(&mutex);
	
	remove_item(cid);
	
	signal(&mutex);
	signal(&empty);
	
	return 0;
}

void * producer(void * args){
	int l = 1001;
	//int numberOfConsumers = *(int *)args;
	
	while(l<=1010){
		wait(&empty);
		wait(&mutex);
		
		insert_item(l);
		
		signal(&mutex);
		signal(&full);
		int ti = (rand()%2)+2;
		sleep(ti);
		l++;
	}
	
	return 0;
}

int main(int argc, char * argv[]){
	int numberOfConsumers = atoi(argv[1]);
	pthread_t consumerThread[numberOfConsumers];
	pthread_t producerThread;
	
	/*sem_init(&empty, 0, MAX);
	sem_init(&full, 0, 0);
	sem_init(&mutex, 0, 1);
	*/
	int * arg = malloc(sizeof(* arg));
	* arg = numberOfConsumers;
	int r = pthread_create(&producerThread, NULL,producer, (void *)arg);
	
	if(r!=0){
		printf("Failed to create producer thread!!");
		exit(1);
	}
	
	for(int i=0;i<numberOfConsumers;i++){
		int * id = malloc(sizeof(* id));
		*id = i+1;
		int r = pthread_create(&consumerThread[i], NULL, consumer, (void *)id);
		
		if(r!=0){
			printf("Failed to create producer thread!!");
			exit(1);
		}
	}
	
	for(int i=0;i<numberOfConsumers;i++){
		pthread_join(consumerThread[i],NULL);
	}
	
	pthread_join(producerThread, NULL);
	
	printf("---------------------------------------------------------\n");
	for(int i=0;i<MAX;i++){
		printf("Item in buffer at index %d: %d \n",i, buffer[i]);
	}
	printf("---------------------------------------------------------\n");
	return 0;
		
}