// C Program for Message Queue (Writer Process)
#include <stdio.h>
#include <sys/ipc.h>
#include <sys/msg.h>
#include<string.h>
#define MAX 10
  
// structure for message queue
struct msg_queue {
    long msg_type;
    char msg_text[100];
} message;
  
int main() {
    key_t key;
    int msgid;
  
    // ftok to generate unique key
    key = ftok("progfile", 65);
  
    // msgget creates a message queue
    // and returns identifier
    msgid = msgget(key, 0666 | IPC_CREAT);
    message.msg_type = 1;
    
    char to_exit[] = "END";

    bzero(message.msg_text,100);
    while(1)
    {
        if(message.msg_text[0] == '\0')
        printf("Name of file: ");
        fgets(message.msg_text,MAX,stdin);
        if(message.msg_text[0] == to_exit[0] && message.msg_text[1] == to_exit[1] && message.msg_text[2] == to_exit[2])
        {
            printf("Exited\n");
            break;
        }
        FILE * fp = fopen(message.msg_text , "r");
        if(fp == NULL)
        {
            bzero(message.msg_text,100);
            continue;
        }
        char store[100];
        int j = 0;
        do
        {
            store[j++] = fgetc(fp);
        } 
        while (store[j-1] != EOF);
        store[j-1] = '\0';
        strcpy(message.msg_text,store);
        // msgsnd to send message
        msgsnd(msgid, &message, sizeof(message), 0);

        // display the message
        // printf("Content of the file send is: %s \n", message.msg_text);
    }
    return 0;
}