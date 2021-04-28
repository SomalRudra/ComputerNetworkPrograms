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
    char* localfifo_c1 = "lf_c1";
    char* localfifo_c2 = "lf_c2";
    mkfifo(famousfifo,0666);
    mkfifo(localfifo_c1,0666);
    mkfifo(localfifo_c2,0666);
    
    int rfd,wfd1,wfd2;
    char buff[100];
    while(1){
        rfd = open(famousfifo,O_RDONLY);
        read(rfd,buff,100);
        cout << "Message In Server: " << buff << endl;
        close(rfd);  

        //writing in local buffer
        wfd1 = open(localfifo_c1,O_WRONLY);
        write(wfd1,buff,100);
        close(wfd1);
        wfd2 = open(localfifo_c2,O_WRONLY);
        write(wfd2,buff,100);
        close(wfd2);
        
        
    }    
}