#include<stdio.h>  
#include<unistd.h>  
#include<fcntl.h> 
#include <iostream>
#include<stdlib.h> 
#include <semaphore.h>
using namespace std;

int main(){
    FILE *fd = popen("./test2","r");
    char buff[1024];
    cout << "\nvalue read at parent";
    read(fileno(fd),buff,1024);
    cout << buff << "\n";
    cout << "Write from P1\n";
    fgets(buff,1024,stdin);
    cout << "Input from user->" << buff;
    write(0,buff,4);
}