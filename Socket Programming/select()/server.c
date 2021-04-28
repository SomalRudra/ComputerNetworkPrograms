#include <unistd.h> 
#include <stdio.h> 
#include <sys/socket.h> 
#include <stdlib.h> 
#include <netinet/in.h> 
#include <string.h> 
#include <arpa/inet.h>
#include <poll.h>
#include <sys/poll.h>
#include <pthread.h>
#include <sys/select.h>
int nsfd1,nsfd2,nsfd3;
  int sfd1,sfd2,sfd3;

  int max(int a,int b){
      if(a<b) return b;
      else return a;
  }

int main()
{
    
    printf(
    "\n\nafter running server executable(server.out), run client1.out \n\n"
    );
    if((sfd1=socket(AF_INET,SOCK_STREAM,0))==0)
    {
        perror("socket 1 failed\n");
        return 0;
    }
    int opt1=1,opt2=1,opt3=1;
    if (setsockopt(sfd1, SOL_SOCKET, SO_REUSEADDR | SO_REUSEPORT, 
												&opt1, sizeof(opt1))) 
	{ 
		perror("setsockopt"); 
		exit(EXIT_FAILURE); 
	} 
    if((sfd2=socket(AF_INET,SOCK_STREAM,0))==0)
    {
        perror("socket 2 failed\n");
        return 0;
    }
    if (setsockopt(sfd2, SOL_SOCKET, SO_REUSEADDR | SO_REUSEPORT, 
												&opt2, sizeof(opt2))) 
	{ 
		perror("setsockopt"); 
		exit(EXIT_FAILURE); 
	} 
    if((sfd3=socket(AF_INET,SOCK_STREAM,0))==0)
    {
        perror("socket 3 failed\n");
        return 0;
    }
    if (setsockopt(sfd3, SOL_SOCKET, SO_REUSEADDR | SO_REUSEPORT, 
												&opt3, sizeof(opt3))) 
	{ 
		perror("setsockopt"); 
		exit(EXIT_FAILURE); 
	} 
    struct sockaddr_in addr1,addr2,addr3;
    addr1.sin_port=htons(7001);
    addr1.sin_family=AF_INET;
    inet_pton(AF_INET, "127.0.0.1", &(addr1.sin_addr));
    addr2.sin_port=htons(8001);
    addr2.sin_family=AF_INET;
    inet_pton(AF_INET, "127.0.0.1", &(addr2.sin_addr));
    addr3.sin_port=htons(9001);
    addr3.sin_family=AF_INET;
    inet_pton(AF_INET, "127.0.0.1", &(addr3.sin_addr));
    if(bind(sfd1,(struct sockaddr*)&addr1,sizeof(addr1))<0)
    {
        perror("bind 1 failed");
        return 0;
    }
    if(bind(sfd2,(struct sockaddr*)&addr2,sizeof(addr2))<0)
    {
        perror("bind 2 failed");
        return 0;
    }
    if(bind(sfd3,(struct sockaddr*)&addr3,sizeof(addr3))<0)
    {
        perror("bind 3 failed");
        return 0;
    }
    if(listen(sfd1,3)<0)
    {
        perror("listen 1 failed");
        return 0;
    }
    if(listen(sfd2,3)<0)
    {
        perror("listen 2 failed");
        return 0;
    }
    if(listen(sfd3,3)<0)
    {
        perror("listen 3 failed");
        return 0;
    }
    
    socklen_t addrlen1=sizeof(addr1);
    socklen_t addrlen2=sizeof(addr2);
    socklen_t addrlen3=sizeof(addr3);

    //select starts from here

    fd_set currentFDsets;
    FD_ZERO(&currentFDsets);
    int maxSize = max(max(sfd1,sfd2),sfd3)+1;

    while (1)
    {
        FD_SET(sfd1,&currentFDsets);
        FD_SET(sfd2,&currentFDsets);
        FD_SET(sfd3,&currentFDsets);
        int ready_fd = select(maxSize,&currentFDsets,NULL,NULL,NULL);

        if(FD_ISSET(sfd1,&currentFDsets)){
            nsfd1=accept(sfd1,(struct sockaddr*)&addr1,&addrlen1);
            int c;
            if((c=fork())==0){
                close(sfd1);
                char buff[1024];
                read(nsfd1,buff,sizeof(&buff));
                printf("\n Value in server -> %s",buff);
                printf("\n Write to client ->");
                char buffWrite[1024];
                scanf("%s",buffWrite);
                write(nsfd1,buffWrite,sizeof(&buffWrite));
                close(nsfd1);
                exit(0);

            }
            close(nsfd1);
        }
        if(FD_ISSET(sfd2,&currentFDsets)){
            nsfd2=accept(sfd2,(struct sockaddr*)&addr2,&addrlen2);
            int c;
            if((c=fork())==0){
                close(sfd2);
                char buff[1024];
                read(nsfd2,buff,sizeof(&buff));
                printf("\n Value in server -> %s",buff);
                printf("\n Write to client->");
                char buffWrite[1024];
                scanf("%s",buffWrite);
                write(nsfd2,buffWrite,sizeof(&buffWrite));
                
                
                close(nsfd2);
                exit(0);

            }
            close(nsfd2);
        }if(FD_ISSET(sfd3,&currentFDsets)){
            nsfd3=accept(sfd3,(struct sockaddr*)&addr3,&addrlen3);
            int c;
            if((c=fork())==0){
                close(sfd3);
                char buff[1024];
                read(nsfd3,buff,sizeof(&buff));
                printf("\n Value in server -> %s",buff);
                printf("\n Write to client->");
                char buffWrite[1024];
                scanf("%s",buffWrite);
                write(nsfd3,buffWrite,sizeof(&buffWrite));
                close(nsfd3);
                exit(0);

            }
            close(nsfd3);
        }
    
    }   return 0;
}