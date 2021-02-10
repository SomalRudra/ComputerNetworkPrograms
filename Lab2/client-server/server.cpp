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
#include <sys/poll.h>
#include <sys/time.h>
#include <assert.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <poll.h>
#include <unistd.h>
#include <signal.h>
#include <sys/stat.h>
#include <sys/uio.h>
using namespace std;

int main(){
    mkfifo("c1",0666);
    mkfifo("c2",0666);

    int c1fd = open("c1",O_WRONLY);
    int c2fd = open("c2",O_WRONLY);

    struct iovec iov[1];
    char buff[1][1024];
    cout << "write data";
    cin >> buff[0];
    iov[0].iov_base = buff[0];
    iov[0].iov_len = 1;
    cout << buff[0];

    ssize_t size1 = writev(c1fd,iov,1);
    cout << "size of data written into c1->" << size1;
    ssize_t size2 = writev(c2fd,iov,1);
    cout << "size of data written into c2->" << size2;
    close(c1fd);
    close(c2fd);
}