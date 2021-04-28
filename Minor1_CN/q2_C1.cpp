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

const char* sem1= "s1";
const char* sem2 = "s2";

int main(){
    sem_t *s1=sem_open(sem1,O_CREAT,0666,0);
	sem_t *s2=sem_open(sem1,O_CREAT,0666,0);

    key_t k_shmptr=ftok("spid",65);
	int shm_spid=shmget(k_shmptr,sizeof(int),IPC_CREAT|0666);
	int* shmptr=(int*)shmat(shm_spid,NULL,0);
    cout << "write to sharedmemory: " << "\n";
    int n;
    cin >> n;
    *shmptr = n;
    cout << "\nData written from process 1->" << *shmptr;
    cout << "\nSemaphore 1->" << s1;
    cout << "\nSemaphore 2->" << s2;
    //workOnESS();
    // sem_wait(s1);
    // sem_post(s2);
    cout << "\nReleased and back to process 1";
	shmdt(shmptr);
}