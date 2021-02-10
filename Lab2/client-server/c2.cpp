
#include <sys/uio.h>
#include <bits/stdc++.h>
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
#include <sys/stat.h>
#include <sys/time.h>
#include <assert.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <poll.h>
#include <unistd.h>
#include <signal.h>
#define _XOPEN_SOURCE_EXTENDED 1
// #include <iostream>
#include <sys/uio.h>
// #include <bits/stdc++.h>
#include <unistd.h>
#include <stdio.h> //for fork system call
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
    mkfifo("c2",0666);

    int c2fd = open("c2",O_RDONLY);

    struct iovec iov[1];
    // iov[0].iov_base = "1";
    // iov[0].iov_len = 1;

    ssize_t size = readv(c2fd,iov,1);
    cout << "number of bytes read->" << size;
    close(c2fd);
    
}