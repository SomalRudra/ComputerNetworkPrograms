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

struct shared_memory
{
	int pid;
	int kill_count;
};
typedef shared_memory *shmptr;
		


int main(){
	key_t k_shmptr=ftok("spid",65);
	int shm_spid=shmget(k_shmptr,sizeof(shared_memory),IPC_CREAT|0666);
	shmptr shmptr1=(shmptr)shmat(shm_spid,NULL,0);
	int pid = shmptr1->pid;
	
	int c;
	
	while(1){
		cout << "\n Enter value of signal: ";
		cin >> c;
		if(c==1){
			kill(pid,SIGUSR1);
			shmptr1->kill_count = shmptr1->kill_count+1;
		}else if(c==2){
			kill(pid,SIGUSR2);			
			shmptr1->kill_count = shmptr1->kill_count+1;
		}else{
			cout << "\n total kills: " << shmptr1->kill_count;
		}
	}
	// shmdt(kill_shmptr);
	// shmctl(kill_shm_spid,IPC_RMID,NULL);

}