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
  int tcp_socket,udp_socket,sfd3;

  int max(int a,int b){
      if(a>b) return a;
      else return b;
  }

int main()
{
    
    printf(
    "\n\nafter running server executable(server.out), run client1.out \n\n"
    );
    if((tcp_socket=socket(AF_INET,SOCK_STREAM,0))==0)
    {
        perror("socket 1 failed\n");
        return 0;
    }
    int opt1=1,opt2=1,opt3=1;
    if (setsockopt(tcp_socket, SOL_SOCKET, SO_REUSEADDR | SO_REUSEPORT, 
												&opt1, sizeof(opt1))) 
	{ 
		perror("setsockopt"); 
		exit(EXIT_FAILURE); 
	} 
    if((udp_socket=socket(AF_INET,SOCK_DGRAM,0))==0)
    {
        perror("socket 2 failed\n");
        return 0;
    }
    if (setsockopt(udp_socket, SOL_SOCKET, SO_REUSEADDR | SO_REUSEPORT, 
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
    // addr2.sin_port=htons(8001);
    // addr2.sin_family=AF_INET;
    // inet_pton(AF_INET, "127.0.0.1", &(addr2.sin_addr));
    
    if(bind(tcp_socket,(struct sockaddr*)&addr1,sizeof(addr1))<0)
    {
        perror("bind 1 failed");
        return 0;
    }
    if(bind(udp_socket,(struct sockaddr*)&addr1,sizeof(addr1))<0)
    {
        perror("bind 2 failed");
        return 0;
    }
    
    //no listening in udp
    if(listen(tcp_socket,3)<0)
    {
        perror("listen 1 failed");
        return 0;
    }
    
    
    socklen_t addrlen1=sizeof(addr1);
    socklen_t addrlen2=sizeof(addr2);

    //select starts from here

    fd_set currentFDsets;
    FD_ZERO(&currentFDsets);
    int maxSize = max(tcp_socket,udp_socket)+1;

    while (1)
    {
        FD_SET(tcp_socket,&currentFDsets);
        FD_SET(udp_socket,&currentFDsets);
        
        int ready_fd = select(maxSize,&currentFDsets,NULL,NULL,NULL);

        if(FD_ISSET(tcp_socket,&currentFDsets)){
            nsfd1=accept(tcp_socket,(struct sockaddr*)&addr1,&addrlen1);
            int c;
            if((c=fork())==0){
                close(tcp_socket);
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
        if(FD_ISSET(udp_socket,&currentFDsets)){
           
           // no forking here, no closing fds, 
                char buff[1024];
                int n = recvfrom(udp_socket, buff, sizeof(buff), MSG_WAITALL, 
                         (struct sockaddr*)&addr2, &addrlen2);
                printf("\n Value in server -> %s",buff);


                printf("\n Write to client->");
                char buffWrite[1024];
                scanf("%s",buffWrite);
                sendto(udp_socket, (const char*)buffWrite, sizeof(buffWrite), MSG_WAITALL, 
                   (struct sockaddr*)&addr2, sizeof(addr2)); 
                
        }
    
    }   return 0;
}