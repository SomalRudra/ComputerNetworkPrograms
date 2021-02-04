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

#define FILLED 0 
#define Ready 1 
#define NotReady -1 

#define SIGHUP  1   /* Hangup the process */ 
#define SIGINT  2   /* Interrupt the process */ 
#define SIGQUIT 3   /* Quit the process */ 
#define SIGILL  4   /* Illegal instruction. */ 
#define SIGTRAP 5   /* Trace trap. */ 
#define SIGABRT 6   /* Abort. */

struct sigaction act;
		
void handler(int sig, siginfo_t *siginfo, void *context){
	printf("Sending pid: %ld, UID: %ld\n",(long) siginfo->si_pid, (long) siginfo->si_uid);
}

int main(){
	key_t k_shmptr=ftok("spid",65);
	int shm_spid=shmget(k_shmptr,sizeof(int),IPC_CREAT|0666);
	int* shmptr=(int*)shmat(shm_spid,NULL,0);
	cout << "pid received is" << *shmptr;
	int pid = *shmptr;
	shmdt(shmptr);
	shmctl(shm_spid,IPC_RMID,NULL); 

	key_t kill_key_shmptr=ftok("killCount",65);
	int kill_shm_spid=shmget(kill_key_shmptr,sizeof(int),IPC_CREAT|0666);
	int* kill_shmptr=(int*)shmat(kill_shm_spid,NULL,0);
	int killCount = *kill_shmptr;
	
	int c;
	
	while(1){
		cout << "\n Enter value of signal: ";
		cin >> c;
		if(c==1){
			kill(pid,SIGUSR1);
			*kill_shmptr = *kill_shmptr+1;
		}else if(c==2){
			kill(pid,SIGUSR2);
			*kill_shmptr = *kill_shmptr+1;
		}else{
			cout << "else";
			cout << "\n total kills: " << *kill_shmptr;
		}
	}
	shmdt(kill_shmptr);
	shmctl(kill_shm_spid,IPC_RMID,NULL);

}