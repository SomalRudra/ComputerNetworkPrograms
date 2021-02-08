#include <iostream>
#include <stdio.h> 
#include <sys/ipc.h> 
#include <sys/msg.h> 
#include <sys/wait.h>
#include<stdio.h> 
#include <unistd.h> 
#include <sys/types.h>
#include <stdlib.h> 
#include <iostream>
#include <sys/wait.h>
#include <sys/ipc.h> 
#include <sys/shm.h> 
#include <fcntl.h>
#include <pthread.h> 
#include <semaphore.h> 
#include <string.h>
using namespace std;

struct msg_buffer_struct{
    long msg_type;
    char message[1024];
}msg_buffer;

int main(){
    key_t msgQkey;
    int msgid;
    
    msgQkey = ftok("msgQChatting",65);

    msgid= msgget(msgQkey,0666|IPC_CREAT);
    int count=2;
    while(count--){
        msg_buffer.msg_type=2;

        cout << "Write Data:";
        cin >> msg_buffer.message;

        msgsnd(msgid,&msg_buffer,sizeof(msg_buffer),0);

        cout << "message sent is->" << msg_buffer.message << "\n";


        msgrcv(msgid,&msg_buffer,sizeof(msg_buffer),1,0);
   
        cout << "message received is->" << msg_buffer.message << "\n";
    }
    msgctl(msgid, IPC_RMID, NULL);



}