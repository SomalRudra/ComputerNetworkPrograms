#include <iostream>
#include <stdio.h> 
#include <sys/ipc.h> 
#include <sys/msg.h> 
#include <cstring>
#include <sys/types.h>
#include <unistd.h>
#include <sstream> 
using namespace std;

struct msg_buffer_struct{
    long msg_type;
    char message[1024];
}msg_buffer;

bool storePID(key_t msgQkey,int msgid,int pid){
    msg_buffer.msg_type = 2;
    string s = to_string(pid);
    char const *pid_char = s.c_str(); 
    strcpy(msg_buffer.message,pid_char);
    if(msgsnd(msgid,&msg_buffer,sizeof(msg_buffer),0)==-1){
        return false;
    }
    return true;
    //cout << "message sent is->" << msg_buffer.message << "\n";
}

// void showPID(key_t msgQkey,int msgid,int pid){
//     msgrcv(msgid,&msg_buffer,sizeof(msg_buffer),pid,0);
//     cout << "msg received is->"  << msg_buffer.message;
// }

string getMsgFromP1(key_t msgQkey,int msgid,int pid){
    msgrcv(msgid,&msg_buffer,sizeof(msg_buffer),pid,0);
   cout << "\nmsg received is->"  << msg_buffer.message;
   return msg_buffer.message;
}

int main(){
    key_t msgQkey;
    int msgid;
    
    msgQkey = ftok("msgQmpcPID",65);

    msgid= msgget(msgQkey,0666|IPC_CREAT);
    

    //store pid of p2
    bool isStored = storePID(msgQkey,msgid,getpid());  

    //receive msg from p1
    string rcvdMsg = getMsgFromP1(msgQkey,msgid,getpid());
    cout << "\nReceived Message From P1->" << rcvdMsg;

    //get pid of p3
    msgrcv(msgid,&msg_buffer,sizeof(msg_buffer),3,0);
    string pid3_str = msg_buffer.message;
    cout << "\npid of 3rd->" << pid3_str;

    //convert string pid3 to int 
    stringstream geek(pid3_str); 
    int pid3 = 0; 
    geek >> pid3; 

    //send message for p3
    msg_buffer.msg_type = pid3;
    string messageStr = rcvdMsg;
    char const *universalMsg_char = messageStr.c_str(); 
    strcpy(msg_buffer.message,universalMsg_char);
    msgsnd(msgid,&msg_buffer,sizeof(msg_buffer),0);  

    
}