#include<stdio.h>
#include<string.h>    //strlen
#include<stdlib.h>    //strlen
#include<sys/socket.h>
#include<arpa/inet.h> //inet_addr
#include<unistd.h>    //write
#include <sys/types.h>
#include<pthread.h>

#define MAXLINE 200

void* client_thread(void* args){

char *argv = (char*)args;

int sockfd, n;
char recvline[MAXLINE + 1];
struct sockaddr_in servaddr;

if ( (sockfd = socket(AF_INET, SOCK_STREAM, 0)) < 0){
	printf("socket error");
        return 0;
}

bzero(&servaddr, sizeof(servaddr));
servaddr.sin_family = AF_INET;
servaddr.sin_port = htons(49153); /* daytime server */

//Convert IPv4 and IPv6 addresses from text to binary form
int x;
x=inet_pton(AF_INET, argv,&servaddr.sin_addr);
if (x< 0){
	printf("inet_pton error for %s",argv);
	return 0;
}

if (connect(sockfd, (struct sockaddr *) &servaddr,sizeof(servaddr)) < 0){
	printf("connection errorr");
	return 0;
}

char *filename = (char*)calloc(100, sizeof(char));
printf("Enter filename: ");
gets(filename);
if(filename)
printf("Input is  %s\n", filename);

send(sockfd, filename, 10, 0);

char str[1000];
int valread = read(sockfd, str, 1000);
puts(str);
}


int main(int argc, char **argv)
{
    pthread_t tid;
       
    if(pthread_create(&tid, NULL, client_thread, argv[1])){
           printf("Error in creating thread");
    }
    if(pthread_join(tid, NULL)){
        printf("Error in ending thread");
    }
    exit(0);
}
