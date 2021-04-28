#include<stdio.h>  
#include<unistd.h>  
#include<fcntl.h> 
#include<stdlib.h> 
#include<pthread.h>
#include <semaphore.h>
#include <iostream>
using namespace std;

sem_t s1,s2,s3;
void* p1(void* arg1){
	int loop=2;
	while(loop--){
		cout << "in p1\n";
		sem_post(&s2);
		sem_wait(&s1);
	}
	sem_post(&s2);
	
}
void* p2(void* arg2){
	int loop=2;
	sem_wait(&s2);
	while(loop--){
		cout << "in p2\n";
		sem_post(&s3);
		sem_wait(&s2);
	}
	sem_post(&s3);
}
void* p3(void* arg3){
	int loop=2;
	sem_wait(&s3);
	while(loop--){
		cout << "in p3\n";
		sem_post(&s1);
		sem_wait(&s3);
	}
}
int main(){
	pthread_t pt1,pt2,pt3;
	sem_init(&s1,0,0);
	sem_init(&s2,0,0);
	sem_init(&s3,0,0);
	pthread_create(&pt1,NULL,p1,NULL);
	pthread_create(&pt2,NULL,p2,NULL);
	pthread_create(&pt3,NULL,p3,NULL);
	pthread_join(pt1,NULL);
	pthread_join(pt2,NULL);
	pthread_join(pt3,NULL);
	sem_destroy(&s1);
	sem_destroy(&s2);
	sem_destroy(&s3);
	return 0;
}

/* 
	sem_init	-> Initializes an unnamed semaphore
	sem_destroy -> Destroys an unnamed semaphore
	sem_wait -> for waiting
	sem_post -> for resume after wait
*/