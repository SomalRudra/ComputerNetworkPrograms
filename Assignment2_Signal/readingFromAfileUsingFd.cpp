#include <iostream> 
#include <sys/ipc.h> 
#include <sys/shm.h> 
#include <stdio.h> 
#include <unistd.h>
#include <stdlib.h>
#include <semaphore.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
using namespace std; 

sem_t sem1;
sem_t sem2;

int main() 
{ 
    int fd = open("input.txt",O_RDONLY);
    char ch;
    while(read(fd,&ch,1)){
        if(ch=='\n'){
            cout << "\n\n\n new line";
            cout << "\n";
        }else{
            cout << ch;
        }
    }
} 
