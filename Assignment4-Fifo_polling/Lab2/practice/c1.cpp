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

const char* name = "C1";

void* reader(void* args)
{
   while(1)
   {
   	 int rfd = open(name,O_RDONLY);
   	 ssize_t nr;
     struct iovec iov[1];
   	 char c,msg[1024];
   	 iov[0].iov_base = msg;
   	 iov[0].iov_len = sizeof(msg);
   	 readv(rfd,iov,1);
   	 cout<<msg<<"\n";
   	 close(rfd);
   }
}

void* writer(void* args)
{
  while(1)
  {
  	 struct iovec iov[1];
     ssize_t nr;
  	 char c,msg[1024],buff[1024];
  	 int j=0;
  	 read(STDIN_FILENO,&c,1);
  	 while(c!='\n')
  	 {
       msg[j++] = c;
       read(STDIN_FILENO,&c,1);
  	 }
  	 msg[j] = '\0';
  	 buff[0] = '\0';
  	 strcat(buff,name);
  	 strcat(buff,":");
  	 strcat(buff,msg);
     strcat(buff,"\n");
     iov[0].iov_base = buff;
     iov[0].iov_len = sizeof(buff);
     //mkfifo("server",0666);
  	 int wfd = open("serve",O_WRONLY);
  	 writev(wfd,iov,1);

     close(wfd);
  }
}

int main()
{
	cout<<name<<" Client started!\n";
	mkfifo(name,0666);



	pthread_t write_th,read_th;
	pthread_create(&write_th,NULL,writer,NULL);
	pthread_create(&read_th,NULL,reader,NULL);

	pthread_join(write_th,NULL);
	pthread_join(read_th,NULL);
}