 #include <iostream>
#include <sys/uio.h>
// #include <bits/stdc++.h>
#include <unistd.h>
#include <stdio.h> 
#include <unistd.h> //for fork system call
#include <sys/types.h>
#include <stdlib.h> //for exit system call
#include <sys/wait.h>
#include <sys/ipc.h> 
#include <sys/shm.h> 
#include <fcntl.h>
#include <pthread.h> 
#include <semaphore.h> 
#include <string.h>
#include <sys/stat.h>
#include <sys/poll.h>
#include <sys/time.h>
#include <assert.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <poll.h>
#include <unistd.h>
#include <signal.h>
#include <sys/uio.h>
using namespace std;

int main(){
    mkfifo("c1",0666);

    int c1fd = open("c1",O_RDONLY);

    struct iovec iov[1];
    // iov[0].iov_base = "1";
    // iov[0].iov_len = 1;


    ssize_t size = readv(c1fd,iov,1);

    cout << "number of bytes read->" << size;
    cout << (char *) iov[0].iov_base;
    close(c1fd);
    
}