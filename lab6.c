#include <stdio.h>
#include <pthread.h>
#include <stdlib.h>
#include <unistd.h>
#define Max 10

struct threadId{
	int flag;
	long unsigned int tid;
} thread[Max];

int init_ds(){
	for(int i=0;i<Max;i++){
		thread[i].flag = 0;
		thread[i].tid = i+1;
	}
	
	return 1;
}

int allocate_tid(){
	for(int i=0;i<Max;i++){
		if(thread[i].flag==0){
			thread[i].flag=1;
			return thread[i].tid;
			}
		}
	return -1;
}

void release_tid(int tid){
	for(int i=0;i<Max;i++){
		if(thread[i].tid==tid)thread[i].flag=0;
		}
}
void* Runner_Func(){
	long unsigned int tid = allocate_tid();
	if(tid!=-1){
	printf("Running Tid:%lu\n",tid);
	int s = 2 + rand()%(9);
	sleep(s);
	release_tid(tid);
	printf("Release Tid:%lu\n",tid);
	}
	
}

int main(){
	int create_ds = init_ds();
	if(create_ds==-1){
		printf("Initialization error\n");
		return 1;
	}
	int count = Max;
	pthread_t tid[count];
	for(int i=0;i<count+2;i++){
		pthread_create(&tid[i],NULL,Runner_Func,NULL);
	}
	for(int i=0;i<count;i++){
		pthread_join(tid[i],NULL);
	}
	for(int j=0;j<Max;j++){
		printf("Tid:%ld\tFlag:%d\n",thread[j].tid,thread[j].flag);
	}
	
	return 0;
}
