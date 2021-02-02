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
#include <iostream>
using namespace std;

#define SIGHUP  1   /* Hangup the process */ 
#define SIGINT  2   /* Interrupt the process */ 
#define SIGQUIT 3   /* Quit the process */ 
#define SIGILL  4   /* Illegal instruction. */ 
#define SIGTRAP 5   /* Trace trap. */ 
#define SIGABRT 6   /* Abort. */
#define NotReady -1
#define Ready 1
#define FILLED 0

struct memory { 
    char buff[100]; 
    int status, pid1, pid2; 
}; 
  
struct memory* shmptr; 

void handler(int sig){
	if(sig == SIGUSR2){   // user 1 receiving 
		printf("Receiving User 1 : \n");
		puts(shmptr->buff);
	}	
}

int main(){

	int pid = getpid();
	key_t key = ftok("abc",65); 
  
    int shmid = shmget(key,sizeof(struct memory),0666|IPC_CREAT);

    shmptr = (struct memory *) shmat(shmid , NULL , 0);

    shmptr->pid2 = pid;
    shmptr->status = NotReady;

    signal(SIGUSR2 , handler);
    while(1){
    	sleep(1);

    	printf("User 2: \n");
    	fgets(shmptr->buff , 100 ,stdin);
    	shmptr->status = Ready;

    	kill(shmptr->pid1 , SIGUSR1);
    	while(shmptr->status == Ready){
    		continue;
    	}
    }
    shmdt((void*)shmptr); 
    shmctl(shmid, IPC_RMID, NULL);
    return 0;

}