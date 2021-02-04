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
#include <sys/stat.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <poll.h>
#include <unistd.h>
#include <signal.h>
#include <iostream>
using namespace std;

#define FILLED 0 
#define Ready 1 
#define NotReady -1 

#define SIGHUP  1   /* Hangup the process */ 
#define SIGINT  2   /* Interrupt the process */ 
#define SIGQUIT 3   /* Quit the process */ 
#define SIGILL  4   /* Illegal instruction. */ 
#define SIGTRAP 5   /* Trace trap. */ 
#define SIGABRT 6   /* Abort. */


int main(){
    char* c2fifo = "c2fifo";
    mkfifo(c2fifo,0666);
	while(1){
        cout << "\nWrite data into C2";
        char buff[1024];
        cin >> buff;
        int fd = open(c2fifo,O_WRONLY);
        write(fd,buff,1024);
        close(fd);
    }
	return 0;
}