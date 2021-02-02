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

void handler(int x){
    //printf("this is parent handler\n");
    write(1,"This is parent handler\n",sizeof "This is parent handler\n"-1);
}

int main()
{
    signal(SIGUSR1,handler);
    setpgid(0,0);
    int gid=getpgid(0);
    int c=getpid();
	int c1=fork();
    if(c1>0){
        //wait(NULL);
        int c2=fork();
        if(c2>0){
            //wait(NULL);
            
            int c3=fork();
            if(c3>0){
                //while(1)
                sleep(5);
                killpg(gid,SIGUSR1);
                //wait(NULL);
                
            }
            else{
                setpgid(c3,c);
                execv("./p4",NULL);
            }
        }
        else{
            setpgid(c2,c);
            execv("./p3",NULL);
        }
    }
    else{
        setpgid(c1,c);
        execv("./p2",NULL);
    }
}