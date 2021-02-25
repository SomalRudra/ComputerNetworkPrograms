#include<stdio.h>  
#include<unistd.h>  
#include<fcntl.h> 
#include <iostream>
#include<stdlib.h> 
#include <semaphore.h>
using namespace std;

int main(){
    char buff[1024];
    cout << "write from P2 to P1";
    fgets(buff,1024,stdin);
    write(1,buff,1024);
    FILE *fd = popen("./test1","r");
    cout << " \n Returned FD From P2 is" << fileno(fd);
    char buff1[1024];
    read(fileno(fd),buff1,1024);
    //cout << "\nRead From P1->" << buff1;
}