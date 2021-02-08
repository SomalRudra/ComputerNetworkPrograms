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
    int type;
    int count=5;
    msgQkey = ftok("file1",65);
    msgid= msgget(msgQkey,0666|IPC_CREAT);
    while(count--){
         cout << "Give msg type: ";
        cin >> type;
        ssize_t x= msgrcv(msgid,&msg_buffer,sizeof(msg_buffer),type,0);
        cout << "\n ssize_t" << x;
        cout << "message received is->" << msg_buffer.message << "\n";

    }
    msgctl(msgid, IPC_RMID, NULL);
}