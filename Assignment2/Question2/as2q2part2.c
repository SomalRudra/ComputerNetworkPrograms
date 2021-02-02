#include<stdio.h>  
#include<unistd.h>  
#include<fcntl.h> 
#include<stdlib.h> 
#include <semaphore.h>

const char* sem1= "s1";
const char* sem2 = "s2";


void func(){
  sem_t *s1=sem_open(sem1,0);
  sem_t *s2=sem_open(sem2,0);

  sem_wait(s1);

  char buf;
  while(read(STDIN_FILENO,&buf,1)==1){

    if(buf=='\n'){
       printf("->p2\n");
       sem_post(s2);
       sem_wait(s1);
    }
    else if(buf==' '){
        printf(" ");
    }
    else{
        printf("%c",buf);
    }
  }
  sem_post(s2);
}

int main(){
  
    func();
    return 0;
}