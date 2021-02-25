#include <iostream> 
#include <sys/ipc.h> 
#include <sys/shm.h> 
#include <stdio.h> 
using namespace std; 

int main() 
{ 
	// ftok-> convert a pathname and a project identifier to a System V IPC key
	key_t key = ftok("shmfile",65); 

	// shmget returns an identifier in shmid 
	int shmid = shmget(key,1024,0666|IPC_CREAT); 

	// shmat to attach to shared memory 
	char *str = (char*) shmat(shmid,(void*)0,0); 

	str = "written in memory";

	printf("Data read from memory: %s\n",str); 
	
	//detach from shared memory 
	shmdt(str); 
	
	// destroy the shared memory 
	shmctl(shmid,IPC_RMID,NULL); 
	
	return 0; 
} 