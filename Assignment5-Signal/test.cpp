#include <stdio.h>
#include <unistd.h>
#include <string.h>
#include <signal.h>
#include <fcntl.h>
#include <stdlib.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <iostream>
using namespace std; 

int main() 
{ 
	char* ftrpid = "ftrpid"; //fifo to write pid
	cout << ftrpid;
	mkfifo(ftrpid, 0666); 
	
	int fd = open(ftrpid,O_WRONLY);

	//------> convert int to string buffer
	cout << getpid();

	write(fd,ftrpid,5);
	close(fd);

	return 0; 
} 
