#include <iostream>
#include <sys/types.h>
#include <sys/wait.h>
#include <sys/stat.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <fcntl.h>
#include <string.h>
#include <sys/uio.h>
using namespace std;

int main()
{
	mkfifo("serve",0666);
	mkfifo("C1",0666);
	mkfifo("C2",0666);
	while(1){
	int fd = open("serve",O_RDONLY);
	cout<<"Serve Fifo is opened\n";
	char buff[2][1024],c;
	int j=0,cnt=0;

    struct iovec iov[2];
    ssize_t nr;
    for(int i=0;i<2;i++)
    {
      iov[i].iov_base = buff[i];
      iov[i].iov_len = sizeof(buff[i]);
    }
    readv(fd,iov,2);

	//read(fd,&buff,1024);
	cout<<"Message read from group by server: \n";
	for(int i=0;i<2;i++)
	{
		printf ("Client %d: %s", i+1, (char *) iov[i].iov_base);
	}
	int fd2 = open("C1",O_WRONLY);
	int fd3 = open("C2",O_WRONLY);
	//write(fd3,buff[0],1024);
	writev(fd2,iov,2);
	writev(fd3,iov,2);
	//write(fd2,buff[0],1024);
	//write(fd3,buff[1],1024);
	//write(fd2,buff[1],1024);
	close(fd2);
	close(fd3);
	close(fd);
   }
	return 0;
}