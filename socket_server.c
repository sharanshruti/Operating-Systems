#include<stdio.h>
#include<string.h>    //strlen
#include<stdlib.h>    //strlen
#include<sys/socket.h>
#include<arpa/inet.h> //inet_addr
#include<unistd.h>    //write
#include<pthread.h>
#include<semaphore.h> //for threading , link with lpthread


void *helper(void* args){
    char str[100];
    int new_socket = *((int *)args);
    int valread = read(new_socket, str, 100);
    
    char buff[1000];

    FILE* fp = fopen(str, "r");
    if(fp == NULL){
        printf("Error");
    }

    int j = 0;
    do{
        buff[j++] = fgetc(fp);
    } while (buff[j - 1] != EOF);

    buff[j - 1] = '\0';

    send(new_socket, buff, 1000, 0);
    
}

int main(int argc , char *argv[])
{
	int socket_desc, new_socket;
	struct sockaddr_in server;
	char *message;
	//Create socket
	//Stream sockets allow processes to communicate using TCP. A stream socket provides bidirectional, reliable, sequenced, and unduplicated flow of data with no record boundaries. After the connection has been established, data can be read from and written to these sockets as a byte stream. The socket type is SOCK_STREAM.
	
	// int socket(int domain,int type,int protocol);
	socket_desc = socket(AF_INET , SOCK_STREAM , 0);
	bzero(&server, sizeof(server));
	if (socket_desc == -1)
	{
		printf("Could not create socket");
	}
	//Prepare the sockaddr_in structure
	server.sin_family = AF_INET;

	//INADDR_ANY: special IP address when we don't know the IP address of the server machine
	server.sin_addr.s_addr = htonl(INADDR_ANY); //host to network byte order
	//network byte order, as used on the Internet, is Most Significant Byte first.

	server.sin_port = htons(49153);
	//Bind
	if( bind(socket_desc,(struct sockaddr *)&server , sizeof(server)) < 0)
	{
		puts("Bind failed");
		return 1;
	}
	puts("Bind done");
	//Listen
	listen(socket_desc, 50);

    pthread_t tid[60];

    int i = 0;

    while(i<60)
    {
        
	    puts("Waiting for incoming connections...");
	    new_socket = accept(socket_desc, NULL,NULL); 
	    printf("Accept returns %d\n",new_socket);
	    puts("Connection accepted");

		// Reply to the client
		// message = "Hello Client , here is a message for you. \n";
		// write(new_socket , message , strlen(message));
		// if (new_socket<0)
		// {
		// 	perror("accept failed");
		// 	return 1;
		// }
        if(pthread_create(&tid[i], NULL, helper, &new_socket)){
            printf("Error in creating thread");
        }
		i+=1;
    }

	int j = 0;
	while(j<=50){
		if(pthread_join(&tid[j], NULL)){
			printf("Error in ending thread");
		}
		j+=1;
	}

	return 0;
}
