// using a common file descriptor read one line from main process and
// another line from different programme.
#include<stdio.h> 
#include <unistd.h> //for fork system call
#include <sys/types.h>
#include <stdlib.h> //for exit system call
#include <sys/wait.h>
#include <sys/ipc.h> 
#include <sys/shm.h> 
#include <fcntl.h>
#include <pthread.h> 
#include <semaphore.h> 
const char* sem1= "s1";
const char* sem2 = "s2";

void p1(int fd){

	sem_t *s1=sem_open(sem1,O_EXCL);
	sem_t *s2=sem_open(sem2,O_EXCL);
	
	char buf;
	while(read(fd,&buf,1)==1){

	  if(buf=='\n'){
		   printf("->p1\n");
		   sem_post(s1);
		   sem_wait(s2);
	  }
	  else if(buf==' '){
	    	printf(" ");
	  }
	  else{
	    	printf("%c",buf);
	  }
	}
}



int main(){
	sem_t *s1 = sem_open(sem1,O_CREAT|O_EXCL,0666,0);
    sem_t *s2 = sem_open(sem2,O_CREAT|O_EXCL,0666,0);
    int fd=open("input.txt",O_RDONLY);
    
    pid_t c=fork();
    if(c>0){
    	p1(fd);
    }
    else{
		dup2(fd,STDIN_FILENO); 
        execv("./as2q2part2.out",NULL);
    }
    sem_unlink(sem1);
    sem_unlink(sem2); 
	return 0;
}
