#include<stdio.h>
#include <pthread.h>
#include <unistd.h>
#include<poll.h>
struct pollfd fds[3];
int timeout_msecs = 5000;
int ret;

//run only this program and give input. no need to run other programs
int main(){
  	int fd[3];
  	char buf[128];
  	fd[0]=fileno(popen("./poll_1","r"));
  	fd[1]=fileno(popen("./poll_2","r"));
  	fd[2]=fileno(popen("./poll_3","r"));
  	int t=4;
  	while(t--)
	{
    	fds[0].fd=fd[0];
    	fds[1].fd=fd[1];
    	fds[2].fd=fd[2];
    	
    	fds[0].events=POLLIN;
    	fds[1].events=POLLIN;
    	fds[2].events=POLLIN;
  		
  		ret=poll(fds,3,-1);
  		
  		if (ret<=0) 
  		{
			printf ("%d seconds elapsed.\n", 0);
			return 0;
		}
    	for(int j=0;j<10;j++)
    	{
      		if(fds[j].revents & POLLIN)
      		{
        		int i=read(fds[j].fd,buf,5);
        		write(1,buf,i);
                printf("value received-> %s\n",buf);


      		}
    	}
	}
  	return 0;
}