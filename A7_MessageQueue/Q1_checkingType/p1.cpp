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
    
    msgQkey = ftok("msgQ1",65);

    msgid= msgget(msgQkey,0666|IPC_CREAT);
    for(int i=0; i<3; i++){
        cout << "\nEnter Message Type: ";
        int x; cin>> x;
         msg_buffer.msg_type=x;
         cout << "\nWrite " << i << "th message: ";
         cin >> msg_buffer.message;
         msgsnd(msgid,&msg_buffer,sizeof(msg_buffer),0);
         cout << "\nmessage sent is->" << msg_buffer.message << "\n";
    }
}