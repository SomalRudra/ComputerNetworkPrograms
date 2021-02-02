#include <fcntl.h>
#include <stdio.h>
#include <iostream>
#include <sys/poll.h>
#include <sys/time.h>
#include <unistd.h>
using namespace std; 

int main(){
    int x;
    cout << "read from keyboard->0, read from file->1,\n what do you want to do?";
    cin >> x;
    if(x==0){

        cout << "buffer is of length 2. write something of 2 characters\n";
        struct pollfd pfds[1];
        pfds[0].fd = STDIN_FILENO;
        pfds[0].events = POLLIN;
        char buff1[2];
        
        poll(pfds,2,-1);
        if(pfds[0].revents & POLLIN){            
            int i = read(pfds[0].fd,buff1,2);
            if(!i) cout << "wrong\n";
            else {
                write(STDOUT_FILENO,buff1,2);
                cout << buff1 << "\n";
            }
            
        }
              
    }else{
        struct pollfd pfdsFILE[1];
        pfdsFILE[0].fd = open("input.txt",O_RDONLY);
        pfdsFILE[0].events = POLLIN;
        poll(pfdsFILE,2,-1);
        char buff2[8];
        if(pfdsFILE[0].revents & POLLIN){            
            int i = read(pfdsFILE[0].fd,buff2,8);
            if(!i) cout << "wrong\n";
            else{
                cout << "read from file: " << buff2;
            } 
        }
    }
     
    

}
