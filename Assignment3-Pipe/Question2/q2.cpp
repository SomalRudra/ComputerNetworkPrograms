#include<stdio.h>  
#include<unistd.h>  
#include<fcntl.h> 
#include<stdlib.h> 
#include <semaphore.h>
#include <iostream>

using namespace std;

int main(){
    int A[2];
    int B[2];
    pipe(A);
    pipe(B);
    int c = fork();
    if(c>0){
        char buff[128];
        close(A[0]);
        close(B[1]);
        fgets(buff,128,stdin);
        write(A[1],buff,128);
        char buff2[128];
        read(B[0],buff2,128);
        cout << "read from pipeB: "<< buff2;
    }else{

        char buff[128];
        close(A[1]);
        close(B[0]);
        
        read(A[0],buff,128);
        cout << "read from pipeA: " << buff;
        buff[0]='X';
        write(B[1],buff,128);
        // char buff2[128];

    }
}