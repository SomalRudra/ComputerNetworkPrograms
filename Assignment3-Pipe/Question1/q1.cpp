#include<stdio.h>  
#include<unistd.h>  
#include<fcntl.h> 
#include<stdlib.h> 
#include <semaphore.h>
#include <iostream>

using namespace std;

int main(){
    int pp[2];
    pipe(pp);
    char buff[128];
    fgets(buff,128,stdin);
    write(pp[1],buff,128);
    char buff2[128];
    read(pp[0],buff2,128);
    cout << buff2;
}