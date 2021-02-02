#include<stdio.h> 
#include <unistd.h> 
#include <sys/types.h>
#include <stdlib.h> 
#include <iostream>
#include <sys/wait.h>
#include <sys/ipc.h> 
#include <sys/shm.h> 
#include <fcntl.h>
#include <pthread.h> 
#include <semaphore.h> 
#include <string.h>
using namespace std;

// shared memory X
key_t key1 = ftok("X",65);  
int shmid1 = shmget(key1,1024,0666|IPC_CREAT); 
char *str1 = (char*) shmat(shmid1,(void*)0,0); 

//shared memory Y
key_t key2 = ftok("Y",65); 
int shmid2 = shmget(key2,1024,0666|IPC_CREAT); 
char *str2 = (char*) shmat(shmid2,(void*)0,0); 

void c2pRead(int signum){
  	
	cout << "\nData read from X in child process-> " << str1 << endl;
  	shmdt(str1);
  	shmctl(shmid1,IPC_RMID,NULL);  

 }

void p2cWrite(int signum){
		
  	cout << "\nWrite into X from P1: ";
	char writeXbuff[1024];
	fgets(writeXbuff,1024,stdin);
	str1=writeXbuff;
	signal(SIGUSR2,c2pRead);
	raise(SIGUSR2);
	shmdt(str1);
  	shmctl(shmid1,IPC_RMID,NULL);  
}


 void p2cRead(int signum){
	 cout << "\nData read from Y in parent process-> " << str2 << endl;
  	shmdt(str2);
  	shmctl(shmid1,IPC_RMID,NULL);  

 }

 void c2pwrite(int signum){
	 cout << "\nWrite into Y from Child: ";
	char writeXbuff[1024];
	fgets(writeXbuff,1024,stdin);
	str2=writeXbuff;
	
	signal(SIGUSR1,p2cRead);
	raise(SIGUSR1);
	
  	shmdt(str2);  

  	shmctl(shmid2,IPC_RMID,NULL);  


 }





int main(){
    signal(SIGUSR1,p2cWrite);
    signal(SIGUSR2,c2pwrite);
   
    pid_t c=fork();
    if(c>0){
    	raise(SIGUSR1);
		sleep(10);
    }
    else{
		sleep(6);
        raise(SIGUSR2);
    }
	return 0;
	
}
