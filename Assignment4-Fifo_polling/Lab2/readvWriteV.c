#define _XOPEN_SOURCE_EXTENDED 1
// #include <iostream>
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
//#include <iostream>
//using namespace std;


int main(){
    char *str0 = "C";
    char *str1 = "N";
    struct iovec iov[2];
    ssize_t nwritten,nread;
    
    iov[0].iov_base = str0;
    iov[0].iov_len = strlen(str0);
    iov[1].iov_base = str1;
    iov[1].iov_len = strlen(str1);

    int writeFd = open("input.txt",O_WRONLY);
    nwritten = writev(writeFd, iov, 2);
    close(writeFd);
    printf("number of bytes written %d",nwritten);

    // int readFd;
    char *str2 = "Computer ";
    char *str3 = "world\n";
    struct iovec iov1[1];
    // iov1[0].iov_base = str2;
    // iov1[0].iov_len = strlen(str2);
    // iov1[1].iov_base = str3;
    // iov1[1].iov_len = strlen(str3);
    int readFd = open("output.txt",O_RDONLY);
    // char* x;
    // int count=0;
    // while(read(readFd,&x,1)){
    //     printf("%c",x);
    //     count++;
    //     if(count==20) break;
    // }
    nread = readv(readFd,iov,1);
    printf("\nnumber of bytes read %d",nread);

    // ssize_t bytes_read;
    // int fd;
    // char buf0[20];
    // char buf1[30];
    // char buf2[40];
    // int iovcnt;
    // struct iovec iov[3];


    // iov[0].iov_base = buf0;
    // iov[0].iov_len = sizeof(buf0);
    // iov[1].iov_base = buf1;
    // iov[1].iov_len = sizeof(buf1);
    // iov[2].iov_base = buf2;
    // iov[2].iov_len = sizeof(buf2);
    // iovcnt = sizeof(iov) / sizeof(struct iovec);


    // bytes_read = readv(fd, iov, iovcnt);
    // cout << "bytes read->" << bytes_read;

}