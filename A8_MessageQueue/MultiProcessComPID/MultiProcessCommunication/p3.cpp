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
    msg_buffer.msg_type = 3;
    string s = to_string(pid);
    char const *pid_char = s.c_str(); 
    strcpy(msg_buffer.message,pid_char);
    
    if(msgsnd(msgid,&msg_buffer,sizeof(msg_buffer),0)==-1){
        return false;
    }
    msg_buffer.msg_type = 4;
    msgsnd(msgid,&msg_buffer,sizeof(msg_buffer),0);
    cout << "\nmessage sent is->" << msg_buffer.message << " with type: " << msg_buffer.msg_type;
    return true;
    //cout << "message sent is->" << msg_buffer.message << "\n";
}


string getMsgFromP2(key_t msgQkey,int msgid,int pid){
    msgrcv(msgid,&msg_buffer,sizeof(msg_buffer),pid,0);
   cout << "\nmsg received is->"  << msg_buffer.message;
   return msg_buffer.message;
}

int main(){
    key_t msgQkey;
    int msgid;
    
    msgQkey = ftok("msgQmpcPID",65);

    msgid= msgget(msgQkey,0666|IPC_CREAT);
    
    //store pid
    bool isStored = storePID(msgQkey,msgid,getpid()); 
    string rcvdMsg = getMsgFromP2(msgQkey,msgid,getpid());
    cout << "\n Received msg from p2->" << rcvdMsg;
  
    
    //get pid of p1
    msgrcv(msgid,&msg_buffer,sizeof(msg_buffer),1,0);
    string pid1_str = msg_buffer.message;
    cout << "\npid of 1st->" << pid1_str;

    //convert string pid1 to int 
    stringstream geek(pid1_str); 
    int pid1 = 0; 
    geek >> pid1; 

    //send message for p1
    msg_buffer.msg_type = pid1;
    string messageStr = rcvdMsg;
    char const *universalMsg_char = messageStr.c_str(); 
    strcpy(msg_buffer.message,universalMsg_char);
    msgsnd(msgid,&msg_buffer,sizeof(msg_buffer),0);  
    
}