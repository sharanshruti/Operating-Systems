#include <stdio.h>
#include <sys/ipc.h>
#include <sys/msg.h>


struct msg_queue {
	long msg_type;
	char msg_text[100];
} msg;

int main(){
	key_t key;
	int id_msg;

	// ftok to generate unique key
	key = ftok("progfile", 65);

	// msgget creates a msg queue
	// and returns identifier
	id_msg = msgget(key, 0666 | IPC_CREAT);

	while(1)
	{	
		// msgrcv to receive msg
		msgrcv(id_msg, &msg, sizeof(msg), msg.msg_type , 0);
		// display the msg
		if( msg.msg_text == "END" ) break;
		else printf("Data Received is : %s \n",msg.msg_text);

	}
	// to destroy the msg queue
	msgctl(id_msg, IPC_RMID, NULL);
	return 0;
}