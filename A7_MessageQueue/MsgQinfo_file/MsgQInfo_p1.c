#include <stdio.h> 
#include <unistd.h> //for fork system call
#include <sys/types.h>
#include <stdlib.h> //for exit system call
#include <sys/wait.h>
#include <sys/ipc.h> 
#include <sys/shm.h> 
#include <fcntl.h>
#include <pthread.h> 
#include <semaphore.h> 
#include <string.h>
#include <sys/poll.h>
#include <sys/time.h>
#include <assert.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <poll.h>
#include <unistd.h>
#include <signal.h>
#include <errno.h>
#include <sys/msg.h>

struct msg_buff
{
    long msg_type;
    char msg_text[1024];
};

struct msg_buff message;
struct msqid_ds msgq_ll;
static const struct msqid_ds empty;
int get_queue_info(int msgid)
{
    if(msgctl(msgid,IPC_STAT,&msgq_ll)==-1)
    {   
        printf("Error in IPC_STAT\n");
        return errno;
    }
    printf("Number of messages currently in the queue: %lu\n",msgq_ll.msg_qnum);
    printf("Max number of bytes allowed in queue: %lu\n",msgq_ll.msg_qbytes);
    printf("Current number of bytes in queue: %lu\n",msgq_ll.__msg_cbytes);
    printf("PID of the last process that called msgsnd() for the queue: %d\n",msgq_ll.msg_lspid);
    printf("PID of the last process that called msgrcv() for the queue: %d\n",msgq_ll.msg_lrpid);
    printf("Owner's UID: %d\n",msgq_ll.msg_perm.uid);
    printf("Owner's GID: %d\n",msgq_ll.msg_perm.gid);
    printf("Creator's UID: %d\n",msgq_ll.msg_perm.cuid);
    printf("Creator's GID: %d\n",msgq_ll.msg_perm.cgid);
    printf("Access Modes: %d\n",msgq_ll.msg_perm.mode);
    
    return 1;
}

int main()
{
    key_t key=ftok("file1",65);

    int msgid=msgget(key,0666|IPC_CREAT);
    int x=1;
    int count=2;
    while(count--)
    {        
        message.msg_type=x++;

        printf("Type Message: ");

        fgets(message.msg_text,1024,stdin);

        msgsnd(msgid,&message,sizeof(message),0);
        printf("DATA AFTER Sending:\n");
        
        get_queue_info(msgid);

        printf("Msg stored in type %d:\n",x-1);
        msgq_ll=empty;

        int type; 
        scanf("%d",&type);
        msgrcv(msgid,&message,sizeof(message),type,0);
        printf("P2: %s",message.msg_text);
        printf("DATA AFTER RECEIVE:\n");
        get_queue_info(msgid);
        msgq_ll=empty;
    }
    msgctl(msgid,IPC_RMID,NULL);
    return 0;
}

// #include <iostream>
// #include <stdio.h> 
// #include <sys/ipc.h> 
// #include <sys/msg.h> 
// using namespace std;

// struct msg_buffer_struct{
//     long msg_type;
//     char message[1024];
// }msg_buffer;

// int main(){
//      key_t msgQkey;
//     int msgid;
    
//     msgQkey = ftok("msgQ1",65);

//     msgid= msgget(msgQkey,0666|IPC_CREAT);
//     msg_buffer.msg_type=1;

//     cout << "Write Data:";
//     cin >> msg_buffer.message;

//     msgsnd(msgid,&msg_buffer,sizeof(msg_buffer),0);

//     cout << "message sent is->" << msg_buffer.message << "\n";
// }