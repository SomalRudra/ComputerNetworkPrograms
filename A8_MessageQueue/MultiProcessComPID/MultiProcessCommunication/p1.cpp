#include <iostream>
#include <stdio.h> 
#include <sys/ipc.h> 
#include <sys/msg.h> 
#include <cstring>
#include <sys/types.h>
#include <unistd.h> 
#include<fcntl.h> 
#include<stdlib.h> 
#include <semaphore.h>
#include <sstream> 
using namespace std;

char* s11 = "s11";
char* s22 = "s22";
char* s33 = "s33";
char* s12 = "s12";
char* s23 = "s23";
char* s31 = "s41";

struct msg_buffer_struct{
    long msg_type;
    char message[1024];
}msg_buffer;

bool storePID(key_t msgQkey,int msgid,int pid){
    msg_buffer.msg_type = 1;
    string s = to_string(pid);
    char const *pid_char = s.c_str(); 
    strcpy(msg_buffer.message,pid_char);
    if(msgsnd(msgid,&msg_buffer,sizeof(msg_buffer),0)==-1){
        return false;
    }
    return true;
}

void showPID(key_t msgQkey,int msgid){
    msgrcv(msgid,&msg_buffer,sizeof(msg_buffer),1,0);
    cout << "pid received is->"  << msg_buffer.message;
}

int main(){
    key_t msgQkey;
    int msgid;

	// sem_t *mutex1 = sem_open(s12,O_CREAT,0666,0);
    // sem_t *mutex2 = sem_open(s31,O_CREAT,0666,0);
    
    msgQkey = ftok("msgQmpcPID",65);

    msgid= msgget(msgQkey,0666|IPC_CREAT);
    
    //store p1 pid
    bool isStored = storePID(msgQkey,msgid,getpid());       
    
        
    //get pid of p2
    msgrcv(msgid,&msg_buffer,sizeof(msg_buffer),2,0);
    string pid2_str = msg_buffer.message;
    cout << "\npid of 2nd->" << pid2_str;


    //convert string pid2 to int 
    stringstream geek1(pid2_str); 
    int pid2 = 0; 
    geek1 >> pid2; 
    cout << "\nint pid of 2nd->" << pid2_str;
    //send message for p2
    msg_buffer.msg_type = pid2;
    string messageStr = "universal Message";
    char const *universalMsg_char = messageStr.c_str(); 
    strcpy(msg_buffer.message,universalMsg_char);
    msgsnd(msgid,&msg_buffer,sizeof(msg_buffer),0);  

    //receive msg from p3
    //step1-> get pid of p3
    msgrcv(msgid,&msg_buffer,sizeof(msg_buffer),4,0);
    string pid3_str = msg_buffer.message;
    cout << "\npid of 3rd->" << pid3_str;

    //step2->convert that to int
    stringstream geek2(pid3_str); 
    int pid3 = 0; 
    geek2 >> pid3; 

    //step3-> read msg from q3
    msgrcv(msgid,&msg_buffer,sizeof(msg_buffer),pid3,0);
    cout << "\nmessage received from p3->" << msg_buffer.message;
    msgctl(msgid, IPC_RMID, NULL); 

}