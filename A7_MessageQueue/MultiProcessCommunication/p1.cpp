#include <iostream>
#include <stdio.h> 
#include <sys/ipc.h> 
#include <sys/msg.h> 
using namespace std;

struct msg_buffer_struct{
    long msg_type;
    char message[1024];
}msg_buffer;

int main(){
    key_t msgQkey;
    int msgid;
    
    msgQkey = ftok("msgQmpc",65);

    msgid= msgget(msgQkey,0666|IPC_CREAT);
    int count=1;
    while(count--){
        msg_buffer.msg_type=2;
        cout << "Write Data For P2:";
        cin >> msg_buffer.message;
        msgsnd(msgid,&msg_buffer,sizeof(msg_buffer),0);
        cout << "message sent is->" << msg_buffer.message << "\n";

        msgrcv(msgid,&msg_buffer,sizeof(msg_buffer),1,0);
        cout << "message received is->" << msg_buffer.message << "\n";
    }
    msgctl(msgid, IPC_RMID, NULL);
    
}