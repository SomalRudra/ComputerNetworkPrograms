#include <stdio.h> 
#include <string.h> 
#include <fcntl.h> 
#include <sys/stat.h> 
#include <sys/types.h> 
#include <unistd.h> 
#include <iostream>
using namespace std;


int main(){
    char* famousfifo = "ff";
    char* localfifo_c2 = "lf_c2";

    mkfifo(famousfifo,0666);
    mkfifo(localfifo_c2,0666);
    
    int wfd,rfd;
    char buff[100],buff2[10];
    while(1){  
        wfd = open(famousfifo,O_WRONLY);
        cout << "start writing message\n:";
        strcat(buff2,"#client2->");
        fgets(buff,100,stdin);
        strcat(buff2,buff);
        write(wfd,buff2,100);
        close(wfd);

        //reading from local buffer
        rfd = open(localfifo_c2,O_RDONLY);
        read(rfd,buff,100);
        cout << "Message In Client2's local fifo: " << buff << endl;
        close(rfd);  

    }
}